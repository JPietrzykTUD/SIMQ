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
#include <benchmarks/queries/data/measurement_helper.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>

namespace tuddbs {
   template<
      class VectorExtension,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize
   >
   struct sequential_parallel_wl_q11 {
      template<
         std::size_t BS = BatchSize,
         typename std::enable_if< BS == 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
      ) {
         using T = typename VectorExtension::base_t;
         using chrono_tp = std::chrono::time_point< std::chrono::high_resolution_clock >;
         
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         column <T> * const results_from_queries =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         results_from_queries->init( 0 );
         
         std::vector < column < T > * > filter_result_masks;
         std::vector < column < T > * > aggregation_result_cols;
         
         for(
            std::size_t query_id = 0; query_id < QueryCount; ++query_id
            ) {
            filter_result_masks.emplace_back( create_bitmask( T, data_count ) );
            aggregation_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
         }
         
         chrono_tp * start_tps = ( chrono_tp * ) malloc( sizeof( chrono_tp ) * QueryCount );
         chrono_tp * end_tps   = ( chrono_tp * ) malloc( sizeof( chrono_tp ) * QueryCount );
         
         for(
            std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep
         ) {
            for(
               std::size_t query_id           = 0; query_id < QueryCount; ++query_id
               ) {
               filter_result_masks[ query_id ]->init( 0 ); // make one per thread
               aggregation_result_cols[ query_id ]->init( 0 ); // make one per thread
            }
            std::size_t    column_id          = 0;
            auto           dummy              = cache_flusher::instance( )->flush( );
            auto           start_simq_builder = now( );
            
            // QCnt Workers
            auto
               magic                           =
               [ &datagenerator, &filter_result_masks, &aggregation_result_cols, &results_from_queries, &start_tps, &end_tps ](
                  const std::size_t query_id, const std::size_t column_id
               ) {
                  start_tps[ query_id ] = now( );
                  column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
                  column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
                  T predicate = datagenerator->predicates[ query_id ];
                  
                  sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                     filter_result_masks[ query_id ], filter_column, broadcast< VectorExtension >( predicate )
                  );
                  sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
                     aggregation_result_cols[ query_id ], aggregate_column, filter_result_masks[ query_id ]
                  );
                  results_from_queries->data_ptr[ query_id ] = aggregation_result_cols[ query_id ]->data_ptr[ 0 ];
                  end_tps[ query_id ]                        = now( );
               };
            
            // auto start = now( );
            std::vector <std::thread> pool;
            for(
               std::size_t            query_id = 0; query_id < QueryCount; ++query_id
               ) {
               cpu_set_t cpuset;
               CPU_ZERO(&cpuset);
#ifdef CPU_PINNING_DENSE
               #ifdef KNL
                  CPU_SET( ( (query_id*68)%271 ), &cpuset );
   #elif defined(XEON)
                  CPU_SET( ( (query_id*12)%23 ), &cpuset );
   #else
                  CPU_SET( query_id, &cpuset );
   #endif
#elif defined(CPU_PINNING_LOOSE)
               CPU_SET( query_id, &cpuset );
#else
               static_assert(false, "No Pinning strategy defined.");
#endif
               // Parallelize
               pool.emplace_back( std::thread( magic, query_id, column_id ) );
               int rc = pthread_setaffinity_np(pool[query_id].native_handle(), sizeof(cpu_set_t), &cpuset);
               if (rc != 0) {
                  std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
               }
               if( ( ( query_id + 1 ) % ( QueryCount / ColumnCount ) == 0 ) ) {
                  ++column_id;
               }
            }
            
            // Wait for threads to finish
            std::for_each(
               pool.begin( ), pool.end( ),
               [ ]( std::thread & t ) { t.join( ); }
            );
            
            // auto end = now( );
            
            auto earliest_start    = start_tps[ 0 ];
            auto latest_end        = end_tps[ 0 ];
            auto total_cpu_time_ns = time_elapsed_ns( start_tps[ 0 ], end_tps[ 0 ] );
            
            for(
               std::size_t query_id = 1; query_id < QueryCount; ++query_id
               ) {
               earliest_start = std::min( earliest_start, start_tps[ query_id ] );
               latest_end     = std::max( latest_end, end_tps[ query_id ] );
               total_cpu_time_ns
                  += time_elapsed_ns( start_tps[ query_id ], end_tps[ query_id ] );
                  
            }
            
            experiment_query_11_12< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
               rep, datagenerator, "SISQ-PAR", "BITMASK", "SEQ", QueryCount, QueryCount,
               start_simq_builder, start_simq_builder, earliest_start, latest_end,
               total_cpu_time_ns, "", dummy, results_from_queries
            );
         }
         destroy_column( results_from_queries );
         for(
            std::size_t query_id = 0; query_id < QueryCount; ++query_id
            ) {
            destroy_column( filter_result_masks[ query_id ] );
            destroy_column( aggregation_result_cols[ query_id ] );
         }
      }
   
   
   
   
      template<
         std::size_t BS = BatchSize,
         typename std::enable_if< BS != 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
      ) {
         using T = typename VectorExtension::base_t;
         using chrono_tp = std::chrono::time_point< std::chrono::high_resolution_clock >;
      
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         column <T> * const results_from_queries =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         results_from_queries->init( 0 );
      
         std::vector < column < T > * > filter_result_masks;
         std::vector < column < T > * > aggregation_result_cols;
      
         for(
            std::size_t query_id = 0; query_id < QueryCount; ++query_id
            ) {
            filter_result_masks.emplace_back( create_bitmask( T, data_count ) );
            aggregation_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
         }
   
         std::size_t const BatchCount = BatchSize / sizeof( T );
         
         chrono_tp * start_tps = ( chrono_tp * ) malloc( sizeof( chrono_tp ) * QueryCount );
         chrono_tp * end_tps   = ( chrono_tp * ) malloc( sizeof( chrono_tp ) * QueryCount );
      
         for(
            std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep
            ) {
            for(
               std::size_t query_id           = 0; query_id < QueryCount; ++query_id
               ) {
               filter_result_masks[ query_id ]->init( 0 ); // make one per thread
               aggregation_result_cols[ query_id ]->init( 0 ); // make one per thread
            }
            std::size_t    column_id          = 0;
            auto           dummy              = cache_flusher::instance( )->flush( );
            auto           start_simq_builder = now( );
         
            // QCnt Workers
            auto
               magic                           =
               [ &datagenerator, &filter_result_masks, &aggregation_result_cols, &results_from_queries,
                 &start_tps,
                 &end_tps ](
                  const std::size_t query_id, const std::size_t column_id
               ) {
                  start_tps[ query_id ] = now( );
                  column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
                  column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
                  T predicate = datagenerator->predicates[ query_id ];
   
                  typename VectorExtension::mask_t * filter_result_bitmask_ptr_new;
                  
                  
                  T * filter_column_ptr    = filter_column->data_ptr;
                  T * aggregate_column_ptr = aggregate_column->data_ptr;
                  aggregation_result_cols[query_id]->init( 0 );
                  T * aggregation_result_column_ptr = aggregation_result_cols[ query_id ]->data_ptr;
                  T * const filter_column_ptr_end = filter_column->data_ptr + filter_column->data_count;
                  typename VectorExtension::mask_t
                     * filter_result_bitmask_ptr =
                     ( typename VectorExtension::mask_t * ) ( filter_result_masks[ query_id ]->data_ptr );
                  
                  while( filter_column_ptr != filter_column_ptr_end ) {
                     filter_result_bitmask_ptr_new =
                        sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                           filter_result_bitmask_ptr, filter_column_ptr, BatchCount, broadcast< VectorExtension >(
                              predicate )
                        );
                     sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
                        aggregation_result_column_ptr,  aggregate_column_ptr, BatchCount, filter_result_bitmask_ptr
                     );
                     filter_result_bitmask_ptr = filter_result_bitmask_ptr_new;
                  }
                  results_from_queries->data_ptr[ query_id ] = aggregation_result_cols[ query_id ]->data_ptr[ 0 ];
                  end_tps[ query_id ]                        = now( );
               };
         
            // auto start = now( );
            std::vector <std::thread> pool;
            for(
               std::size_t            query_id = 0; query_id < QueryCount; ++query_id
               ) {
               cpu_set_t cpuset;
               CPU_ZERO(&cpuset);
#ifdef CPU_PINNING_DENSE
               #ifdef KNL
                  CPU_SET( ( (query_id*68)%271 ), &cpuset );
   #elif defined(XEON)
                  CPU_SET( ( (query_id*12)%23 ), &cpuset );
   #else
                  CPU_SET( query_id, &cpuset );
   #endif
#elif defined(CPU_PINNING_LOOSE)
               CPU_SET( query_id, &cpuset );
#else
               static_assert(false, "No Pinning strategy defined.");
#endif
               // Parallelize
               pool.emplace_back( std::thread( magic, query_id, column_id ) );
               int rc = pthread_setaffinity_np(pool[query_id].native_handle(), sizeof(cpu_set_t), &cpuset);
               if (rc != 0) {
                  std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
               }

               if( ( ( query_id + 1 ) % ( QueryCount / ColumnCount ) == 0 ) ) {
                  ++column_id;
               }
            }
         
            // Wait for threads to finish
            std::for_each(
               pool.begin( ), pool.end( ),
               [ ]( std::thread & t ) { t.join( ); }
            );
         
            // auto end = now( );
         
            auto earliest_start    = start_tps[ 0 ];
            auto latest_end        = end_tps[ 0 ];
            auto total_cpu_time_ns = time_elapsed_ns( start_tps[ 0 ], end_tps[ 0 ] );
         
            for(
               std::size_t query_id = 1; query_id < QueryCount; ++query_id
               ) {
               earliest_start = std::min( earliest_start, start_tps[ query_id ] );
               latest_end     = std::max( latest_end, end_tps[ query_id ] );
               total_cpu_time_ns
                  += time_elapsed_ns( start_tps[ query_id ], end_tps[ query_id ] );
            
            }
         
            experiment_query_11_12< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
               rep, datagenerator, "SISQ-PAR", "BITMASK", "SEQ", QueryCount, QueryCount,
               start_simq_builder, start_simq_builder, earliest_start, latest_end,
               total_cpu_time_ns, "", dummy, results_from_queries
            );
         }
         destroy_column( results_from_queries );
         for(
            std::size_t query_id = 0; query_id < QueryCount; ++query_id
            ) {
            destroy_column( filter_result_masks[ query_id ] );
            destroy_column( aggregation_result_cols[ query_id ] );
         }
      }
      
   };
   
}

#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_PARALLEL_H
