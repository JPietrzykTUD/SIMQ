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


#ifndef EXPERIMENT_THROUGHPUT_TIME_SLOT
#define EXPERIMENT_THROUGHPUT_TIME_SLOT 30
#endif
#ifndef EXPERIMENT_THROUGHPUT_THREAD_BUDGET
#define EXPERIMENT_THROUGHPUT_THREAD_BUDGET 4
#endif
#include <benchmarks/queries/q11/query11_data.h>
#include <benchmarks/queries/data/measurement_helper.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <future>
#include <atomic>
#include <utils/cpu_freq_monitor.h>

namespace tuddbs {
   template<
      class VectorExtension, std::size_t ColumnCount, std::size_t QueryCount, std::size_t BatchSize
   >
   struct sequential_parallel_wl_q11_tput {
      template<
         std::size_t BS = BatchSize, typename std::enable_if< BS == 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
      ) {
         using T = typename VectorExtension::base_t;
         
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         column <T> * const results_from_queries = create_column(
            T, vector_constants_t< VectorExtension >::vector_element_count_t::value * EXPERIMENT_THROUGHPUT_THREAD_BUDGET
         );
         results_from_queries->init( 0 );
         
         std::vector < column < T > * > filter_result_masks;
         std::vector < column < T > * > aggregation_result_cols;
         
         for(
            std::size_t query_id = 0; query_id < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++query_id
            ) {
            filter_result_masks.emplace_back( create_bitmask( T, data_count ) );
            aggregation_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
         }
         
         std::array <std::atomic< std::size_t >, EXPERIMENT_THROUGHPUT_THREAD_BUDGET> global_query_counter = { };
         std::promise< void >                                 p;
         std::shared_future< void >                           ready_future( p.get_future( ) );
         
         bool finished = false;
         auto
              magic    =
                 [ &ready_future, &global_query_counter, &finished, &datagenerator, &filter_result_masks, &aggregation_result_cols, &results_from_queries ](
                    const std::size_t tid, const std::size_t column_id
                 ) {
                    ready_future.wait( );
               
                    size_t pos = tid;
               
                    filter_result_masks[ tid ]->init( 0 ); // make one per thread
                    aggregation_result_cols[ tid ]->init( 0 ); // make one per thread
               
                    column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
                    column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               
                    while( !finished ) {
                       T predicate = datagenerator->extended_predicates[ pos & 1023 ];
                       pos += EXPERIMENT_THROUGHPUT_THREAD_BUDGET;
                       sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                          filter_result_masks[ tid ], filter_column, broadcast< VectorExtension >( predicate )
                       );
                       sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
                          aggregation_result_cols[ tid ], aggregate_column, filter_result_masks[ tid ]
                       );
                       results_from_queries->data_ptr[ tid ] = aggregation_result_cols[ tid ]->data_ptr[ 0 ];
                       ++global_query_counter[ tid ];
                    }
                 };
         
         std::size_t               column_id = 0;
         std::vector <std::thread> pool;
         cpu_set_t cpuset;
         for(
            std::size_t            tid       = 0; tid < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++tid
            ) {
            CPU_ZERO(&cpuset);
            CPU_SET(tid, &cpuset);
            // Parallelize
            pool.emplace_back( std::thread( magic, tid, column_id ) );
            int rc = pthread_setaffinity_np(pool[tid].native_handle(), sizeof(cpu_set_t), &cpuset);
            if (rc != 0) {
               std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
            }
            if( ( ( tid + 1 ) % ( QueryCount / ColumnCount ) == 0 ) ) {
               ++column_id;
               if( column_id >= ColumnCount ) {
                  column_id = 0;
               }
            }
         }
         using namespace std::chrono_literals;
         cpu_freq_monitor::instance()->init(
            EXPERIMENT_THROUGHPUT_THREAD_BUDGET, (std::chrono::milliseconds( EXPERIMENT_THROUGHPUT_TIME_SLOT ) / cpu_freq_monitor::instance()
               ->get_resolution()) + 1
         );
         p.set_value( );
         
         cpu_freq_monitor::instance()->start_monitoring();
         auto start_interval = now( );
         while( std::chrono::duration_cast< std::chrono::seconds >( now( ) - start_interval ).count( ) < EXPERIMENT_THROUGHPUT_TIME_SLOT ) {
            std::this_thread::sleep_for( 900ms );
         }
         std::size_t    executed_queries = 0;
         for(
            std::size_t i                = 0; i < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++i
            ) {
            executed_queries += global_query_counter[ i ];
         }
         auto end_interval = now( );
         cpu_freq_monitor::instance()->stop_monitoring();
         finished = true;
         
         // Wait for threads to finish
         std::for_each( pool.begin( ), pool.end( ), [ ]( std::thread & t ) { t.join( ); } );
         T aggregated_result = (T) 0;
         for(
            std::size_t i                = 0; i < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++i
            ) {
            aggregated_result ^= results_from_queries->data_ptr[ i ];
         }
         
         experiment_query_11_12< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
            0, datagenerator, "SISQ-PAR-Budget", "BITMASK", "SEQ", executed_queries, EXPERIMENT_THROUGHPUT_THREAD_BUDGET,
            start_interval, start_interval, start_interval, end_interval, time_elapsed_ns( start_interval,
                                                                                           end_interval ),
            cpu_freq_monitor::instance()->get_data(), 0, results_from_queries
         );
         destroy_column( results_from_queries );
         for(
            std::size_t query_id = 0; query_id < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++query_id
            ) {
            destroy_column( filter_result_masks[ query_id ] );
            destroy_column( aggregation_result_cols[ query_id ] );
         }
      }
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
      template<
         std::size_t BS = BatchSize, typename std::enable_if< BS != 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
      ) {
         using T = typename VectorExtension::base_t;
      
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         column <T> * const results_from_queries = create_column(
            T, vector_constants_t< VectorExtension >::vector_element_count_t::value * EXPERIMENT_THROUGHPUT_THREAD_BUDGET
         );
         results_from_queries->init( 0 );
      
         std::vector < column < T > * > filter_result_masks;
         std::vector < column < T > * > aggregation_result_cols;
      
         for(
            std::size_t query_id = 0; query_id < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++query_id
            ) {
            filter_result_masks.emplace_back( create_bitmask( T, data_count ) );
            aggregation_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
         }
      
         std::array <std::atomic< std::size_t >, EXPERIMENT_THROUGHPUT_THREAD_BUDGET> global_query_counter = { };
         std::promise< void >                                 p;
         std::shared_future< void >                           ready_future( p.get_future( ) );
   
         std::size_t const BatchCount = BatchSize / sizeof( T );
         
         bool finished = false;
         auto
              magic    =
                 [ &ready_future, &global_query_counter, &finished, &datagenerator, &filter_result_masks,
                   &aggregation_result_cols, &results_from_queries ](
                    const std::size_t tid, const std::size_t column_id
                 ) {
                    ready_future.wait( );
                    size_t pos = tid;
            
                    filter_result_masks[ tid ]->init( 0 ); // make one per thread
                    aggregation_result_cols[ tid ]->init( 0 ); // make one per thread
            
                    column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
                    column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
   
                    T * filter_column_ptr    = filter_column->data_ptr;
                    T * const filter_column_ptr_end = filter_column->data_ptr + filter_column->data_count;
                    T * aggregate_column_ptr = aggregate_column->data_ptr;
                    typename VectorExtension::mask_t * filter_result_bitmask_ptr = ( typename VectorExtension::mask_t
                       * ) filter_result_masks[ tid ]->data_ptr;
                    typename VectorExtension::mask_t * filter_result_bitmask_ptr_new;
                    auto aggregation_result_column_ptr = aggregation_result_cols[ tid ]->data_ptr;
                    while( !finished ) {
                       T predicate = datagenerator->extended_predicates[ pos & 1023 ];
                       pos += EXPERIMENT_THROUGHPUT_THREAD_BUDGET;
   
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
                       results_from_queries->data_ptr[ tid ] = aggregation_result_cols[ tid ]->data_ptr[ 0 ];
                       ++global_query_counter[ tid ];
                    }
                 };
      
         std::size_t               column_id = 0;
         std::vector <std::thread> pool;
         cpu_set_t cpuset;
         for(
            std::size_t            tid       = 0; tid < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++tid
            ) {
            CPU_ZERO(&cpuset);
            CPU_SET(tid, &cpuset);
            // Parallelize
            pool.emplace_back( std::thread( magic, tid, column_id ) );
            int rc = pthread_setaffinity_np(pool[tid].native_handle(), sizeof(cpu_set_t), &cpuset);
            if (rc != 0) {
               std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
            }
            if( ( ( tid + 1 ) % ( QueryCount / ColumnCount ) == 0 ) ) {
               ++column_id;
               if( column_id >= ColumnCount ) {
                  column_id = 0;
               }
            }
         }
         using namespace std::chrono_literals;
         cpu_freq_monitor::instance()->init(
            EXPERIMENT_THROUGHPUT_THREAD_BUDGET, (std::chrono::milliseconds( EXPERIMENT_THROUGHPUT_TIME_SLOT ) / cpu_freq_monitor::instance()
               ->get_resolution()) + 1
         );
         p.set_value( );
      
         cpu_freq_monitor::instance()->start_monitoring();
         auto start_interval = now( );
         while( std::chrono::duration_cast< std::chrono::seconds >( now( ) - start_interval ).count( ) < EXPERIMENT_THROUGHPUT_TIME_SLOT ) {
            std::this_thread::sleep_for( 900ms );
         }
         std::size_t    executed_queries = 0;
         for(
            std::size_t i                = 0; i < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++i
            ) {
            executed_queries += global_query_counter[ i ];
         }
         auto end_interval = now( );
         cpu_freq_monitor::instance()->stop_monitoring();
         finished = true;
      
         // Wait for threads to finish
         std::for_each( pool.begin( ), pool.end( ), [ ]( std::thread & t ) { t.join( ); } );
         T aggregated_result = (T) 0;
         for(
            std::size_t i                = 0; i < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++i
            ) {
            aggregated_result ^= results_from_queries->data_ptr[ i ];
         }
      
         experiment_query_11_12< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
            0, datagenerator, "SISQ-PAR-Budget", "BITMASK", "SEQ", executed_queries, EXPERIMENT_THROUGHPUT_THREAD_BUDGET,
            start_interval, start_interval, start_interval, end_interval, time_elapsed_ns( start_interval,
                                                                                           end_interval ),
            cpu_freq_monitor::instance()->get_data(), 0, results_from_queries
         );
         destroy_column( results_from_queries );
         for(
            std::size_t query_id = 0; query_id < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++query_id
            ) {
            destroy_column( filter_result_masks[ query_id ] );
            destroy_column( aggregation_result_cols[ query_id ] );
         }
      }
   };
   
}

#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_PARALLEL_TPUT_H
