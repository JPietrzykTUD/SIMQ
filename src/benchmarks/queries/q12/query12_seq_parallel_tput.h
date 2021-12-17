/*
 * This file is part of the SIMQ Project (https://github.com/JPietrzykTUD/SIMQ).
 * Copyright (c) 2021 Johannes Pietrzyk.
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

#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SEQ_PARALLEL_TPUT_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SEQ_PARALLEL_TPUT_H

#include <benchmarks/queries/q11/query11_data.h>
#include <benchmarks/queries/data/measurement_helper.h>

#include <future>
#include <atomic>
#include <utils/cpu_freq_monitor.h>

#define ThreadCount 12

namespace tuddbs {
   
   
   template<
      class VectorExtension,
      std::size_t QueryCount2ndStageOp1,
      std::size_t QueryCount2ndStageOp2,
      std::size_t ColumnCount = 1,
      std::size_t ColumnCount2ndStageOp1 = 1
   >
   struct seq_parallel_wl_q12_two_Stage2_ops_tput {
      using QueryCount_t = std::integral_constant<
         std::size_t,
         QueryCount2ndStageOp1 + QueryCount2ndStageOp2
      >;
      
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         using T = typename VectorExtension::base_t;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
         column <T> * const results1_from_queries =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value * ThreadCount );
         column <T> * const results2_from_queries =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value * ThreadCount );
         results1_from_queries->init( 0 );
         results2_from_queries->init( 0 );

         std::vector < column < T > * > filter_result_masks;
         std::vector < column < T > * > aggregation_result_cols1;
         std::vector < column < T > * > aggregation_result_cols2;

         for( std::size_t query_id = 0; query_id < ThreadCount; ++query_id ) {
            filter_result_masks.emplace_back( create_bitmask( T, data_count ) );
            aggregation_result_cols1.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
            aggregation_result_cols2.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
         }
        
         for( std::size_t query_id = 0; query_id < ThreadCount; ++query_id ) {
            filter_result_masks[ query_id ]->init( 0 );
            aggregation_result_cols1[ query_id ]->init( 0 );
            aggregation_result_cols2[ query_id ]->init( 0 );
         }

         // const size_t TotalQueryCount = QueryCount2ndStageOp1 + QueryCount2ndStageOp2;
         // auto           dummy              = cache_flusher::instance( )->flush( );
         // auto           start_simq_builder = now( );

         std::array <std::atomic< std::size_t >, ThreadCount> global_query_counter = { };
         std::promise< void > p;
         std::shared_future< void > ready_future( p.get_future( ) );         
         bool finished = false;

         auto magic1 = [ &datagenerator, &aggregation_result_cols1, &filter_result_masks, &results1_from_queries ]( const std::size_t tid, const std::size_t column_id, const size_t pos ) {
            column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
            column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
            T predicate = datagenerator->extended_predicates[ pos & 1023 ];

            sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
               filter_result_masks[ tid ], filter_column, broadcast< VectorExtension >( predicate )
            );
            sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
               aggregation_result_cols1[ tid ], aggregate_column, filter_result_masks[ tid ]
            );
            results1_from_queries->data_ptr[ tid ] = aggregation_result_cols1[ tid ]->data_ptr[ 0 ];
         };

         auto magic2 = [ &datagenerator, &aggregation_result_cols2, &filter_result_masks, &results2_from_queries ]( const std::size_t tid, const std::size_t column_id, const size_t pos ) {
            column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
            column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
            T predicate = datagenerator->extended_predicates[ pos & 1023 ];
            
            sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
               filter_result_masks[ tid ], filter_column, broadcast< VectorExtension >( predicate )
            );
            sequential_aggregate_impl< VectorExtension, aggregate_mask_min >::apply(
               aggregation_result_cols2[ tid ], aggregate_column, filter_result_masks[ tid ]
            );
            results2_from_queries->data_ptr[ tid ] = aggregation_result_cols2[ tid ]->data_ptr[ 0 ];
         };
         
         auto metamagic = [ &ready_future, &finished, &magic1, &magic2, &global_query_counter ] ( const size_t tid, const size_t column_id ) {
            size_t pos = tid;
            ready_future.wait();
            while ( !finished ) {
               magic1( tid, column_id, pos );
               ++global_query_counter[ tid ];
               magic2( tid, column_id, pos );
               ++global_query_counter[ tid ];
               pos += ThreadCount;
            }
         };
         
         std::size_t column_id = 0;
         std::vector <std::thread> pool;
         for(
            std::size_t            tid       = 0; tid < ThreadCount; ++tid
            ) {
            cpu_set_t cpuset;
            CPU_ZERO(&cpuset);
#ifdef CPU_PINNING_DENSE
            #ifdef KNL
                  CPU_SET( ( (tid*68)%271 ), &cpuset );
   #elif defined(XEON)
                  CPU_SET( ( (tid*12)%23 ), &cpuset );
   #else
                  CPU_SET( tid, &cpuset );
   #endif
#elif defined(CPU_PINNING_LOOSE)
            CPU_SET( tid, &cpuset );
#else
            static_assert(false, "No Pinning strategy defined.");
#endif
            // Parallelize
            pool.emplace_back( std::thread( metamagic, tid, column_id ) );
            int rc = pthread_setaffinity_np(pool[tid].native_handle(), sizeof(cpu_set_t), &cpuset);
            if (rc != 0) {
               std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
            }
            if( ( ( tid + 1 ) % ( ThreadCount / ColumnCount ) == 0 ) ) {
               ++column_id;
               if( column_id >= ColumnCount ) {
                  column_id = 0;
               }
            }
         }
         using namespace std::chrono_literals;
         cpu_freq_monitor::instance()->init(
            ThreadCount, (std::chrono::milliseconds( EXPERIMENT_THROUGHPUT_TIME_SLOT ) / cpu_freq_monitor::instance()
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
            std::size_t i                = 0; i < ThreadCount; ++i
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
            std::size_t i                = 0; i < ThreadCount; ++i
            ) {
            aggregated_result ^= results2_from_queries->data_ptr[ i ] ^ results1_from_queries->data_ptr[ i ];
         }
         
   
         experiment_query_11_12<
            VectorExtension, ColumnCount,
            QueryCount_t::value, 0, QueryCount2ndStageOp2
         >::print_experiment_result(
            0, datagenerator, "SISQ-PAR-Budget", "BITMASK", "SEQ",
            executed_queries, EXPERIMENT_THROUGHPUT_THREAD_BUDGET, start_interval,
            start_interval,  start_interval, end_interval, time_elapsed_ns( start_interval,
                                                                            end_interval ), "", 0,
            results1_from_queries,
            results2_from_queries
         );

         for( std::size_t query_id = 0; query_id < ThreadCount; ++query_id ) {
            destroy_column( filter_result_masks[ query_id ] );
            destroy_column( aggregation_result_cols1[ query_id ] );
            destroy_column( aggregation_result_cols2[ query_id ] );
         }
         destroy_column( results2_from_queries );
         destroy_column( results1_from_queries );
      }
      
   };
   
   template<
      class VectorExtension,
      std::size_t QueryCount2ndStageOp1,
      std::size_t QueryCount2ndStageOp2,
      std::size_t QueryCount2ndStageOp3,
      std::size_t ColumnCount = 1,
      std::size_t ColumnCount2ndStageOp1 = 1,
      std::size_t ColumnCount2ndStageOp2_3 = 1
   >
   struct seq_parallel_wl_q12_three_Stage2_ops_tput {
      using QueryCount_t = std::integral_constant<
         std::size_t,
         QueryCount2ndStageOp1 + QueryCount2ndStageOp2 + QueryCount2ndStageOp3
      >;
      
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         using T = typename VectorExtension::base_t;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
         column <T> * const results1_from_queries =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value * ThreadCount );
         column <T> * const results2_from_queries =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value * ThreadCount );
         column <T> * const results3_from_queries =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value * ThreadCount );
         results1_from_queries->init( 0 );
         results2_from_queries->init( 0 );
         results3_from_queries->init( 0 );

         std::vector < column < T > * > filter_result_masks;
         std::vector < column < T > * > aggregation_result_cols1;
         std::vector < column < T > * > aggregation_result_cols2;
         std::vector < column < T > * > aggregation_result_cols3;

         for( std::size_t query_id = 0; query_id < ThreadCount; ++query_id ) {
            filter_result_masks.emplace_back( create_bitmask( T, data_count ) );
            aggregation_result_cols1.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
            aggregation_result_cols2.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
            aggregation_result_cols3.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
         }

         for( std::size_t query_id = 0; query_id < ThreadCount; ++query_id ) {
            filter_result_masks[ query_id ]->init( 0 );
            aggregation_result_cols1[ query_id ]->init( 0 );
            aggregation_result_cols2[ query_id ]->init( 0 );
            aggregation_result_cols3[ query_id ]->init( 0 );
         }

         // auto           dummy              = cache_flusher::instance( )->flush( );
         // auto           start_simq_builder = now( );

         std::array <std::atomic< std::size_t >, ThreadCount> global_query_counter = { };
         std::promise< void > p;
         std::shared_future< void > ready_future( p.get_future( ) );         
         bool finished = false;

         auto magic1 = [ &datagenerator, &aggregation_result_cols1, &filter_result_masks, &results1_from_queries ]( const std::size_t tid, const std::size_t column_id, const size_t pos ) {
            column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
            column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
            T predicate = datagenerator->extended_predicates[ pos & 1023 ];

            sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
               filter_result_masks[ tid ], filter_column, broadcast< VectorExtension >( predicate )
            );
            sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
               aggregation_result_cols1[ tid ], aggregate_column, filter_result_masks[ tid ]
            );
            results1_from_queries->data_ptr[ tid ] = aggregation_result_cols1[ tid ]->data_ptr[ 0 ];
         };

         auto magic2 = [ &datagenerator, &aggregation_result_cols2, &filter_result_masks, &results2_from_queries ]( const std::size_t tid, const std::size_t column_id, const size_t pos ) {
            column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
            column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
            T predicate = datagenerator->extended_predicates[ pos & 1023 ];
            
            sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
               filter_result_masks[ tid ], filter_column, broadcast< VectorExtension >( predicate )
            );
            sequential_aggregate_impl< VectorExtension, aggregate_mask_min >::apply(
               aggregation_result_cols2[ tid ], aggregate_column, filter_result_masks[ tid ]
            );
            results2_from_queries->data_ptr[ tid ] = aggregation_result_cols2[ tid ]->data_ptr[ 0 ];
         };
         
         auto magic3 = [ &datagenerator, &aggregation_result_cols3, &filter_result_masks, &results3_from_queries ] ( const std::size_t tid, const std::size_t column_id, const size_t pos ) {
            column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
            column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
            T predicate = datagenerator->extended_predicates[ pos & 1023 ];
            
            sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
               filter_result_masks[ tid ], filter_column, broadcast< VectorExtension >( predicate )
            );
            sequential_aggregate_impl< VectorExtension, aggregate_mask_max >::apply(
               aggregation_result_cols3[ tid ], aggregate_column, filter_result_masks[ tid ]
            );
            results3_from_queries->data_ptr[ tid ] = aggregation_result_cols3[ tid ]->data_ptr[ 0 ];
         };
         
         auto metamagic = [ &ready_future, &finished, &magic1, &magic2, &magic3, &global_query_counter ] ( const size_t tid, const size_t column_id ) {
            size_t pos = tid;
            ready_future.wait();
            while ( !finished ) {
               magic1( tid, column_id, pos );
               ++global_query_counter[ tid ];
               magic1( tid, column_id, pos );
               ++global_query_counter[ tid ];
               magic2( tid, column_id, pos );
               ++global_query_counter[ tid ];
               magic3( tid, column_id, pos );
               ++global_query_counter[ tid ];
               pos += ThreadCount;
            }
         };
         
         std::size_t column_id = 0;
         std::vector <std::thread> pool;
         for(
            std::size_t            tid       = 0; tid < ThreadCount; ++tid
            ) {
            cpu_set_t cpuset;
            CPU_ZERO(&cpuset);
#ifdef CPU_PINNING_DENSE
            #ifdef KNL
                  CPU_SET( ( (tid*68)%271 ), &cpuset );
   #elif defined(XEON)
                  CPU_SET( ( (tid*12)%23 ), &cpuset );
   #else
                  CPU_SET( tid, &cpuset );
   #endif
#elif defined(CPU_PINNING_LOOSE)
            CPU_SET( tid, &cpuset );
#else
            static_assert(false, "No Pinning strategy defined.");
#endif
            // Parallelize
            pool.emplace_back( std::thread( metamagic, tid, column_id ) );
            int rc = pthread_setaffinity_np(pool[tid].native_handle(), sizeof(cpu_set_t), &cpuset);
            if (rc != 0) {
               std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
            }
            if( ( ( tid + 1 ) % ( ThreadCount / ColumnCount ) == 0 ) ) {
               ++column_id;
               if( column_id >= ColumnCount ) {
                  column_id = 0;
               }
            }
         }
         using namespace std::chrono_literals;
         cpu_freq_monitor::instance()->init(
            ThreadCount, (std::chrono::milliseconds( EXPERIMENT_THROUGHPUT_TIME_SLOT ) / cpu_freq_monitor::instance()
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
            std::size_t i                = 0; i < ThreadCount; ++i
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
            std::size_t i                = 0; i < ThreadCount; ++i
            ) {
            aggregated_result ^= results3_from_queries->data_ptr[ i ] ^ results2_from_queries->data_ptr[ i ] ^ results1_from_queries->data_ptr[ i ];
         }

         experiment_query_11_12<
            VectorExtension, ColumnCount,
            QueryCount_t::value, 0, QueryCount2ndStageOp2,
            QueryCount2ndStageOp3
         >::print_experiment_result(
            0, datagenerator, "SISQ-PAR-Budget", "BITMASK", "SEQ",
            executed_queries, EXPERIMENT_THROUGHPUT_THREAD_BUDGET, start_interval,
            start_interval,  start_interval, end_interval, time_elapsed_ns( start_interval,
                                                                            end_interval ), "", 0,
                                                                            results1_from_queries,
            results2_from_queries, results3_from_queries
         );

         for( std::size_t query_id = 0; query_id < ThreadCount; ++query_id ) {
            destroy_column( filter_result_masks[ query_id ] );
            destroy_column( aggregation_result_cols1[ query_id ] );
            destroy_column( aggregation_result_cols2[ query_id ] );
            destroy_column( aggregation_result_cols3[ query_id ] );
         }
         destroy_column( results3_from_queries );
         destroy_column( results2_from_queries );
         destroy_column( results1_from_queries );
      }
      
   };
}
#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SEQ_PARALLEL_TPUT_H
