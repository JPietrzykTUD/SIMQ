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


#include <iostream>
#include <random>
#include <cstdint>
#include <cstddef>
#include <data/column.h>
#include <simd/intrin.h>
#include <data/container/column_array.h>
#include <simq/control/vector_builder/vector_view.h>
#include <simq/control/vector_builder/vector_builder.h>
#include <simq/control/vector_builder/build_variants/buffer.h>
#include <simq/control/vector_builder/build_variants/mask_broadcast.h>
#include <simq/control/vector_builder/build_variants/set.h>
#include <simq/control/vector_builder/build_variants/gather.h>
#include <utils/clock.h>
#include <utils/definitions.h>
#include <utils/helper.h>
#include <utils/random.h>

template< class VectorExtension, std::size_t ColumnCount, std::size_t QueryCount >
void run_sequential( std::size_t data_size ) {
   using namespace tuddbs;
   using T = typename VectorExtension::base_t;
   std::size_t data_count = data_size / sizeof( T );
   typename rng< T >::engine_t engine( 0xC004C0FEEBADC0DE );
   std::uniform_int_distribution< T > dist(0, std::numeric_limits< T >::max() );

   column_array< VectorExtension, ColumnCount > mb_column_array;
   for( std::size_t i = 0; i < ColumnCount; ++i ) {
      auto column = create_column( T, data_count );
      T * data = column->data_ptr;
      for( std::size_t j = 0; j < data_count; ++j ) {
         data[ j ] = dist( engine );
      }
      mb_column_array.set( i, column );
   }
   T * output_buffer =
      ( T * ) acquire(
         sizeof( T ) * QueryCount,
         vector_constants_t< VectorExtension >::vector_alignment_byte_t::value
      );

   T * const output_buffer_orig = output_buffer;
   std::size_t data_count_vec = data_count / vector_constants_t< VectorExtension >::vector_element_count_t::value;
   for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
      output_buffer = output_buffer_orig;
      auto dummy = cache_flusher::instance()->flush();
      auto start = now( );
         for( std::size_t column_id = 0; column_id < ColumnCount; ++column_id ) {
            for( std::size_t query_id = 0; query_id < ( QueryCount / ColumnCount ); ++query_id ) {
               typename VectorExtension::vector_t result = set_zero< VectorExtension >( );
               typename vector_constants_t< VectorExtension >::array_t buff;
               column< T > * col = mb_column_array.columns[ column_id ];
               T * col_data = col->data_ptr;
               for( std::size_t i = 0; i < data_count_vec; ++i  ) {
                  result = bitwise_xor< VectorExtension >( result, load< VectorExtension >( col_data ) );
                  col_data += vector_constants_t< VectorExtension >::vector_element_count_t::value;
               }
               [[maybe_unused]] T * out_tmp = store< VectorExtension >( buff.data(), result );
               T tmp = 0;
               for( auto b : buff ) {
                  tmp ^= b;
               }
               *( output_buffer++ ) = tmp;
            }
         }
      auto end = now( );
      std::cout <<
                rep << ";" <<
                data_count << ";" <<
                data_size << ";" <<
                vec_ext_to_string_t< VectorExtension >::apply( ) << ";" <<
                "Sequential" << ";" <<
                ColumnCount << ";" <<
                QueryCount << ";" <<
                time_elapsed_ns( start, end ) << "; | ";
      for( std::size_t i = 0; i < QueryCount; ++i ) {
         std::cout << ( uint64_t ) output_buffer_orig[ i ] << " | ";
      }
      std::cout << ";" << dummy << "\n";
   }

   /**
    * Release used buffers.
    */
   release_ptr( output_buffer_orig );
   for( std::size_t i = 0; i < ColumnCount; ++i ) {
      destroy_column( mb_column_array.columns[ ColumnCount - 1 - i ] );
   }
}

template<
   template< class, std::size_t, typename, class > class Strategy,
   class VectorExtension,
   std::size_t ColumnCount,
   std::size_t QueryCount
>
void run_single_build_variant( std::size_t data_size ) {
   using namespace tuddbs;
   using T = typename VectorExtension::base_t;
   std::size_t data_count = data_size / sizeof( T );
   typename rng< T >::engine_t engine( 0xC004C0FEEBADC0DE );
   std::uniform_int_distribution< T > dist(0, std::numeric_limits< T >::max() );

   column_array< VectorExtension, ColumnCount > mb_column_array;
   for( std::size_t i = 0; i < ColumnCount; ++i ) {
      auto column = create_column( T, data_count );
      T * data = column->data_ptr;
      for( std::size_t j = 0; j < data_count; ++j ) {
         data[ j ] = dist( engine );
      }
      mb_column_array.set( i, column );
   }

   using svb_t =
   simq_vector_builder_t<
      Strategy,
      column_array< VectorExtension, ColumnCount >,
      QueryCount
   >;
   T * output_buffer =
      ( T * ) acquire(
         sizeof( T ) * QueryCount,
         vector_constants_t< VectorExtension >::vector_alignment_byte_t::value
      );
   T * const output_buffer_orig = output_buffer;
   for( std::size_t rep = 0; rep < EXPERIMENT_MEASUREMENT_REPETITION_COUNT; ++rep ) {
      output_buffer = output_buffer_orig;
      auto dummy = cache_flusher::instance()->flush();
      auto start = now( );
         svb_t svb( mb_column_array );
         std::size_t incrementor = svb_t::get_incrementor( );
         typename VectorExtension::vector_t result = set_zero< VectorExtension >( );
         for( std::size_t i = 0; i < data_count; i += incrementor ) {
            result = bitwise_xor< VectorExtension >( result, svb.get_and_increment( ) );
         }
         typename vector_constants_t< VectorExtension >::array_t buff;
         [[maybe_unused]] T * out_tmp = store< VectorExtension >( buff.data(), result );
         std::size_t lanes_per_query = vector_constants_t< VectorExtension >::vector_element_count_t::value / QueryCount;
         for( std::size_t i = 0; i < QueryCount; ++i ) {
            T result_of_query = 0;
            for( std::size_t j = 0; j < lanes_per_query; ++j ) {
               result_of_query ^= buff[ i * lanes_per_query + j ];
            }
            *( output_buffer++ ) = result_of_query;
         }
      auto end = now( );
      std::cout <<
                rep << ";" <<
                data_count << ";" <<
                data_size << ";" <<
                vec_ext_to_string_t< VectorExtension >::apply( ) << ";" <<
                Strategy<
                   column_array< VectorExtension, ColumnCount >,
                   QueryCount,
                   typename VectorExtension::base_t,
                   VectorExtension
                >::get_name() << ";" <<
                ColumnCount << ";" <<
                QueryCount << ";" <<
                time_elapsed_ns( start, end ) << "; | ";
      for( std::size_t i = 0; i < QueryCount; ++i ) {
         std::cout << ( uint64_t ) output_buffer_orig[ i ] << " | ";
      }
      std::cout << ";" << dummy << "\n";
      svb.reset();
   }

   release_ptr( output_buffer_orig );
   for( std::size_t i = 0; i < ColumnCount; ++i ) {
      destroy_column( mb_column_array.columns[ ColumnCount - 1 - i ] );
   }
}

template< class VectorExtension, std::size_t ColumnCount, std::size_t QueryCount >
void run_vector_extension( std::size_t data_size ) {
   using namespace tuddbs;
   run_sequential< VectorExtension, ColumnCount, QueryCount >( data_size );
   run_single_build_variant< simq_vector_builder_buffer_t, VectorExtension, ColumnCount, QueryCount >( data_size );
   run_single_build_variant< simq_vector_builder_mask_broadcast_t, VectorExtension, ColumnCount, QueryCount >( data_size );
   run_single_build_variant< simq_vector_builder_set_t, VectorExtension, ColumnCount, QueryCount >( data_size );
   if( sizeof( typename VectorExtension::base_t ) > 2 )
      run_single_build_variant< simq_vector_builder_gather_t, VectorExtension, ColumnCount, QueryCount >( data_size );
}

void run_benchmark_sse( std::size_t data_size ) {
   using namespace tuddbs;
   run_vector_extension< sse< uint8_t >, 1, 1 >( data_size );
   run_vector_extension< sse< uint8_t >, 1, 2 >( data_size );
   run_vector_extension< sse< uint8_t >, 2, 2 >( data_size );
   run_vector_extension< sse< uint8_t >, 1, 4 >( data_size );
   run_vector_extension< sse< uint8_t >, 2, 4 >( data_size );
   run_vector_extension< sse< uint8_t >, 4, 4 >( data_size );
   run_vector_extension< sse< uint8_t >, 1, 8 >( data_size );
   run_vector_extension< sse< uint8_t >, 2, 8 >( data_size );
   run_vector_extension< sse< uint8_t >, 4, 8 >( data_size );
   run_vector_extension< sse< uint8_t >, 8, 8 >( data_size );
   run_vector_extension< sse< uint8_t >, 1, 16 >( data_size );
   run_vector_extension< sse< uint8_t >, 2, 16 >( data_size );
   run_vector_extension< sse< uint8_t >, 4, 16 >( data_size );
   run_vector_extension< sse< uint8_t >, 8, 16 >( data_size );
   run_vector_extension< sse< uint8_t >, 16, 16 >( data_size );

   run_vector_extension< sse< uint16_t >, 1, 1 >( data_size );
   run_vector_extension< sse< uint16_t >, 1, 2 >( data_size );
   run_vector_extension< sse< uint16_t >, 2, 2 >( data_size );
   run_vector_extension< sse< uint16_t >, 1, 4 >( data_size );
   run_vector_extension< sse< uint16_t >, 2, 4 >( data_size );
   run_vector_extension< sse< uint16_t >, 4, 4 >( data_size );
   run_vector_extension< sse< uint16_t >, 1, 8 >( data_size );
   run_vector_extension< sse< uint16_t >, 2, 8 >( data_size );
   run_vector_extension< sse< uint16_t >, 4, 8 >( data_size );
   run_vector_extension< sse< uint16_t >, 8, 8 >( data_size );

   run_vector_extension< sse< uint32_t >, 1, 1 >( data_size );
   run_vector_extension< sse< uint32_t >, 1, 2 >( data_size );
   run_vector_extension< sse< uint32_t >, 2, 2 >( data_size );
   run_vector_extension< sse< uint32_t >, 1, 4 >( data_size );
   run_vector_extension< sse< uint32_t >, 2, 4 >( data_size );
   run_vector_extension< sse< uint32_t >, 4, 4 >( data_size );

   run_vector_extension< sse< uint64_t >, 1, 1 >( data_size );
   run_vector_extension< sse< uint64_t >, 1, 2 >( data_size );
   run_vector_extension< sse< uint64_t >, 2, 2 >( data_size );
}

void run_benchmark_avx2( std::size_t data_size ) {
   using namespace tuddbs;
   run_vector_extension< avx2< uint8_t >, 1, 1 >( data_size );
   run_vector_extension< avx2< uint8_t >, 1, 2 >( data_size );
   run_vector_extension< avx2< uint8_t >, 2, 2 >( data_size );
   run_vector_extension< avx2< uint8_t >, 1, 4 >( data_size );
   run_vector_extension< avx2< uint8_t >, 2, 4 >( data_size );
   run_vector_extension< avx2< uint8_t >, 4, 4 >( data_size );
   run_vector_extension< avx2< uint8_t >, 1, 8 >( data_size );
   run_vector_extension< avx2< uint8_t >, 2, 8 >( data_size );
   run_vector_extension< avx2< uint8_t >, 4, 8 >( data_size );
   run_vector_extension< avx2< uint8_t >, 8, 8 >( data_size );
   run_vector_extension< avx2< uint8_t >, 1, 16 >( data_size );
   run_vector_extension< avx2< uint8_t >, 2, 16 >( data_size );
   run_vector_extension< avx2< uint8_t >, 4, 16 >( data_size );
   run_vector_extension< avx2< uint8_t >, 8, 16 >( data_size );
   run_vector_extension< avx2< uint8_t >, 16, 16 >( data_size );
   run_vector_extension< avx2< uint8_t >, 1, 32 >( data_size );
   run_vector_extension< avx2< uint8_t >, 2, 32 >( data_size );
   run_vector_extension< avx2< uint8_t >, 4, 32 >( data_size );
   run_vector_extension< avx2< uint8_t >, 8, 32 >( data_size );
   run_vector_extension< avx2< uint8_t >, 16, 32 >( data_size );
   run_vector_extension< avx2< uint8_t >, 32, 32 >( data_size );

   run_vector_extension< avx2< uint16_t >, 1, 1 >( data_size );
   run_vector_extension< avx2< uint16_t >, 1, 2 >( data_size );
   run_vector_extension< avx2< uint16_t >, 2, 2 >( data_size );
   run_vector_extension< avx2< uint16_t >, 1, 4 >( data_size );
   run_vector_extension< avx2< uint16_t >, 2, 4 >( data_size );
   run_vector_extension< avx2< uint16_t >, 4, 4 >( data_size );
   run_vector_extension< avx2< uint16_t >, 1, 8 >( data_size );
   run_vector_extension< avx2< uint16_t >, 2, 8 >( data_size );
   run_vector_extension< avx2< uint16_t >, 4, 8 >( data_size );
   run_vector_extension< avx2< uint16_t >, 8, 8 >( data_size );
   run_vector_extension< avx2< uint16_t >, 1, 16 >( data_size );
   run_vector_extension< avx2< uint16_t >, 2, 16 >( data_size );
   run_vector_extension< avx2< uint16_t >, 4, 16 >( data_size );
   run_vector_extension< avx2< uint16_t >, 8, 16 >( data_size );
   run_vector_extension< avx2< uint16_t >, 16, 16 >( data_size );

   run_vector_extension< avx2< uint32_t >, 1, 1 >( data_size );
   run_vector_extension< avx2< uint32_t >, 1, 2 >( data_size );
   run_vector_extension< avx2< uint32_t >, 2, 2 >( data_size );
   run_vector_extension< avx2< uint32_t >, 1, 4 >( data_size );
   run_vector_extension< avx2< uint32_t >, 2, 4 >( data_size );
   run_vector_extension< avx2< uint32_t >, 4, 4 >( data_size );
   run_vector_extension< avx2< uint32_t >, 1, 8 >( data_size );
   run_vector_extension< avx2< uint32_t >, 2, 8 >( data_size );
   run_vector_extension< avx2< uint32_t >, 4, 8 >( data_size );
   run_vector_extension< avx2< uint32_t >, 8, 8 >( data_size );

   run_vector_extension< avx2< uint64_t >, 1, 1 >( data_size );
   run_vector_extension< avx2< uint64_t >, 1, 2 >( data_size );
   run_vector_extension< avx2< uint64_t >, 2, 2 >( data_size );
   run_vector_extension< avx2< uint64_t >, 1, 4 >( data_size );
   run_vector_extension< avx2< uint64_t >, 2, 4 >( data_size );
   run_vector_extension< avx2< uint64_t >, 4, 4 >( data_size );
}

void run_benchmark_avx512( std::size_t data_size ) {
   using namespace tuddbs;
   run_vector_extension< avx512< uint8_t >, 1, 1 >( data_size );
   run_vector_extension< avx512< uint8_t >, 1, 2 >( data_size );
   run_vector_extension< avx512< uint8_t >, 2, 2 >( data_size );
   run_vector_extension< avx512< uint8_t >, 1, 4 >( data_size );
   run_vector_extension< avx512< uint8_t >, 2, 4 >( data_size );
   run_vector_extension< avx512< uint8_t >, 4, 4 >( data_size );
   run_vector_extension< avx512< uint8_t >, 1, 8 >( data_size );
   run_vector_extension< avx512< uint8_t >, 2, 8 >( data_size );
   run_vector_extension< avx512< uint8_t >, 4, 8 >( data_size );
   run_vector_extension< avx512< uint8_t >, 8, 8 >( data_size );
   run_vector_extension< avx512< uint8_t >, 1, 16 >( data_size );
   run_vector_extension< avx512< uint8_t >, 2, 16 >( data_size );
   run_vector_extension< avx512< uint8_t >, 4, 16 >( data_size );
   run_vector_extension< avx512< uint8_t >, 8, 16 >( data_size );
   run_vector_extension< avx512< uint8_t >, 16, 16 >( data_size );
   run_vector_extension< avx512< uint8_t >, 1, 32 >( data_size );
   run_vector_extension< avx512< uint8_t >, 2, 32 >( data_size );
   run_vector_extension< avx512< uint8_t >, 4, 32 >( data_size );
   run_vector_extension< avx512< uint8_t >, 8, 32 >( data_size );
   run_vector_extension< avx512< uint8_t >, 16, 32 >( data_size );
   run_vector_extension< avx512< uint8_t >, 32, 32 >( data_size );
   run_vector_extension< avx512< uint8_t >, 1, 64 >( data_size );
   run_vector_extension< avx512< uint8_t >, 2, 64 >( data_size );
   run_vector_extension< avx512< uint8_t >, 4, 64 >( data_size );
   run_vector_extension< avx512< uint8_t >, 8, 64 >( data_size );
   run_vector_extension< avx512< uint8_t >, 16, 64 >( data_size );
   run_vector_extension< avx512< uint8_t >, 32, 64 >( data_size );
   run_vector_extension< avx512< uint8_t >, 64, 64 >( data_size );

   run_vector_extension< avx512< uint16_t >, 1, 1 >( data_size );
   run_vector_extension< avx512< uint16_t >, 1, 2 >( data_size );
   run_vector_extension< avx512< uint16_t >, 2, 2 >( data_size );
   run_vector_extension< avx512< uint16_t >, 1, 4 >( data_size );
   run_vector_extension< avx512< uint16_t >, 2, 4 >( data_size );
   run_vector_extension< avx512< uint16_t >, 4, 4 >( data_size );
   run_vector_extension< avx512< uint16_t >, 1, 8 >( data_size );
   run_vector_extension< avx512< uint16_t >, 2, 8 >( data_size );
   run_vector_extension< avx512< uint16_t >, 4, 8 >( data_size );
   run_vector_extension< avx512< uint16_t >, 8, 8 >( data_size );
   run_vector_extension< avx512< uint16_t >, 1, 16 >( data_size );
   run_vector_extension< avx512< uint16_t >, 2, 16 >( data_size );
   run_vector_extension< avx512< uint16_t >, 4, 16 >( data_size );
   run_vector_extension< avx512< uint16_t >, 8, 16 >( data_size );
   run_vector_extension< avx512< uint16_t >, 16, 16 >( data_size );
   run_vector_extension< avx512< uint16_t >, 1, 32 >( data_size );
   run_vector_extension< avx512< uint16_t >, 2, 32 >( data_size );
   run_vector_extension< avx512< uint16_t >, 4, 32 >( data_size );
   run_vector_extension< avx512< uint16_t >, 8, 32 >( data_size );
   run_vector_extension< avx512< uint16_t >, 16, 32 >( data_size );
   run_vector_extension< avx512< uint16_t >, 32, 32 >( data_size );

   run_vector_extension< avx512< uint32_t >, 1, 1 >( data_size );
   run_vector_extension< avx512< uint32_t >, 1, 2 >( data_size );
   run_vector_extension< avx512< uint32_t >, 2, 2 >( data_size );
   run_vector_extension< avx512< uint32_t >, 1, 4 >( data_size );
   run_vector_extension< avx512< uint32_t >, 2, 4 >( data_size );
   run_vector_extension< avx512< uint32_t >, 4, 4 >( data_size );
   run_vector_extension< avx512< uint32_t >, 1, 8 >( data_size );
   run_vector_extension< avx512< uint32_t >, 2, 8 >( data_size );
   run_vector_extension< avx512< uint32_t >, 4, 8 >( data_size );
   run_vector_extension< avx512< uint32_t >, 8, 8 >( data_size );
   run_vector_extension< avx512< uint32_t >, 1, 16 >( data_size );
   run_vector_extension< avx512< uint32_t >, 2, 16 >( data_size );
   run_vector_extension< avx512< uint32_t >, 4, 16 >( data_size );
   run_vector_extension< avx512< uint32_t >, 8, 16 >( data_size );
   run_vector_extension< avx512< uint32_t >, 16, 16 >( data_size );

   run_vector_extension< avx512< uint64_t >, 1, 1 >( data_size );
   run_vector_extension< avx512< uint64_t >, 1, 2 >( data_size );
   run_vector_extension< avx512< uint64_t >, 2, 2 >( data_size );
   run_vector_extension< avx512< uint64_t >, 1, 4 >( data_size );
   run_vector_extension< avx512< uint64_t >, 2, 4 >( data_size );
   run_vector_extension< avx512< uint64_t >, 4, 4 >( data_size );
   run_vector_extension< avx512< uint64_t >, 1, 8 >( data_size );
   run_vector_extension< avx512< uint64_t >, 2, 8 >( data_size );
   run_vector_extension< avx512< uint64_t >, 4, 8 >( data_size );
   run_vector_extension< avx512< uint64_t >, 8, 8 >( data_size );
}

void run_benchmark( std::size_t data_size ) {
   run_benchmark_sse( data_size );
   run_benchmark_avx2( data_size );
   run_benchmark_avx512( data_size );
}

int main( void ) {
   using namespace tuddbs;
   const char * description = "#Results of the microbenchmark for different build variants for the SIMQ-Vector builder.";

   std::cout << description << "\n" << get_definitions("#") <<
      "id;data_count;data_size;vector_extension_name;data_type_size_bit;" <<
      "build_variant_name;column_count;query_count;time_needed_ns;dummy_result;dummy_val\n";

   run_benchmark( 16_KiB );
   run_benchmark( 512_KiB );
   run_benchmark( 8_MiB );
   run_benchmark( 32_MiB );
   run_benchmark( 128_MiB );
}
