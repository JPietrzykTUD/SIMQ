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
#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SCALAR_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SCALAR_H

#include <benchmarks/queries/q11/query11_data.h>

namespace tuddbs {
   template<
      typename T,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize
   >
   struct scalar_sequential_wl_q11 {
      template<
         std::size_t BS = BatchSize,
         typename std::enable_if< BS == 0, std::nullptr_t >::type = nullptr
      >
      static void run(
         datagenerator_q11< T, ColumnCount, QueryCount > * const datagenerator
      ) {
         std::size_t const step_width = (sizeof(T)*8);
         std::size_t const data_count = datagenerator->data_size / sizeof( T );

         column< T > * const results_from_queries =
            create_column( T, 64 );
         results_from_queries->init(0);
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count );
         column< T > * const aggregation_result_column =
            create_column( T, 64 );
         for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
            filter_result_bitmask->init( 0 );
            aggregation_result_column->init( 0 );
            std::size_t column_id = 0;

            auto dummy = cache_flusher::instance( )->flush( );
            auto start = now( );
               for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
                  column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
                  T * filter_ptr = filter_column->data_ptr;
                  T * filter_result_ptr = filter_result_bitmask->data_ptr;
                  column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
                  T * aggregate_ptr = aggregate_column->data_ptr;
                  T predicate = datagenerator->predicates[ query_id ];

                  for( std::size_t i = 0; i < data_count; i+=step_width ) {
                     T result_filter = 0;
                     for( std::size_t j = 0; j < step_width; ++j ) {
                        result_filter |= ( ( ( T )( *(filter_ptr++) < predicate ) ) << j );
                     }
                     *(filter_result_ptr++) = result_filter;
                  }

                  T result = 0;
                  filter_result_ptr = filter_result_bitmask->data_ptr;
                  for( std::size_t i = 0; i < data_count; i+=step_width ) {
                     T result_filter = *(filter_result_ptr++);
                     for( std::size_t j = 0; j < step_width; ++j ) {
                        result += ( *( aggregate_ptr++ ) & ( ~ ( ( result_filter & 0b1 ) - 1 ) ) );
                        result_filter >>= 1;
                     }
                  }

                  results_from_queries->data_ptr[ query_id ] = result;

                  if( ( ( query_id + 1 ) % ( QueryCount / ColumnCount ) == 0 )  ) {
                     ++column_id;
                  }
               }
            auto end = now( );
            global::outputfile << rep << ";"
                               << data_count << ";"
                               << data_count * sizeof( T ) << ";"
                               << "SCALAR;"
                               << sizeof( T ) * 8 << ";"
                               << "SISQ" << ";"
                               << "BITMASK" << ";"
                               << "SEQ" << ";"
                               << ColumnCount << ";"
                               << QueryCount << ";"
                               << "Operator at a Time;"
                               << BatchSize << ";"
                               << 0 << ";"
                               << time_elapsed_ns( start, end ) << ";"
                               << " | ";
            for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
               global::outputfile << ( uint64_t ) results_from_queries->data_ptr[ query_id ] << " | ";
            }
            global::outputfile << ";" << dummy << "\n";
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
         datagenerator_q11< T, ColumnCount, QueryCount > * const datagenerator
      ) {
         std::size_t const step_width = (sizeof(T)*8);
         std::size_t const data_count = datagenerator->data_size / sizeof( T );

         column< T > * const results_from_queries =
            create_column( T, 64 );
         results_from_queries->init(0);
         column< T > * const filter_result_bitmask = create_bitmask( T, data_count );
         column< T > * const aggregation_result_column =
            create_column( T, 64 );
         for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
            filter_result_bitmask->init( 0 );
            aggregation_result_column->init( 0 );
            std::size_t column_id = 0;

            auto dummy = cache_flusher::instance( )->flush( );
            auto start = now( );
            for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
               column <T> * const filter_column = datagenerator->filter_columns[ column_id ];
               T * filter_ptr = filter_column->data_ptr;
               T * filter_result_ptr = filter_result_bitmask->data_ptr;
               T * filter_result_aggregate_ptr = filter_result_ptr;
               column <T> * const aggregate_column = datagenerator->aggregate_columns[ column_id ];
               T * aggregate_ptr = aggregate_column->data_ptr;
               T predicate = datagenerator->predicates[ query_id ];
               T result = 0;
               for( std::size_t x = 0; x < data_count; x+=BatchSize ) {
                  for( std::size_t i = 0; i < BatchSize; i+=step_width ) {
                     T result_filter = 0;
                     for( std::size_t j = 0; j < step_width; ++j ) {
                        result_filter |= ( ( ( T )( *(filter_ptr++) < predicate ) ) << j );
                     }
                     *(filter_result_ptr++) = result_filter;
                  }

                  for( std::size_t i = 0; i < BatchSize; i+=step_width ) {
                     T result_filter = *(filter_result_aggregate_ptr++);
                     for( std::size_t j = 0; j < step_width; ++j ) {
                        result += ( *( aggregate_ptr++ ) & ( ~ ( ( result_filter & 0b1 ) - 1 ) ) );
                        result_filter >>= 1;
                     }
                  }
               }

               results_from_queries->data_ptr[ query_id ] = result;

               if( ( ( query_id + 1 ) % ( QueryCount / ColumnCount ) == 0 )  ) {
                  ++column_id;
               }
            }
            auto end = now( );
            global::outputfile << rep << ";"
                               << data_count << ";"
                               << data_count * sizeof( T ) << ";"
                               << "SCALAR;"
                               << sizeof( T ) * 8 << ";"
                               << "SISQ" << ";"
                               << "BITMASK" << ";"
                               << "SEQ" << ";"
                               << ColumnCount << ";"
                               << QueryCount << ";"
                               << "Batch at a Time;"
                               << BatchSize << ";"
                               << 0 << ";"
                               << time_elapsed_ns( start, end ) << ";"
                               << " | ";
            for( std::size_t query_id = 0; query_id < QueryCount; ++query_id ) {
               global::outputfile << ( uint64_t ) results_from_queries->data_ptr[ query_id ] << " | ";
            }
            global::outputfile << ";" << dummy << "\n";
         }
         destroy_column( aggregation_result_column );
         destroy_column( filter_result_bitmask );
         destroy_column( results_from_queries );
      }
   };

}

#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q11_QUERY11_SCALAR_H
