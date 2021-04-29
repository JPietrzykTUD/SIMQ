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
#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_H

#include <benchmarks/queries/q11/query11_data.h>
#include <benchmarks/queries/data/measurement_helper.h>
namespace tuddbs {
   template<
      class VectorExtension,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize
   >
   struct sequential_wl_q11 {
      template<
         std::size_t BS = BatchSize,
         typename std::enable_if< BS == 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
      ) {
         using T = typename VectorExtension::base_t;
         
         std::size_t const data_count = datagenerator->data_size / sizeof( T );

#ifdef HAS_MCD
         column< T > * const results_from_queries =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value, false );
         results_from_queries->init(0);
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count, false );
         column< T > * const aggregation_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value, false );
#else
         column <T> * const results_from_queries =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         results_from_queries->init( 0 );
         column <T> * const filter_result_bitmask     = create_bitmask( T, data_count );
         column <T> * const aggregation_result_column =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
#endif
         for(
            std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep
            ) {
            filter_result_bitmask->init( 0 );
            aggregation_result_column->init( 0 );
            std::size_t column_id = 0;
            
            auto           dummy              = cache_flusher::instance( )->flush( );
            auto           start_simq_builder = now( );
            auto           start              = now( );
            for(
               std::size_t query_id           = 0; query_id < QueryCount; ++query_id
               ) {
               column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
               column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               T predicate = datagenerator->predicates[ query_id ];
               
               sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                  filter_result_bitmask, filter_column, broadcast< VectorExtension >( predicate )
               );
               sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
                  aggregation_result_column, aggregate_column, filter_result_bitmask
               );
               results_from_queries->data_ptr[ query_id ] = aggregation_result_column->data_ptr[ 0 ];
               
               if( ( ( query_id + 1 ) % ( QueryCount / ColumnCount ) == 0 ) ) {
                  ++column_id;
               }
            }
            auto end = now( );
            experiment_query_11_12< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
               rep, datagenerator, "SISQ", "BITMASK", "SEQ", QueryCount, 1,
               start_simq_builder, start_simq_builder, start, end,  time_elapsed_ns( start, end ),
               "", dummy, results_from_queries
            );
         }
         destroy_column( aggregation_result_column );
         destroy_column( filter_result_bitmask );
         destroy_column( results_from_queries );
      }
      
      template<
         std::size_t BS = BatchSize,
         typename std::enable_if< BS != 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
      ) {
         using T = typename VectorExtension::base_t;
         
         std::size_t const data_count = datagenerator->data_size / sizeof( T );

#ifdef HAS_MCD
         column< T > * const results_from_queries =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value, false );
         results_from_queries->init(0);
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count, false );
         column< T > * const aggregation_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value, false );
#else
         column <T> * const results_from_queries =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         results_from_queries->init( 0 );
         column <T> * const filter_result_bitmask     = create_bitmask( T, data_count );
         column <T> * const aggregation_result_column =
                       create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
#endif
         std::size_t const BatchCount = BatchSize / sizeof( T );
         
         for(
            std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep
            ) {
            filter_result_bitmask->init( 0 );
            aggregation_result_column->init( 0 );
            std::size_t column_id = 0;
            
            auto           dummy              = cache_flusher::instance( )->flush( );
            auto           start_simq_builder = now( );
            auto           start              = now( );
            for(
               std::size_t query_id           = 0; query_id < QueryCount; ++query_id
               ) {
               column <T> * const filter_column    = datagenerator->filter_columns[ column_id ];
               column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               T * filter_column_ptr    = filter_column->data_ptr;
               T * aggregate_column_ptr = aggregate_column->data_ptr;
               T predicate = datagenerator->predicates[ query_id ];
               
               typename VectorExtension::mask_t
                                                * filter_result_bitmask_ptr =
                  ( typename VectorExtension::mask_t * ) ( filter_result_bitmask->data_ptr );
               typename VectorExtension::mask_t * filter_result_bitmask_ptr_new;
               aggregation_result_column->init( 0 );
               T * aggregation_result_column_ptr = aggregation_result_column->data_ptr;
               T * const filter_column_ptr_end = filter_column->data_ptr + filter_column->data_count;
               
               while( filter_column_ptr != filter_column_ptr_end ) {
                  filter_result_bitmask_ptr_new =
                     sequential_filter_impl< VectorExtension, point_filter_lt_core >::apply(
                        filter_result_bitmask_ptr, filter_column_ptr, BatchCount,
                        broadcast< VectorExtension >( predicate )
                     );
                  sequential_aggregate_impl< VectorExtension, aggregate_mask_add >::apply(
                     aggregation_result_column_ptr, aggregate_column_ptr, BatchCount, filter_result_bitmask_ptr
                  );
                  filter_result_bitmask_ptr = filter_result_bitmask_ptr_new;
                  
               }
               results_from_queries->data_ptr[ query_id ] = aggregation_result_column->data_ptr[ 0 ];
               
               if( ( ( query_id + 1 ) % ( QueryCount / ColumnCount ) == 0 ) ) {
                  ++column_id;
               }
            }
            auto end = now( );
            experiment_query_11_12< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
               rep, datagenerator, "SISQ", "BITMASK", "SEQ", QueryCount, 1,
               start_simq_builder, start_simq_builder, start, end,  time_elapsed_ns( start, end ),
               "", dummy, results_from_queries
            );
         }
         destroy_column( aggregation_result_column );
         destroy_column( filter_result_bitmask );
         destroy_column( results_from_queries );
      }
   };
   
}

#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SEQ_H
