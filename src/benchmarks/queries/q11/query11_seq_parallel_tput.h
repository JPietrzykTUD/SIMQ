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

#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_PARALLEL_TPUT_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_PARALLEL_TPUT_H

#include <benchmarks/queries/q11/query11_data.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <future>
#include <atomic>

namespace tuddbs {
   template<
      class VectorExtension,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize
   >
	struct sequential_parallel_wl_q11_tput {
	  template<
		 std::size_t BS = BatchSize,
		 typename std::enable_if< BS == 0, std::nullptr_t >::type = nullptr
		>
		static void run(
			datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
		) {
			using T                 = typename VectorExtension::base_t;
			const size_t ThreadCount = 16;
			
			std::size_t const data_count = datagenerator->data_size / sizeof( T );
			column< T > * const results_from_queries =
				create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value * ThreadCount );
			results_from_queries->init(0);
			
			std::vector< column< T > * > filter_result_masks;
			std::vector< column< T > * > aggregation_result_cols;

			for( std::size_t query_id = 0; query_id < ThreadCount; ++query_id ) {
				filter_result_masks.emplace_back( create_bitmask( T, data_count ) );
				aggregation_result_cols.emplace_back( create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value ) );
			}
			
			std::atomic<size_t> global_query_counter = {0};
			std::promise<void> p;
			std::shared_future<void> ready_future(p.get_future());
			// uint64_t* flushs = (uint64_t*) malloc( sizeof(uint64_t) * ThreadCount );
			
			bool finished = false;
			auto magic = [&ready_future,&global_query_counter,&finished,&datagenerator,&filter_result_masks,&aggregation_result_cols,&results_from_queries]( const std::size_t tid, const std::size_t column_id ) {
				ready_future.wait();

				size_t pos = tid;
				// flushs[tid] = cache_flusher::instance( )->flush( );
				// auto start_simq_builder = now( );

				filter_result_masks[tid]->init( 0 ); // make one per thread
				aggregation_result_cols[tid]->init( 0 ); // make one per thread

				column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
				column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];

				while (!finished) {
					T predicate = datagenerator->extended_predicates[ pos & 1023 ];
					pos += ThreadCount;
					// T predicate = datagenerator->predicates[ tid ];
					sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
						filter_result_masks[tid], filter_column, broadcast< VectorExtension >( predicate )
					);
					sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
						aggregation_result_cols[tid], aggregate_column, filter_result_masks[tid]
					);
					results_from_queries->data_ptr[ tid ] = aggregation_result_cols[tid]->data_ptr[ 0 ];
					global_query_counter += 1;
				}
			};
			
			// auto start = now( );
			std::size_t column_id = 0;
			std::vector< std::thread > pool;
			for( std::size_t tid = 0; tid < ThreadCount; ++tid ) {
				// Parallelize
				pool.emplace_back( std::thread( magic, tid, column_id ) );
				if( ( ( tid + 1 ) % ( QueryCount / ColumnCount ) == 0 )  ) {
					++column_id;
					if ( column_id >= ColumnCount ) {
						column_id = 0;
					}
				}
			}
			p.set_value();
			
			auto start_interval = now();
			while ( std::chrono::duration_cast< std::chrono::seconds >( now() - start_interval ).count() < 10 ) {
				using namespace std::chrono_literals;
				std::this_thread::sleep_for( 900ms );
			}
			std::cout << "SEQ GQC: " << global_query_counter << std::endl;
			finished = true;
			
			// Wait for threads to finish
			std::for_each(pool.begin(), pool.end(), [](std::thread &t) {t.join();} );
			// uint64_t dummy = 0;
			// for ( std::size_t tid = 0; tid < ThreadCount; ++tid ) {
				// dummy += flushs[tid];
			// }
			// experiment_query11< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
				// 0, datagenerator, "SISQ", "BITMASK", "SEQ-PAR-TPUT",
				// now(), now(), now(), now(), results_from_queries, dummy
			// );
			destroy_column( results_from_queries );
			for( std::size_t query_id = 0; query_id < ThreadCount; ++query_id ) {
				destroy_column( filter_result_masks[query_id] );
				destroy_column( aggregation_result_cols[query_id] );
			}
		}
   };
   
}

#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_PARALLEL_TPUT_H
