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

#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_PARALLEL_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_PARALLEL_H

#include <benchmarks/queries/q11/query11_data.h>
#include <thread>
#include <vector>
#include <algorithm>

namespace tuddbs {
   template<
      class VectorExtension,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize
   >
      template<
         std::size_t BS = BatchSize,
         typename std::enable_if< BS == 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
      ) {
         using T                 = typename VectorExtension::base_t;
         
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         column< T > * const results_from_queries =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         results_from_queries->init(0);
         
		std::vector< column< T > * > filter_result_masks;
		std::vector< column< T > * > aggregation_result_cols;
		
		for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
			filter_result_masks.emplace_back( create_bitmask( T, data_count ) );
			aggregation_result_cols.emplace_back( create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value ) );
		}
		
		for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
			for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
				filter_result_masks[query_id]->init( 0 ); // make one per thread
				aggregation_result_cols[query_id]->init( 0 ); // make one per thread
			}
			std::size_t column_id = 0;
			
			auto dummy = cache_flusher::instance( )->flush( );
			auto start_simq_builder = now( );
			
			// QCnt Workers
			auto magic = [&datagenerator,&filter_result_masks,&aggregation_result_cols,&results_from_queries]( const std::size_t query_id, const std::size_t column_id ) {
				column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
				column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
				T predicate = datagenerator->predicates[ query_id ];

				sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
				  filter_result_masks[query_id], filter_column, broadcast< VectorExtension >( predicate )
				);
				sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
				  aggregation_result_cols[query_id], aggregate_column, filter_result_masks[query_id]
				);
				results_from_queries->data_ptr[ query_id ] = aggregation_result_cols[query_id]->data_ptr[ 0 ];
			};

			auto start = now( );
			std::vector< std::thread > pool;
			for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
				// Parallelize
				pool.emplace_back( std::thread( magic, query_id, column_id ) );
				if( ( ( query_id + 1 ) % ( QueryCount / ColumnCount ) == 0 )  ) {
					++column_id;
			   }
			}

			// Wait for threads to finish
			std::for_each(pool.begin(), pool.end(), 
				[](std::thread &t) {t.join();}
			);
			
			auto end = now( );
			experiment_query11< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
				rep, datagenerator, "SISQ", "BITMASK", "SEQ-PAR",
				start_simq_builder, start_simq_builder, start, end, results_from_queries, dummy
			);
		 }
		destroy_column( results_from_queries );
		for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
			destroy_column( filter_result_masks[query_id] );
			destroy_column( aggregation_result_cols[query_id] );
		}
      }
      
   };
   
}

#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_PARALLEL_H
