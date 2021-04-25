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
#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SIMQ_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SIMQ_H

#include <benchmarks/queries/q11/query11_data.h>
#include <benchmarks/queries/q12/query12_data.h>

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
      std::size_t ColumnCount = 1
   >
   struct simq_wl_q12_one_Stage2_ops {
      using QueryCount_t = std::integral_constant< std::size_t,
                                                   QueryCount2ndStageOp1 >;
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         using T                 = typename VectorExtension::base_t;
         using column_array_t    = column_array< VectorExtension, ColumnCount >;
         using predicate_array_t = value_array< VectorExtension, QueryCount_t::value >;
         using svbFirstStage_t =
         simq_vector_builder_t<
            Strategy,
            column_array_t,
            QueryCount_t::value
         >;
         using svbSecondStageOp1_t =
         simq_vector_builder_t<
            Strategy,
            column_array_t,
            QueryCount2ndStageOp1
         >;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
         column_array_t q12_filter_column_array;
         column_array_t q12_aggregate1_column_array;
         
         for( std::size_t column_id = 0; column_id < ColumnCount; ++column_id ) {
            q12_filter_column_array.set( column_id, datagenerator->filter_columns[ column_id ] );
            q12_aggregate1_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
         }
         
         predicate_array_t q12_predicates_array;
         for( std::size_t query_id = 0; query_id < QueryCount_t::value; ++query_id ) {
            q12_predicates_array.set( query_id, datagenerator->predicates[ query_id ] );
         }
         
         typename VectorExtension::vector_t predicate_vec =
            simq_value_vector_view_t< predicate_array_t, ColumnCount >::apply( q12_predicates_array );
         
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count * QueryCount_t::value );
         column< T > * const aggregation1_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );

         for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
            filter_result_bitmask->init( 0 );
            aggregation1_result_column->init( 0 );
            
            auto dummy = cache_flusher::instance()->flush();
            auto start_simq_build = now();
            svbFirstStage_t svb_filter( q12_filter_column_array );
            svbSecondStageOp1_t svb_aggregation1( q12_aggregate1_column_array );
            auto end_simq_build = now();
            
            auto start = now( );
            filter_impl< VectorExtension, svbFirstStage_t, point_filter_lt_core >::apply(
               filter_result_bitmask, svb_filter, predicate_vec
            );
            aggregate_impl< VectorExtension, svbSecondStageOp1_t, aggregate_mask_add, QueryCount2ndStageOp1 >::apply(
               aggregation1_result_column, svb_aggregation1, filter_result_bitmask
            );
            auto end = now( );
            [[maybe_unused]]typename VectorExtension::base_t * tmp1 = store< VectorExtension >(
               aggregation1_result_column->data_ptr,
               aggregate_mask_add< VectorExtension >::template finalize< svbSecondStageOp1_t::lanes_per_query_t::value >(
                  load< VectorExtension >( aggregation1_result_column->data_ptr )
               )
            );
            experiment_query12<
               VectorExtension,
               QueryCount2ndStageOp1,
               0,
               0,
               ColumnCount
            >::print_experiment_result(
               rep, datagenerator, "SIMQ", "BITMASK",
               Strategy<
                  column_array_t, QueryCount_t::value,
                  typename VectorExtension::base_t, VectorExtension
               >::get_name( ),
               start_simq_build, end_simq_build, start, end, dummy,
               aggregation1_result_column, nullptr, nullptr
            );
         }
         destroy_column( aggregation1_result_column );
         destroy_column( filter_result_bitmask );
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
      std::size_t ColumnCount = 1
   >
   struct simq_wl_q12_two_Stage2_ops {
      using QueryCount_t = std::integral_constant< std::size_t,
                                                   QueryCount2ndStageOp1+QueryCount2ndStageOp2 >;
      using BitCount2ndStageOp1 = std::integral_constant< std::size_t,
         vector_constants_t< VectorExtension >::vector_element_count_t::value / QueryCount2ndStageOp1 >;
      using BitCount2ndStageOp2 = std::integral_constant< std::size_t,
          vector_constants_t< VectorExtension >::vector_element_count_t::value / QueryCount2ndStageOp2 >;
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         using T                 = typename VectorExtension::base_t;
         using column_array_t    = column_array< VectorExtension, ColumnCount >;
         using predicate_array_t = value_array< VectorExtension, QueryCount_t::value >;
         using svbFirstStage_t =
         simq_vector_builder_t<
            Strategy,
            column_array_t,
            QueryCount_t::value
         >;
         using svbSecondStageOp1_t =
         simq_vector_builder_t<
            Strategy,
            column_array_t,
            QueryCount2ndStageOp1
         >;
         using svbSecondStageOp2_t =
         simq_vector_builder_t<
            Strategy,
            column_array_t,
            QueryCount2ndStageOp2
         >;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
         column_array_t q12_filter_column_array;
         column_array_t q12_aggregate1_column_array;
         column_array_t q12_aggregate2_column_array;
         
         for( std::size_t column_id = 0; column_id < ColumnCount; ++column_id ) {
            q12_filter_column_array.set( column_id, datagenerator->filter_columns[ column_id ] );
            q12_aggregate1_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
            q12_aggregate2_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
         }
         
         predicate_array_t q12_predicates_array;
         for( std::size_t query_id = 0; query_id < QueryCount_t::value; ++query_id ) {
            q12_predicates_array.set( query_id, datagenerator->predicates[ query_id ] );
         }
         
         typename VectorExtension::vector_t predicate_vec =
            simq_value_vector_view_t< predicate_array_t, ColumnCount >::apply( q12_predicates_array );
         
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count * QueryCount_t::value );
         column< T > * const aggregation1_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         column< T > * const aggregation2_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         
         for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
            filter_result_bitmask->init( 0 );
            aggregation1_result_column->init( 0 );
            aggregation2_result_column->init( 0 );
            
            auto dummy = cache_flusher::instance()->flush();
            auto start_simq_build = now();
            svbFirstStage_t svb_filter( q12_filter_column_array );
            svbSecondStageOp1_t svb_aggregation1( q12_aggregate1_column_array );
            svbSecondStageOp2_t svb_aggregation2( q12_aggregate2_column_array );
            auto end_simq_build = now();
            
            auto start = now( );
            filter_impl< VectorExtension, svbFirstStage_t, point_filter_lt_core >::apply(
               filter_result_bitmask, svb_filter, predicate_vec
            );
            aggregate_impl< VectorExtension, svbSecondStageOp1_t, aggregate_mask_add, BitCount2ndStageOp1::value
            >::apply(
               aggregation1_result_column, svb_aggregation1, filter_result_bitmask
            );
            aggregate_impl< VectorExtension, svbSecondStageOp2_t, aggregate_mask_add, BitCount2ndStageOp2::value,
            BitCount2ndStageOp1::value >::apply(
               aggregation2_result_column, svb_aggregation2, filter_result_bitmask
            );
            auto end = now( );
            print< VectorExtension >( std::cerr, load< VectorExtension >( aggregation1_result_column->data_ptr ), "Agg"
                                                                                                                  " 0");
            [[maybe_unused]]typename VectorExtension::base_t * tmp1 = store< VectorExtension >(
               aggregation1_result_column->data_ptr,
               aggregate_mask_add< VectorExtension >::template finalize< svbSecondStageOp1_t::lanes_per_query_t::value >(
                  load< VectorExtension >( aggregation1_result_column->data_ptr )
               )
            );
            print< VectorExtension >( std::cerr, load< VectorExtension >( aggregation2_result_column->data_ptr ), "Agg"
                                                                                                                  " 1");
            [[maybe_unused]]typename VectorExtension::base_t * tmp2 = store< VectorExtension >(
               aggregation2_result_column->data_ptr,
               aggregate_mask_add< VectorExtension >::template finalize<
                  svbSecondStageOp2_t::lanes_per_query_t::value >(
                  load< VectorExtension >( aggregation2_result_column->data_ptr )
               )
            );
            experiment_query12<
               VectorExtension,
               QueryCount2ndStageOp1,
               QueryCount2ndStageOp2,
               0,
               ColumnCount
            >::print_experiment_result(
               rep, datagenerator, "SIMQ", "BITMASK",
               Strategy<
                  column_array_t, QueryCount_t::value,
                  typename VectorExtension::base_t, VectorExtension
               >::get_name( ),
               start_simq_build, end_simq_build, start, end, dummy,
               aggregation1_result_column, aggregation2_result_column, nullptr
            );
         }
         destroy_column( aggregation2_result_column );
         destroy_column( aggregation1_result_column );
         destroy_column( filter_result_bitmask );
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
      std::size_t ColumnCount = 1
   >
   struct simq_wl_q12_three_Stage2_ops {
      using QueryCount_t = std::integral_constant< std::size_t,
         QueryCount2ndStageOp1+QueryCount2ndStageOp2+QueryCount2ndStageOp3 >;
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount_t::value > * const datagenerator
      ) {
         using T                 = typename VectorExtension::base_t;
         using column_array_t    = column_array< VectorExtension, ColumnCount >;
         using predicate_array_t = value_array< VectorExtension, QueryCount_t::value >;
         using svbFirstStage_t =
            simq_vector_builder_t<
               Strategy,
               column_array_t,
               QueryCount_t::value
            >;
         using svbSecondStageOp1_t =
            simq_vector_builder_t<
               Strategy,
               column_array_t,
               QueryCount2ndStageOp1
            >;
         using svbSecondStageOp2_t =
            simq_vector_builder_t<
               Strategy,
               column_array_t,
               QueryCount2ndStageOp2
            >;
         using svbSecondStageOp3_t =
            simq_vector_builder_t<
               Strategy,
               column_array_t,
               QueryCount2ndStageOp3
            >;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
         column_array_t q12_filter_column_array;
         column_array_t q12_aggregate1_column_array;
         column_array_t q12_aggregate2_column_array;
         column_array_t q12_aggregate3_column_array;
         
         for( std::size_t column_id = 0; column_id < ColumnCount; ++column_id ) {
            q12_filter_column_array.set( column_id, datagenerator->filter_columns[ column_id ] );
            q12_aggregate1_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
            q12_aggregate2_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
            q12_aggregate3_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
         }
         
         predicate_array_t q12_predicates_array;
         for( std::size_t query_id = 0; query_id < QueryCount_t::value; ++query_id ) {
            q12_predicates_array.set( query_id, datagenerator->predicates[ query_id ] );
         }
         
         typename VectorExtension::vector_t predicate_vec =
            simq_value_vector_view_t< predicate_array_t, ColumnCount >::apply( q12_predicates_array );

         column< T > * const filter_result_bitmask = create_bitmask( T, data_count * QueryCount_t::value );
         column< T > * const aggregation1_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         column< T > * const aggregation2_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         column< T > * const aggregation3_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         
         for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
            filter_result_bitmask->init( 0 );
            aggregation1_result_column->init( 0 );
            aggregation2_result_column->init( 0 );
            aggregation3_result_column->init( 0 );
            
            auto dummy = cache_flusher::instance()->flush();
            auto start_simq_build = now();
            svbFirstStage_t svb_filter( q12_filter_column_array );
            svbSecondStageOp1_t svb_aggregation1( q12_aggregate1_column_array );
            svbSecondStageOp2_t svb_aggregation2( q12_aggregate2_column_array );
            svbSecondStageOp3_t svb_aggregation3( q12_aggregate3_column_array );
            auto end_simq_build = now();
            
            auto start = now( );
            filter_impl< VectorExtension, svbFirstStage_t, point_filter_lt_core >::apply(
               filter_result_bitmask, svb_filter, predicate_vec
            );
            aggregate_impl< VectorExtension, svbSecondStageOp1_t, aggregate_mask_add, QueryCount2ndStageOp1 >::apply(
               aggregation1_result_column, svb_aggregation1, filter_result_bitmask
            );
            aggregate_impl< VectorExtension, svbSecondStageOp2_t, aggregate_mask_add, QueryCount2ndStageOp2, QueryCount2ndStageOp1 >::apply(
               aggregation2_result_column, svb_aggregation2, filter_result_bitmask
            );
            aggregate_impl< VectorExtension, svbSecondStageOp3_t, aggregate_mask_add, QueryCount2ndStageOp3,
            QueryCount2ndStageOp1+QueryCount2ndStageOp2 >::apply(
               aggregation3_result_column, svb_aggregation3, filter_result_bitmask
            );
            auto end = now( );
            [[maybe_unused]]typename VectorExtension::base_t * tmp1 = store< VectorExtension >(
               aggregation1_result_column->data_ptr,
               aggregate_mask_add< VectorExtension >::template finalize< svbSecondStageOp1_t::lanes_per_query_t::value >(
                  load< VectorExtension >( aggregation1_result_column->data_ptr )
               )
            );
            [[maybe_unused]]typename VectorExtension::base_t * tmp2 = store< VectorExtension >(
               aggregation2_result_column->data_ptr,
               aggregate_mask_add< VectorExtension >::template finalize<
                  svbSecondStageOp2_t::lanes_per_query_t::value >(
                  load< VectorExtension >( aggregation2_result_column->data_ptr )
               )
            );
            [[maybe_unused]]typename VectorExtension::base_t * tmp3 = store< VectorExtension >(
               aggregation3_result_column->data_ptr,
               aggregate_mask_add< VectorExtension >::template finalize<
                  svbSecondStageOp3_t::lanes_per_query_t::value >(
                  load< VectorExtension >( aggregation3_result_column->data_ptr )
               )
            );
            experiment_query12<
               VectorExtension,
               QueryCount2ndStageOp1,
               QueryCount2ndStageOp2,
               QueryCount2ndStageOp3,
               ColumnCount
            >::print_experiment_result(
               rep, datagenerator, "SIMQ", "BITMASK",
               Strategy<
                  column_array_t, QueryCount_t::value,
                  typename VectorExtension::base_t, VectorExtension
               >::get_name( ),
               start_simq_build, end_simq_build, start, end, dummy,
               aggregation1_result_column, aggregation2_result_column, aggregation3_result_column
            );
         }
         destroy_column( aggregation3_result_column );
         destroy_column( aggregation2_result_column );
         destroy_column( aggregation1_result_column );
         destroy_column( filter_result_bitmask );
      }
      
   };
   
}

#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_SIMQ_H
