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

#include <benchmarks/queries/q11/query11_data.h>

namespace tuddbs {
   template<
      template< class, std::size_t, typename, class > class Strategy,
                                                      class VectorExtension,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize
   >
   struct simq_wl_q11_parallel {
      template<
         std::size_t BS = BatchSize,
         typename std::enable_if< BS == 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
      ) {
         using ThreadCount       = std::conditional_t<
            ( QueryCount > vector_constants_t< VectorExtension >::vector_element_count_t::value ),
            std::integral_constant<
               std::size_t,
               ( QueryCount / vector_constants_t< VectorExtension >::vector_element_count_t::value )
            >,
            std::integral_constant< std::size_t, 1 >
         >;
         
         using PackageQueryCount = std::conditional_t<
            (ThreadCount::value == 1 ),
            std::integral_constant< std::size_t, QueryCount >,
            std::integral_constant< std::size_t, vector_constants_t< VectorExtension >::vector_element_count_t::value >
         >;
         
         using T                 = typename VectorExtension::base_t;
         using column_array_t    = column_array< VectorExtension, ColumnCount >;
         using predicate_array_t = value_array< VectorExtension, QueryCount >;
         using svb_t             =
         simq_vector_builder_t<
            Strategy,
            column_array_t,
            QueryCount
         >;
         std::size_t const data_count = datagenerator->data_size / sizeof( T );
         
         column_array_t q11_filter_column_array;
         column_array_t q11_aggregate_column_array;
         for( std::size_t column_id = 0; column_id < ColumnCount; ++column_id ) {
            q11_filter_column_array.set( column_id, datagenerator->filter_columns[ column_id ] );
            q11_aggregate_column_array.set( column_id, datagenerator->aggregate_columns[ column_id ] );
         }
         predicate_array_t q11_predicates_array;
         for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
            q11_predicates_array.set( query_id, datagenerator->predicates[ query_id ] );
         }
         typename VectorExtension::vector_t predicate_vec =
            simq_value_vector_view_t< predicate_array_t, ColumnCount >::apply( q11_predicates_array );
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count * QueryCount );
         column< T > * const aggregation_result_column =
            create_column( T, vector_constants_t< VectorExtension >::vector_element_count_t::value );
         
         for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
            filter_result_bitmask->init( 0 );
            aggregation_result_column->init( 0 );
            
            auto dummy = cache_flusher::instance()->flush();
            auto start_simq_build = now();
            svb_t svb_filter( q11_filter_column_array );
            svb_t svb_aggregation( q11_aggregate_column_array );
            auto end_simq_build = now();
            
            auto start = now( );
            filter_impl< VectorExtension, svb_t, point_filter_lt_core >::apply(
               filter_result_bitmask, svb_filter, predicate_vec
            );
            aggregate_impl< VectorExtension, svb_t, aggregate_mask_add >::apply(
               aggregation_result_column, svb_aggregation, filter_result_bitmask
            );
            auto end = now( );
            [[maybe_unused]]typename VectorExtension::base_t * tmp = store< VectorExtension >(
               aggregation_result_column->data_ptr,
               aggregate_mask_add< VectorExtension >::template finalize< svb_t::lanes_per_query_t::value >(
                  load< VectorExtension >( aggregation_result_column->data_ptr )
               )
            );
            experiment_query11< VectorExtension, ColumnCount, QueryCount, BatchSize >::print_experiment_result(
               rep, datagenerator, "SIMQ", "BITMASK", Strategy< column_array_t, QueryCount,
                                                                typename VectorExtension::base_t, VectorExtension >::get_name( ),
               start_simq_build, end_simq_build, start, end, aggregation_result_column, dummy
            );
         }
         destroy_column( aggregation_result_column );
         destroy_column( filter_result_bitmask );
      }
      
   };
   
}
#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SIMQ_PARALLEL_H
