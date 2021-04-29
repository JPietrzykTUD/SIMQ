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
#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_DATA_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_DATA_H

#include <fstream>

namespace global {
   extern std::ofstream outputfile;
}

#include <data/column.h>
#include <data/container/column_array.h>

#include <simd/intrin.h>

#include <simq/control/vector_builder/vector_view.h>
#include <simq/control/vector_builder/vector_builder.h>
#include <simq/control/vector_builder/build_variants/buffer.h>
#include <simq/control/vector_builder/build_variants/gather.h>
#include <simq/control/vector_builder/build_variants/mask_broadcast.h>
#include <simq/control/vector_builder/build_variants/set.h>

#include <engine/operators/core/filter/point_filter_comparator_core.h>
#include <engine/operators/core/aggregate/aggregate_sum_core.h>
#include <engine/operators/core/aggregate/aggregate_min_core.h>
#include <engine/operators/core/aggregate/aggregate_max_core.h>

#include <engine/operators/bitmask_candidates/sequential/aggregate_bitmask_candidates.h>
#include <engine/operators/bitmask_candidates/sequential/filter_bitmask_candidates.h>

#include <engine/operators/bitmask_candidates/simq/aggregate_bitmask_candidates.h>
#include <engine/operators/bitmask_candidates/simq/filter_bitmask_candidates.h>

#include <utils/random.h>
#include <utils/clock.h>
#include <utils/helper.h>

#include <cstddef>
#include <iostream>

namespace tuddbs {
   
   template<
      typename T,
      std::size_t ColumnCount,
      std::size_t QueryCount
   >
   struct datagenerator_q11 {
      column <T> * filter_columns[ColumnCount];
      column <T> * aggregate_columns[ColumnCount];
      T           predicates[QueryCount];
      T           extended_predicates[1024];
      std::size_t results[QueryCount];
      std::size_t data_size;
      
      template<
         typename T1 = T,
         typename std::enable_if< sizeof( T1 ) <= 2, std::nullptr_t >::type = nullptr
      >
      void fill(
         column <T> * const filter_column,
         column <T> * const aggregate_column
      ) {
         /**
          * create filter data with the following pattern:
          * 2 * 0x0, 2 * 0x1, ... 2 * 0x40, data_count-128 * 0x80
          * This is shuffled.
          * Processing such a column with <64? will lead to a maximum of 128 hits.
          *
          * create sum data consisting of value 2.
          *
          * Thus <64? will lead to an aggregated sum of 256 ( = max. value of uint8_t )
          * query0( <1 ? ) => 2 values => sum = 4
          * query1( <2 ? ) => 4 values => sum = 8
          * query64( <64 ? ) => 128 values => sum = 256
          *
          */
         typename rng< T >::engine_t       engine( 0xC004C0FEEBADC0DE );
         std::size_t                       upper_limit = std::min(
            ( std::numeric_limits< T >::max( ) / ( 2 * QueryCount ) - 1 ),
            filter_column->data_count / ( 2 * QueryCount )
         );
         std::uniform_int_distribution <T> dist( 0, upper_limit );
         std::size_t                       rep         = dist( engine );
         filter_column->init( 128 );
         std::size_t    pos          = 0;
         std::size_t    result_carry = 0;
         for(
            std::size_t i            = 0; i < QueryCount; ++i
            ) {
            for(
               std::size_t j = 0; j < rep; ++j
               ) {
               filter_column->data_ptr[ pos++ ] = i;
            }
            results[ i ]     = result_carry + rep;
            result_carry += rep;
         }

//         std::cerr << "RESULTS SHOULD BE: \n";
//         std::cerr << " | ";
//         for( std::size_t i = 0; i < QueryCount; ++i ) {
//            std::cerr << results[ i ] << " | ";
//         }
//         std::cerr << "\n";
         std::shuffle( filter_column->data_ptr, filter_column->data_ptr + ( filter_column->data_count ), engine );
         aggregate_column->init( 1 );
      }
      
      template<
         typename T1 = T,
         typename std::enable_if< ( sizeof( T1 ) > 2 ), std::nullptr_t >::type = nullptr
      >
      void fill(
         column <T> * const filter_column,
         column <T> * const aggregate_column
      ) {
         typename rng< T >::engine_t       engine( 0xC004C0FEEBADC0DE );
         std::size_t                       upper_limit = std::min(
            ( std::numeric_limits< uint16_t >::max( ) / ( 2 * QueryCount ) - 1 ),
            filter_column->data_count / ( 2 * QueryCount )
         );
         std::uniform_int_distribution <T> dist( 0, upper_limit );
         std::size_t                       rep         = dist( engine );
         filter_column->init( 0 );
         std::size_t    pos = 0;
         for(
            std::size_t i   = 0; i < QueryCount; ++i
            ) {
            for(
               std::size_t j = 0; j < rep; ++j
               ) {
               filter_column->data_ptr[ pos++ ] = i;
            }
         }
         std::shuffle( filter_column->data_ptr, filter_column->data_ptr + ( filter_column->data_count ), engine );
         aggregate_column->init( 1 );
      }
      
      datagenerator_q11( std::size_t data_size ) :
         data_size{ data_size } {
         {
            typename rng< T >::engine_t       engine( 0xC004C0FEEBADC0DE );
            std::size_t                       upper_limit = 100;
            std::uniform_int_distribution <T> dist( 0, upper_limit );
            for(
               std::size_t                    i           = 0; i < 1024; ++i
               ) {
               extended_predicates[ i ] = dist( engine );
            }
         }
         
         std::size_t const data_count = data_size / sizeof( T );
         for(
            std::size_t    column_id  = 0; column_id < ColumnCount; ++column_id
            ) {
#ifdef HAS_MCD
            auto filter_column = create_column( T, data_count, false );
            auto aggregate_column = create_column( T, data_count, false );
#else
            auto filter_column    = create_column( T, data_count );
            auto aggregate_column = create_column( T, data_count );
#endif
            fill( filter_column, aggregate_column );
            filter_columns[ column_id ]    = filter_column;
            aggregate_columns[ column_id ] = aggregate_column;
         }
         for(
            std::size_t    query_id   = 0; query_id < QueryCount; ++query_id
            ) {
            predicates[ query_id ] = query_id + 1;
         }
      }
      
      ~datagenerator_q11( ) {
         for(
            std::size_t column_id = ColumnCount; column_id > 0; --column_id
            ) {
            destroy_column( aggregate_columns[ column_id - 1 ] );
            destroy_column( filter_columns[ column_id - 1 ] );
         }
      }
      
   };
   
   void q11_header( void ) {
      global::outputfile << "rep;"
                         << "data_count;"
                         << "data_size;"
                         << "vector_extension_name;"
                         << "data_type;"
                         << "workload_processing_name;"
                         << "intermediate_format;"
                         << "build_variant_name;"
                         << "column_count;"
                         << "query_count;"
                         << "query_processing_variant_name;"
                         << "batch_size;"
                         << "simq_build_time_ns;"
                         << "execution_time_ns;"
                         << "result;"
                         << "dummy;"
                         << "multithread_total_cpu_time_ns\n";
   }
   
   template<
      class VectorExtension,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize
   >
   struct experiment_query11 {
      static void print_experiment_result(
         std::size_t const rep,
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator,
         std::string variant_name,
         std::string intermediate_name,
         std::string build_name,
         std::chrono::time_point <std::chrono::high_resolution_clock> start_simq_build,
         std::chrono::time_point <std::chrono::high_resolution_clock> end_simq_build,
         std::chrono::time_point <std::chrono::high_resolution_clock> start,
         std::chrono::time_point <std::chrono::high_resolution_clock> end,
         column< typename VectorExtension::base_t > * const aggregation_result_column,
         uint64_t const flush_dummy,
         double total_cpu_time = 0.0
      ) {
         global::outputfile << rep << ";"
                            << datagenerator->data_size / sizeof( typename VectorExtension::base_t ) << ";"
                            << datagenerator->data_size << ";"
                            << vec_ext_to_string_t< VectorExtension >::apply( ) << ";"
                            << variant_name << ";"
                            << intermediate_name << ";"
                            << build_name << ";"
                            << ColumnCount << ";"
                            << QueryCount << ";";
         if( BatchSize == 0 ) {
            global::outputfile << "Operator at a Time;";
         } else {
            global::outputfile << "Batch at a Time;";
         }
         global::outputfile << BatchSize << ";"
                            << time_elapsed_ns( start_simq_build, end_simq_build ) << ";"
                            << time_elapsed_ns( start, end ) << ";"
                            << " | ";
         for(
            std::size_t query_id = 0; query_id < QueryCount; ++query_id
            ) {
            global::outputfile << ( uint64_t ) aggregation_result_column->data_ptr[ query_id ] << " | ";
         }
         global::outputfile << ";" << flush_dummy << ";";
         if( total_cpu_time == 0.0 ) {
            global::outputfile << time_elapsed_ns( start, end ) + time_elapsed_ns( start_simq_build, end_simq_build );
         } else {
            global::outputfile << total_cpu_time;
         }
         global::outputfile << "\n";
      }
   };
   
   void q11_mt_qtp_header( void ) {
      global::outputfile << "rep;"
                         << "data_count;"
                         << "data_size;"
                         << "vector_extension_name;"
                         << "data_type;"
                         << "workload_processing_name;"
                         << "intermediate_format;"
                         << "build_variant_name;"
                         << "column_count;"
                         << "query_count;"
                         << "query_processing_variant_name;"
                         << "batch_size;"
                         << "execution_time_ns;"
                         << "finished_queries;"
                         << "result\n";
   }
   
   /**
    * @brief Single Thread vs Multithread
    * @tparam VectorExtension
    * @tparam ColumnCount
    * @tparam QueryCount
    * @tparam BatchSize
    */
   template<
      class VectorExtension,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize
   >
   struct experiment_query11_mt_qtp {
      static void print_experiment_result(
         std::size_t const rep,
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator,
         std::string variant_name,
         std::string intermediate_name,
         std::string build_name,
         std::chrono::time_point <std::chrono::high_resolution_clock> start,
         std::chrono::time_point <std::chrono::high_resolution_clock> end,
         std::size_t executed_queries,
         std::size_t thread_count,
         typename VectorExtension::base_t result
      ) {
         global::outputfile << rep << ";"
                            << datagenerator->data_size / sizeof( typename VectorExtension::base_t ) << ";"
                            << datagenerator->data_size << ";"
                            << vec_ext_to_string_t< VectorExtension >::apply( ) << ";"
                            << variant_name << ";"
                            << intermediate_name << ";"
                            << build_name << ";"
                            << ColumnCount << ";"
                            << QueryCount << ";";
         if( BatchSize == 0 ) {
            global::outputfile << "Operator at a Time;";
         } else {
            global::outputfile << "Batch at a Time;";
         }
         global::outputfile << BatchSize << ";"
                            << time_elapsed_ns( start, end ) << ";"
                            << executed_queries << ";"
                            << thread_count << ";"
                            << result << "\n";
      }
   };
   
}

#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_DATA_H
