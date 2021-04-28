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

#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SEQ_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SEQ_H

#include <benchmarks/queries/q11/query11_data.h>
#include <benchmarks/queries/q12/query12_data.h>

namespace tuddbs {
   template<
      class VectorExtension,
      std::size_t QueryCount2ndStageOp1,
      std::size_t ColumnCount = 1
   >
   struct seq_wl_q12_one_Stage2_ops {
      using QueryCount_t = std::integral_constant< std::size_t,
                                                   QueryCount2ndStageOp1 >;
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         using T                 = typename VectorExtension::base_t;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
   
         column< T > * const results_from_queries =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         results_from_queries->init(0);
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count );
         column< T > * const aggregation_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
   
         for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
            filter_result_bitmask->init( 0 );
            aggregation_result_column->init( 0 );
            std::size_t column_id = 0;
      
            auto dummy = cache_flusher::instance( )->flush( );
            auto start_simq_builder = now( );
            auto start = now( );
            for( std::size_t query_id = 0; query_id < QueryCount_t::value; ++query_id ) {
               column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
               column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               T predicate = datagenerator->predicates[ query_id ];
         
               sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                  filter_result_bitmask, filter_column, broadcast< VectorExtension >( predicate )
               );
               sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
                  aggregation_result_column, aggregate_column, filter_result_bitmask
               );
               results_from_queries->data_ptr[ query_id ] = aggregation_result_column->data_ptr[ 0 ];
         
               if( ( ( query_id + 1 ) % ( QueryCount_t::value / ColumnCount ) == 0 )  ) {
                  ++column_id;
               }
            }
            auto end = now( );
            experiment_query12<
               VectorExtension,
               QueryCount2ndStageOp1,
               0,
               0,
               ColumnCount
            >::print_experiment_result(
               rep, datagenerator, "SISQ", "BITMASK", "SEQ",
               start_simq_builder, start_simq_builder, start, end, dummy,
               results_from_queries, nullptr, nullptr
            );
         }
         destroy_column( aggregation_result_column );
         destroy_column( filter_result_bitmask );
         destroy_column( results_from_queries );
      }
      
   };
   
   template<
      class VectorExtension,
      std::size_t QueryCount2ndStageOp1,
      std::size_t QueryCount2ndStageOp2,
      std::size_t ColumnCount = 1,
      std::size_t ColumnCount2ndStageOp1 = 1
   >
   struct seq_wl_q12_two_Stage2_ops {
      using QueryCount_t = std::integral_constant< std::size_t,
                                                   QueryCount2ndStageOp1+QueryCount2ndStageOp2 >;
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         using T                 = typename VectorExtension::base_t;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
         column< T > * const results1_from_queries =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         column< T > * const results2_from_queries =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         results1_from_queries->init(0);
         results2_from_queries->init(0);
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count );
         column< T > * const aggregation_result_column1 =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         column< T > * const aggregation_result_column2 =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         
         for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
            filter_result_bitmask->init( 0 );
            aggregation_result_column1->init( 0 );
            aggregation_result_column2->init( 0 );
            std::size_t column_id = 0;
            
            auto dummy = cache_flusher::instance( )->flush( );
            auto start_simq_builder = now( );
            auto start = now( );
            for( std::size_t query_id = 0; query_id < QueryCount2ndStageOp1; ++query_id ) {
               column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
               column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               T predicate = datagenerator->predicates[ query_id ];
               
               sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                  filter_result_bitmask, filter_column, broadcast< VectorExtension >( predicate )
               );
               sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
                  aggregation_result_column1, aggregate_column, filter_result_bitmask
               );
               results1_from_queries->data_ptr[ query_id ] = aggregation_result_column1->data_ptr[ 0 ];
               
               if( ( ( query_id + 1 ) % ( QueryCount_t::value / ColumnCount ) == 0 )  ) {
                  ++column_id;
               }
            }
            for( std::size_t query_id = 0; query_id < QueryCount2ndStageOp2; ++query_id ) {
               column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
               column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               T predicate = datagenerator->predicates[ query_id + QueryCount2ndStageOp1 ];
      
               sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                  filter_result_bitmask, filter_column, broadcast< VectorExtension >( predicate )
               );
               sequential_aggregate_impl< VectorExtension, aggregate_mask_min >::apply(
                  aggregation_result_column2, aggregate_column, filter_result_bitmask
               );
               results2_from_queries->data_ptr[ query_id ] = aggregation_result_column2->data_ptr[ 0 ];
      
               if( ( ( query_id + 1 ) % ( QueryCount_t::value / ColumnCount2ndStageOp1 ) == 0 )  ) {
                  ++column_id;
               }
            }
            auto end = now( );
            experiment_query12<
               VectorExtension,
               QueryCount2ndStageOp1,
               QueryCount2ndStageOp2,
               0,
               ColumnCount
            >::print_experiment_result(
               rep, datagenerator, "SISQ", "BITMASK", "SEQ",
               start_simq_builder, start_simq_builder, start, end, dummy,
               results1_from_queries, results2_from_queries, nullptr
            );
         }
         destroy_column( aggregation_result_column2 );
         destroy_column( aggregation_result_column1 );
         destroy_column( filter_result_bitmask );
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
   struct seq_wl_q12_three_Stage2_ops {
      using QueryCount_t = std::integral_constant< std::size_t,
                                                   QueryCount2ndStageOp1+QueryCount2ndStageOp2+QueryCount2ndStageOp3 >;
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         using T                 = typename VectorExtension::base_t;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
         column< T > * const results1_from_queries =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         column< T > * const results2_from_queries =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         column< T > * const results3_from_queries =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         results1_from_queries->init(0);
         results2_from_queries->init(0);
         results3_from_queries->init(0);
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count );
         column< T > * const aggregation_result_column1 =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         column< T > * const aggregation_result_column2 =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         column< T > * const aggregation_result_column3 =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         
         for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
            filter_result_bitmask->init( 0 );
            aggregation_result_column1->init( 0 );
            aggregation_result_column2->init( 0 );
            aggregation_result_column3->init( 0 );
            std::size_t column_id = 0;
            
            auto dummy = cache_flusher::instance( )->flush( );
            auto start_simq_builder = now( );
            auto start = now( );
            for( std::size_t query_id = 0; query_id < QueryCount2ndStageOp1; ++query_id ) {
               column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
               column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               T predicate = datagenerator->predicates[ query_id ];
               
               sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                  filter_result_bitmask, filter_column, broadcast< VectorExtension >( predicate )
               );
               sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
                  aggregation_result_column1, aggregate_column, filter_result_bitmask
               );
               results1_from_queries->data_ptr[ query_id ] = aggregation_result_column1->data_ptr[ 0 ];
               
               if( ( ( query_id + 1 ) % ( QueryCount_t::value / ColumnCount ) == 0 )  ) {
                  ++column_id;
               }
            }
            for( std::size_t query_id = 0; query_id < QueryCount2ndStageOp2; ++query_id ) {
               column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
               column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               T predicate = datagenerator->predicates[ query_id + QueryCount2ndStageOp1 ];
               
               sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                  filter_result_bitmask, filter_column, broadcast< VectorExtension >( predicate )
               );
               sequential_aggregate_impl< VectorExtension, aggregate_mask_min >::apply(
                  aggregation_result_column2, aggregate_column, filter_result_bitmask
               );
               results2_from_queries->data_ptr[ query_id ] = aggregation_result_column2->data_ptr[ 0 ];
               
               if( ( ( query_id + 1 ) % ( QueryCount_t::value / ColumnCount2ndStageOp1 ) == 0 )  ) {
                  ++column_id;
               }
            }
            for( std::size_t query_id = 0; query_id < QueryCount2ndStageOp3; ++query_id ) {
               column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
               column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               T predicate = datagenerator->predicates[ query_id + QueryCount2ndStageOp1 + QueryCount2ndStageOp2 ];
      
               sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                  filter_result_bitmask, filter_column, broadcast< VectorExtension >( predicate )
               );
               sequential_aggregate_impl< VectorExtension, aggregate_mask_max >::apply(
                  aggregation_result_column3, aggregate_column, filter_result_bitmask
               );
               results3_from_queries->data_ptr[ query_id ] = aggregation_result_column3->data_ptr[ 0 ];
      
               if( ( ( query_id + 1 ) % ( QueryCount_t::value / ColumnCount2ndStageOp2_3 ) == 0 )  ) {
                  ++column_id;
               }
            }
            auto end = now( );
            experiment_query12<
               VectorExtension,
               QueryCount2ndStageOp1,
               QueryCount2ndStageOp2,
               QueryCount2ndStageOp3,
               ColumnCount
            >::print_experiment_result(
               rep, datagenerator, "SISQ", "BITMASK", "SEQ",
               start_simq_builder, start_simq_builder, start, end, dummy,
               results1_from_queries, results2_from_queries, results3_from_queries
            );
         }
         destroy_column( aggregation_result_column3 );
         destroy_column( aggregation_result_column2 );
         destroy_column( aggregation_result_column1 );
         destroy_column( filter_result_bitmask );
         destroy_column( results3_from_queries );
         destroy_column( results2_from_queries );
         destroy_column( results1_from_queries );
      }
      
   };
}
#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SEQ_H
