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
#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SIMQ_PARALLEL_TPUT_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SIMQ_PARALLEL_TPUT_H

#ifndef EXPERIMENT_THROUGHPUT_TIME_SLOT
#define EXPERIMENT_THROUGHPUT_TIME_SLOT 30
#endif
#ifndef EXPERIMENT_THROUGHPUT_THREAD_BUDGET
#define EXPERIMENT_THROUGHPUT_THREAD_BUDGET 4
#endif

#include <benchmarks/queries/q11/query11_data.h>
#include <benchmarks/queries/data/measurement_helper.h>
#include <thread>
#include <future>
#include <atomic>
#include <utils/cpu_freq_monitor.h>

namespace tuddbs {
   
   
   /**
    * @brief Workload for different suboperators.
    * @details All Operators at a specific stage access the very same column -> Full-Columnsharing.
    * The Queries are:
    * Q1: [SELECT SUM(R.A) FROM R WHERE R.A < ?] * QueryCount2ndStageOp1
    * Q2: [SELECT MIN(R.A) FROM R WHERE R.A < ?] * QueryCount2ndStageOp2
    * Q3: [SELECT MAX(R.A) FROM R WHERE R.A < ?] * QueryCount2ndStageOp3
    * --> QueryCount1stStage = (QueryCount2ndStageOp1+QueryCount2ndStageOp2+QueryCount2ndStageOp3)
    * @tparam Strategy
    * @tparam VectorExtension
    * @tparam QueryCount2ndStageOp1
    * @tparam QueryCount2ndStageOp2
    * @tparam QueryCount2ndStageOp3
    */
   template<
      template< class, std::size_t, typename, class > class Strategy,
                                                      class VectorExtension,
      std::size_t QueryCount2ndStageOp1,
      std::size_t QueryCount2ndStageOp2,
      std::size_t ColumnCount = 1,
      std::size_t ColumnCount2ndStageOp1 = 1,
      std::size_t BatchSize = 0
   >
   struct simq_wl_q12_two_Stage2_ops_tput {
      using QueryCount_t = std::integral_constant<
         std::size_t,
         QueryCount2ndStageOp1 + QueryCount2ndStageOp2
      >;
      
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         using T = typename VectorExtension::base_t;
         using column_array_1st_stage_t = column_array< VectorExtension, ColumnCount >;
         using column_array_2nd_stage_t = column_array< VectorExtension, ColumnCount2ndStageOp1 >;
         using predicate_array_t = value_array< VectorExtension, QueryCount_t::value >;
         using svbFirstStage_t =
         simq_vector_builder_t<
            Strategy,
            column_array_1st_stage_t,
            QueryCount_t::value
         >;
         using svbSecondStageOp1_t =
         simq_vector_builder_t<
            Strategy,
            column_array_2nd_stage_t,
            QueryCount2ndStageOp1
         >;
         using svbSecondStageOp2_t =
         simq_vector_builder_t<
            Strategy,
            column_array_2nd_stage_t,
            QueryCount2ndStageOp2
         >;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
   
         std::vector < column < T > * > filter_result_masks;
         std::vector < column < T > * > aggregation1_result_cols;
         std::vector < column < T > * > aggregation2_result_cols;
         for(
            std::size_t tid           = 0; tid < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++tid
            ) {
            filter_result_masks.emplace_back( create_bitmask( T, data_count * QueryCount_t::value ) );
            aggregation1_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
            aggregation2_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
            filter_result_masks[ tid ]->init( 0 ); // make one per thread
            aggregation1_result_cols[ tid ]->init( 0 ); // make one per thread
            aggregation2_result_cols[ tid ]->init( 0 ); // make one per thread
         }
   
         std::array <std::atomic< std::size_t >, EXPERIMENT_THROUGHPUT_THREAD_BUDGET> global_query_counter = { };
         std::promise< void >       p;
         std::shared_future< void > ready_future( p.get_future( ) );
   
         bool finished = false;
   
         auto
            magic                      =
            [ &ready_future, &filter_result_masks, &aggregation1_result_cols, &aggregation2_result_cols,
              &global_query_counter, &datagenerator,
              &finished ](
               const size_t tid
            ) {
               ready_future.wait( );
               column_array_1st_stage_t q12_filter_column_array;
               column_array_2nd_stage_t q12_aggregate1_column_array;
               column_array_2nd_stage_t q12_aggregate2_column_array;
               for(
                  std::size_t    column_id = 0; column_id < ColumnCount; ++column_id
                  ) {
                  q12_filter_column_array.set( column_id, datagenerator->filter_columns[ column_id ] );
                  q12_aggregate1_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
                  q12_aggregate2_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
               }
               predicate_array_t q12_predicates_array;
               filter_result_masks[ tid ]->init( 0 ); // make one per thread
               aggregation1_result_cols[ tid ]->init( 0 ); // make one per thread
               aggregation2_result_cols[ tid ]->init( 0 ); // make one per thread
   
               size_t pos = 0;
               while( !finished ) {
                  pos                                              = 0;
                  for(
                     std::size_t                     query_id      = 0; query_id < QueryCount_t::value; ++query_id
                     ) {
                     q12_predicates_array.set( query_id, datagenerator->extended_predicates[ pos++ & 1023 ] );
                  }
                  typename VectorExtension::vector_t predicate_vec =
                                                        simq_value_vector_view_t<
                                                           predicate_array_t,
                                                           ColumnCount
                                                        >::apply( q12_predicates_array );
   
                  svbFirstStage_t     svb_filter( q12_filter_column_array );
                  svbSecondStageOp1_t svb_aggregation1( q12_aggregate1_column_array );
                  svbSecondStageOp2_t svb_aggregation2( q12_aggregate2_column_array );
                  filter_impl< VectorExtension, svbFirstStage_t, point_filter_lt_core >::apply(
                     filter_result_masks[ tid ], svb_filter, predicate_vec
                  );
                  aggregate_impl<
                     VectorExtension, svbSecondStageOp1_t, aggregate_mask_add, QueryCount2ndStageOp1
                  >::apply(
                     aggregation1_result_cols[ tid ], svb_aggregation1, filter_result_masks[ tid ]
                  );
                  [[maybe_unused]]typename VectorExtension::base_t * tmp1 = store< VectorExtension >(
                     aggregation1_result_cols[ tid ]->data_ptr,
                     aggregate_mask_add< VectorExtension >::template finalize< svbSecondStageOp1_t::lanes_per_query_t::value >(
                        load< VectorExtension >( aggregation1_result_cols[ tid ]->data_ptr )
                     )
                  );
                  global_query_counter[ tid ] += QueryCount2ndStageOp1;
                  aggregate_impl<
                     VectorExtension, svbSecondStageOp2_t, aggregate_mask_min, QueryCount2ndStageOp2,
                     QueryCount2ndStageOp1
                  >::apply(
                     aggregation2_result_cols[ tid ], svb_aggregation2, filter_result_masks[ tid ]
                  );
                  [[maybe_unused]]typename VectorExtension::base_t * tmp2 = store< VectorExtension >(
                     aggregation2_result_cols[ tid ]->data_ptr,
                     aggregate_mask_min< VectorExtension >::template finalize<
                        svbSecondStageOp2_t::lanes_per_query_t::value
                     >(
                        load< VectorExtension >( aggregation2_result_cols[ tid  ]->data_ptr )
                     )
                  );
                  global_query_counter[ tid ] += QueryCount2ndStageOp2;
               }
            };
         
         std::vector <std::thread> pool;
         for(
            std::size_t            tid = 0; tid < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++tid
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
   #ifdef XEON
               CPU_SET( (tid%23 ), &cpuset );
   #else
               CPU_SET( tid, &cpuset );
   #endif
#else
            static_assert(false, "No Pinning strategy defined.");
#endif
            // Parallelize
            pool.emplace_back( std::thread( magic, tid ) );
            int rc = pthread_setaffinity_np(pool[tid].native_handle(), sizeof(cpu_set_t), &cpuset);
            if (rc != 0) {
               std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
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
         while(
            std::chrono::duration_cast< std::chrono::seconds >( now( ) - start_interval ).count( )
            < EXPERIMENT_THROUGHPUT_TIME_SLOT
            ) {
            using namespace std::chrono_literals;
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
   
         experiment_query_11_12< VectorExtension, ColumnCount, QueryCount_t::value, BatchSize, QueryCount2ndStageOp2
         >::print_experiment_result(
            0, datagenerator, "SIMQ-PAR-Budget", "BITMASK", Strategy< column_array_1st_stage_t, QueryCount_t::value,
                                                           typename VectorExtension::base_t, VectorExtension
            >::get_name( ),
            executed_queries, EXPERIMENT_THROUGHPUT_THREAD_BUDGET, start_interval, start_interval, start_interval, end_interval,
            time_elapsed_ns( start_interval, end_interval ),
            cpu_freq_monitor::instance()->get_data(), 0, aggregation1_result_cols[0], aggregation2_result_cols[0]
         );
         for(
            std::size_t query_id = 0; query_id < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++query_id
            ) {
            destroy_column( filter_result_masks[ query_id ] );
            destroy_column( aggregation1_result_cols[ query_id ] );
            destroy_column( aggregation2_result_cols[ query_id ] );
         }
      }
   };
   
   /**
    * @brief Workload for different suboperators.
    * @details All Operators at a specific stage access the very same column -> Full-Columnsharing.
    * The Queries are:
    * Q1: [SELECT SUM(R.A) FROM R WHERE R.A < ?] * QueryCount2ndStageOp1
    * Q2: [SELECT MIN(R.A) FROM R WHERE R.A < ?] * QueryCount2ndStageOp2
    * Q3: [SELECT MAX(R.A) FROM R WHERE R.A < ?] * QueryCount2ndStageOp3
    * --> QueryCount1stStage = (QueryCount2ndStageOp1+QueryCount2ndStageOp2+QueryCount2ndStageOp3)
    * @tparam Strategy
    * @tparam VectorExtension
    * @tparam QueryCount2ndStageOp1
    * @tparam QueryCount2ndStageOp2
    * @tparam QueryCount2ndStageOp3
    */
   template<
      template< class, std::size_t, typename, class > class Strategy,
                                                      class VectorExtension,
      std::size_t QueryCount2ndStageOp1,
      std::size_t QueryCount2ndStageOp2,
      std::size_t QueryCount2ndStageOp3,
      std::size_t ColumnCount = 1,
      std::size_t ColumnCount2ndStageOp1 = 1,
      std::size_t ColumnCount2ndStageOp2_3 = 1,
      std::size_t BatchSize = 0
   >
   struct simq_wl_q12_three_Stage2_ops_tput {
      using QueryCount_t = std::integral_constant<
         std::size_t,
         QueryCount2ndStageOp1 + QueryCount2ndStageOp2 + QueryCount2ndStageOp3
      >;
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         
         using T = typename VectorExtension::base_t;
         using column_array_1st_stage_t = column_array< VectorExtension, ColumnCount >;
         using column_array_2nd_stage_op_1_t = column_array< VectorExtension, ColumnCount2ndStageOp1 >;
         using column_array_2nd_stage_op_2_3_t = column_array< VectorExtension, ColumnCount2ndStageOp2_3 >;
         using predicate_array_t = value_array< VectorExtension, QueryCount_t::value >;
         using svbFirstStage_t =
         simq_vector_builder_t<
            Strategy,
            column_array_1st_stage_t,
            QueryCount_t::value
         >;
         using svbSecondStageOp1_t =
         simq_vector_builder_t<
            Strategy,
            column_array_2nd_stage_op_1_t,
            QueryCount2ndStageOp1
         >;
         using svbSecondStageOp2_t =
         simq_vector_builder_t<
            Strategy,
            column_array_2nd_stage_op_2_3_t,
            QueryCount2ndStageOp2
         >;
         using svbSecondStageOp3_t =
         simq_vector_builder_t<
            Strategy,
            column_array_2nd_stage_op_2_3_t,
            QueryCount2ndStageOp3
         >;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
   
         std::vector < column < T > * > filter_result_masks;
         std::vector < column < T > * > aggregation1_result_cols;
         std::vector < column < T > * > aggregation2_result_cols;
         std::vector < column < T > * > aggregation3_result_cols;
         for(
            std::size_t tid           = 0; tid < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++tid
            ) {
            filter_result_masks.emplace_back( create_bitmask( T, data_count * QueryCount_t::value ) );
            aggregation1_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
            aggregation2_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
            aggregation3_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
            filter_result_masks[ tid ]->init( 0 ); // make one per thread
            aggregation1_result_cols[ tid ]->init( 0 ); // make one per thread
            aggregation2_result_cols[ tid ]->init( 0 ); // make one per thread
            aggregation3_result_cols[ tid ]->init( 0 ); // make one per thread
         }
   
         std::array <std::atomic< std::size_t >, EXPERIMENT_THROUGHPUT_THREAD_BUDGET> global_query_counter = { };
         std::promise< void >       p;
         std::shared_future< void > ready_future( p.get_future( ) );
   
         bool finished = false;
   
         auto
            magic                      =
            [ &ready_future, &filter_result_masks, &aggregation1_result_cols, &aggregation2_result_cols,
              &aggregation3_result_cols, &global_query_counter, &datagenerator,
              &finished ](
               const size_t tid
            ) {
               ready_future.wait( );
               column_array_1st_stage_t q12_filter_column_array;
               column_array_2nd_stage_op_1_t   q12_aggregate1_column_array;
               column_array_2nd_stage_op_2_3_t q12_aggregate2_column_array;
               column_array_2nd_stage_op_2_3_t q12_aggregate3_column_array;
               for(
                  std::size_t    column_id = 0; column_id < ColumnCount; ++column_id
                  ) {
                  q12_filter_column_array.set( column_id, datagenerator->filter_columns[ column_id ] );
               }
               for(
                  std::size_t    column_id = 0; column_id < ColumnCount2ndStageOp1; ++column_id
                  ) {
                  q12_aggregate1_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
               }
               for(
                  std::size_t    column_id = 0; column_id < ColumnCount2ndStageOp2_3; ++column_id
                  ) {
                  q12_aggregate2_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
                  q12_aggregate3_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
               }
               predicate_array_t q12_predicates_array;
               filter_result_masks[ tid ]->init( 0 ); // make one per thread
               aggregation1_result_cols[ tid ]->init( 0 ); // make one per thread
               aggregation2_result_cols[ tid ]->init( 0 ); // make one per thread
               aggregation3_result_cols[ tid ]->init( 0 ); // make one per thread
         
               size_t pos = 0;
               while( !finished ) {
                  pos                                              = 0;
                  for(
                     std::size_t                     query_id      = 0; query_id < QueryCount_t::value; ++query_id
                     ) {
                     q12_predicates_array.set( query_id, datagenerator->extended_predicates[ pos++ & 1023 ] );
                  }
                  typename VectorExtension::vector_t predicate_vec =
                                                        simq_value_vector_view_t<
                                                           predicate_array_t,
                                                           ColumnCount
                                                        >::apply( q12_predicates_array );
            
                  svbFirstStage_t     svb_filter( q12_filter_column_array );
                  svbSecondStageOp1_t svb_aggregation1( q12_aggregate1_column_array );
                  svbSecondStageOp2_t svb_aggregation2( q12_aggregate2_column_array );
                  svbSecondStageOp3_t svb_aggregation3( q12_aggregate3_column_array );
                  filter_impl< VectorExtension, svbFirstStage_t, point_filter_lt_core >::apply(
                     filter_result_masks[ tid ], svb_filter, predicate_vec
                  );
                  aggregate_impl<
                     VectorExtension, svbSecondStageOp1_t, aggregate_mask_add, QueryCount2ndStageOp1
                  >::apply(
                     aggregation1_result_cols[ tid ], svb_aggregation1, filter_result_masks[ tid ]
                  );
                  [[maybe_unused]]typename VectorExtension::base_t * tmp1 = store< VectorExtension >(
                     aggregation1_result_cols[ tid ]->data_ptr,
                     aggregate_mask_add< VectorExtension >::template finalize< svbSecondStageOp1_t::lanes_per_query_t::value >(
                        load< VectorExtension >( aggregation1_result_cols[ tid ]->data_ptr )
                     )
                  );
                  global_query_counter[ tid ] += QueryCount2ndStageOp1;
                  aggregate_impl<
                     VectorExtension, svbSecondStageOp2_t, aggregate_mask_min, QueryCount2ndStageOp2,
                     QueryCount2ndStageOp1
                  >::apply(
                     aggregation2_result_cols[ tid ], svb_aggregation2, filter_result_masks[ tid ]
                  );
                  [[maybe_unused]]typename VectorExtension::base_t * tmp2 = store< VectorExtension >(
                     aggregation2_result_cols[ tid ]->data_ptr,
                     aggregate_mask_min< VectorExtension >::template finalize<
                        svbSecondStageOp2_t::lanes_per_query_t::value
                     >(
                        load< VectorExtension >( aggregation2_result_cols[ tid  ]->data_ptr )
                     )
                  );
                  global_query_counter[ tid ] += QueryCount2ndStageOp2;
                  aggregate_impl<
                     VectorExtension, svbSecondStageOp3_t, aggregate_mask_max, QueryCount2ndStageOp3,
                     QueryCount2ndStageOp1 + QueryCount2ndStageOp2
                  >::apply(
                     aggregation3_result_cols[ tid ], svb_aggregation3, filter_result_masks[ tid ]
                  );
                  [[maybe_unused]]typename VectorExtension::base_t * tmp3 = store< VectorExtension >(
                     aggregation3_result_cols[ tid ]->data_ptr,
                     aggregate_mask_min< VectorExtension >::template finalize<
                        svbSecondStageOp2_t::lanes_per_query_t::value
                     >(
                        load< VectorExtension >( aggregation3_result_cols[ tid  ]->data_ptr )
                     )
                  );
                  global_query_counter[ tid ] += QueryCount2ndStageOp3;
               }
            };
   
         std::vector <std::thread> pool;
         for(
            std::size_t            tid = 0; tid < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++tid
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
   #ifdef XEON
               CPU_SET( (tid%23 ), &cpuset );
   #else
               CPU_SET( tid, &cpuset );
   #endif
#else
            static_assert(false, "No Pinning strategy defined.");
#endif
            // Parallelize
            pool.emplace_back( std::thread( magic, tid ) );
            int rc = pthread_setaffinity_np(pool[tid].native_handle(), sizeof(cpu_set_t), &cpuset);
            if (rc != 0) {
               std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
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
         while(
            std::chrono::duration_cast< std::chrono::seconds >( now( ) - start_interval ).count( )
            < EXPERIMENT_THROUGHPUT_TIME_SLOT
            ) {
            using namespace std::chrono_literals;
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
   
         experiment_query_11_12< VectorExtension, ColumnCount, QueryCount_t::value, BatchSize, QueryCount2ndStageOp2,
         QueryCount2ndStageOp3
         >::print_experiment_result(
            0, datagenerator, "SIMQ-PAR-Budget", "BITMASK", Strategy< column_array_1st_stage_t, QueryCount_t::value,
                                                           typename VectorExtension::base_t, VectorExtension
            >::get_name( ),
            executed_queries, EXPERIMENT_THROUGHPUT_THREAD_BUDGET, start_interval, start_interval, start_interval, end_interval,
            time_elapsed_ns( start_interval, end_interval ),
            cpu_freq_monitor::instance()->get_data(), 0, aggregation1_result_cols[0], aggregation2_result_cols[0],
            aggregation3_result_cols[0]
         );
         for(
            std::size_t query_id = 0; query_id < EXPERIMENT_THROUGHPUT_THREAD_BUDGET; ++query_id
            ) {
            destroy_column( filter_result_masks[ query_id ] );
            destroy_column( aggregation1_result_cols[ query_id ] );
            destroy_column( aggregation2_result_cols[ query_id ] );
            destroy_column( aggregation3_result_cols[ query_id ] );
         }
      }

   };

}

#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SIMQ_PARALLEL_TPUT_H
