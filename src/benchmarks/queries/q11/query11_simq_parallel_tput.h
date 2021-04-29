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

#ifndef EXPERIMENT_THROUGHPUT_TIME_SLOT
#define EXPERIMENT_THROUGHPUT_TIME_SLOT 30
#endif
#include <benchmarks/queries/q11/query11_data.h>
#include <benchmarks/queries/data/measurement_helper.h>
#include <thread>
#include <future>
#include <atomic>
#include <utils/cpu_freq_monitor.h>

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
         const size_t ThreadCount = 12;
         
         using T = typename VectorExtension::base_t;
         using column_array_t = column_array< VectorExtension, ColumnCount >;
         using predicate_array_t = value_array< VectorExtension, QueryCount >;
         using svb_t =
         simq_vector_builder_t<
            Strategy,
            column_array_t,
            QueryCount
         >;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
         std::vector < column < T > * > filter_result_masks;
         std::vector < column < T > * > aggregation_result_cols;
         for(
            std::size_t tid           = 0; tid < ThreadCount; ++tid
            ) {
            filter_result_masks.emplace_back( create_bitmask( T, data_count * QueryCount ) );
            aggregation_result_cols.emplace_back(
               create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value )
            );
            filter_result_masks[ tid ]->init( 0 ); // make one per thread
            aggregation_result_cols[ tid ]->init( 0 ); // make one per thread
         }
         
         std::array <std::atomic< std::size_t >, ThreadCount> global_query_counter = { };
         std::promise< void >       p;
         std::shared_future< void > ready_future( p.get_future( ) );
         
         bool finished = false;
         
         auto
            magic                      =
            [ &ready_future, &filter_result_masks, &aggregation_result_cols, &global_query_counter, &datagenerator, &finished ](
               const size_t tid
            ) {
               ready_future.wait( );
               column_array_t    q11_filter_column_array;
               column_array_t    q11_aggregate_column_array;
               for(
                  std::size_t    column_id = 0; column_id < ColumnCount; ++column_id
                  ) {
                  q11_filter_column_array.set( column_id, datagenerator->filter_columns[ column_id ] );
                  q11_aggregate_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
               }
               predicate_array_t q11_predicates_array;
               
               filter_result_masks[ tid ]->init( 0 ); // make one per thread
               aggregation_result_cols[ tid ]->init( 0 ); // make one per thread
               
               size_t pos = 0;
               while( !finished ) {
                  pos                                              = 0;
                  for(
                     std::size_t                     query_id      = 0; query_id < QueryCount; ++query_id
                     ) {
                     q11_predicates_array.set( query_id, datagenerator->extended_predicates[ pos++ & 1023 ] );
                  }
                  typename VectorExtension::vector_t predicate_vec =
                                                        simq_value_vector_view_t<
                                                           predicate_array_t,
                                                           ColumnCount
                                                        >::apply( q11_predicates_array );
                  svb_t svb_filter( q11_filter_column_array );
                  svb_t svb_aggregation( q11_aggregate_column_array );
                  
                  filter_impl< VectorExtension, svb_t, point_filter_lt_core >::apply(
                     filter_result_masks[ tid ], svb_filter, predicate_vec
                  );
                  aggregate_impl< VectorExtension, svb_t, aggregate_mask_add >::apply(
                     aggregation_result_cols[ tid ], svb_aggregation, filter_result_masks[ tid ]
                  );
                  
                  [[maybe_unused]]typename VectorExtension::base_t * tmp = store< VectorExtension >(
                     aggregation_result_cols[ tid ]->data_ptr,
                     aggregate_mask_add< VectorExtension >::template finalize< svb_t::lanes_per_query_t::value >(
                        load< VectorExtension >( aggregation_result_cols[ tid ]->data_ptr )
                     )
                  );
                  global_query_counter[ tid ] += QueryCount;
               }
            };
         
         std::vector <std::thread> pool;
         cpu_set_t cpuset;
         for(
            std::size_t            tid = 0; tid < ThreadCount; ++tid
            ) {
            CPU_ZERO(&cpuset);
            CPU_SET(tid, &cpuset);
            // Parallelize
            pool.emplace_back( std::thread( magic, tid ) );
            int rc = pthread_setaffinity_np(pool[tid].native_handle(), sizeof(cpu_set_t), &cpuset);
            if (rc != 0) {
               std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
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
         while(
            std::chrono::duration_cast< std::chrono::seconds >( now( ) - start_interval ).count( )
            < EXPERIMENT_THROUGHPUT_TIME_SLOT
            ) {
            using namespace std::chrono_literals;
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
            aggregated_result ^= aggregation_result_cols[i]->data_ptr[ 0 ];
         }

         experiment_query_11_12< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
            0, datagenerator, "SIMQ", "BITMASK", Strategy< column_array_t, QueryCount,
                                                           typename VectorExtension::base_t, VectorExtension
                                                           >::get_name( ),
            executed_queries, ThreadCount, start_interval, start_interval, start_interval, end_interval,
            time_elapsed_ns( start_interval, end_interval ),
            cpu_freq_monitor::instance()->get_data(), 0, aggregation_result_cols[0]
         );
         
         for(
            std::size_t query_id = 0; query_id < ThreadCount; ++query_id
            ) {
            destroy_column( filter_result_masks[ query_id ] );
            destroy_column( aggregation_result_cols[ query_id ] );
         }
      }
      
   };
   
}
#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SIMQ_PARALLEL_H
