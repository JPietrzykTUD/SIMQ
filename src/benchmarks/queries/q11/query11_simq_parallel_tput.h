/*
 * This file is part of the SIMQ Project (https://github.com/JPietrzykTUD/SIMQ).
 * Copyright (c) 2020 Johannes Pietrzyk.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SIMQ_PARALLEL_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SIMQ_PARALLEL_H

#include <benchmarks/queries/q11/query11_data.h>
#include <thread>
#include <future>
#include <atomic>

namespace tuddbs {
   template<
      template< class, std::size_t, typename, class > class Strategy,
                                                      class VectorExtension,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize
   >
   struct simq_wl_q11_parallel_tput {
      template<
         std::size_t BS = BatchSize,
         typename std::enable_if< BS == 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
      ) {
         const size_t ThreadCount = 16;
         
         using T                 = typename VectorExtension::base_t;
         using column_array_t    = column_array< VectorExtension, ColumnCount >;
         using predicate_array_t = value_array< VectorExtension, QueryCount >;
         using svb_t             =
         simq_vector_builder_t<
            Strategy,
            column_array_t,
            QueryCount
         >;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
		std::vector< column< T > * > filter_result_masks;
		std::vector< column< T > * > aggregation_result_cols;
		for( std::size_t tid = 0; tid < ThreadCount; ++tid ) {
			filter_result_masks.emplace_back( create_bitmask( T, data_count * QueryCount ) );
			aggregation_result_cols.emplace_back( create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value ) );
			filter_result_masks[tid]->init( 0 ); // make one per thread
			aggregation_result_cols[tid]->init( 0 ); // make one per thread
		}
		
		// column< T > * const filter_result_bitmask = create_bitmask( T, data_count * QueryCount );
		// column< T > * const aggregation_result_column = create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
		std::atomic<size_t> global_query_counter = {0};
		std::promise<void> p;
		std::shared_future<void> ready_future(p.get_future());
		// uint64_t* flushs = (uint64_t*) malloc( sizeof(uint64_t) * ThreadCount );

		bool finished = false;

		auto magic = [&ready_future,&filter_result_masks,&aggregation_result_cols,&global_query_counter,&datagenerator,&finished] ( const size_t tid ) {
			ready_future.wait();
			column_array_t q11_filter_column_array;
			column_array_t q11_aggregate_column_array;
			for( std::size_t column_id = 0; column_id < ColumnCount; ++column_id ) {
				q11_filter_column_array.set( column_id, datagenerator->filter_columns[ column_id ] );
				q11_aggregate_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
			}
			predicate_array_t q11_predicates_array;
			
			filter_result_masks[tid]->init( 0 ); // make one per thread
			aggregation_result_cols[tid]->init( 0 ); // make one per thread
			
			size_t pos = 0;
			while (!finished) {
				pos = 0;
				for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
					q11_predicates_array.set( query_id, datagenerator->extended_predicates[ pos++ & 1023 ] );
				}
				typename VectorExtension::vector_t predicate_vec =
					simq_value_vector_view_t< predicate_array_t, ColumnCount >::apply( q11_predicates_array );

				// flushs[tid] = cache_flusher::instance()->flush();
				// auto start_simq_build = now();
				svb_t svb_filter( q11_filter_column_array );
				svb_t svb_aggregation( q11_aggregate_column_array );
				// auto end_simq_build = now();
				
				filter_impl< VectorExtension, svb_t, point_filter_lt_core >::apply(
				   filter_result_masks[tid], svb_filter, predicate_vec
				);
				aggregate_impl< VectorExtension, svb_t, aggregate_mask_add >::apply(
				   aggregation_result_cols[tid], svb_aggregation, filter_result_masks[tid]
				);

				[[maybe_unused]]typename VectorExtension::base_t * tmp = store< VectorExtension >(
				   aggregation_result_cols[tid]->data_ptr,
				   aggregate_mask_add< VectorExtension >::template finalize< svb_t::lanes_per_query_t::value >(
					  load< VectorExtension >( aggregation_result_cols[tid]->data_ptr )
				   )
				);
				global_query_counter += QueryCount;
			}
		};
		
		std::vector< std::thread > pool;
		for( std::size_t tid = 0; tid < ThreadCount; ++tid ) {
			// Parallelize
			pool.emplace_back( std::thread( magic, tid ) );
		}
		p.set_value();
		
		auto start_interval = now();
		while ( std::chrono::duration_cast< std::chrono::seconds >( now() - start_interval ).count() < 10 ) {
			using namespace std::chrono_literals;
			std::this_thread::sleep_for( 900ms );
		}
		std::cout << "PAR GQC: " << global_query_counter << std::endl;
		finished = true;

		// Wait for threads to finish
		std::for_each(pool.begin(), pool.end(), [](std::thread &t) {t.join();} );
		// std::cout << "GQC after sync: " << global_query_counter << std::endl;

		// experiment_query11< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
		   // rep, datagenerator, "SIMQ", "BITMASK", Strategy< column_array_t, QueryCount,
															// typename VectorExtension::base_t, VectorExtension >::get_name( ),
		   // start_simq_build, end_simq_build, start, end, aggregation_result_column, dummy
		// );

		for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
			destroy_column( filter_result_masks[query_id] );
			destroy_column( aggregation_result_cols[query_id] );
		}
      }
      
   };
   
}
#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SIMQ_PARALLEL_H
