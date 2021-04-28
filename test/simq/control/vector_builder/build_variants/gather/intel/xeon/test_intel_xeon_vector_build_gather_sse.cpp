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
#include <data/column.h>
#include <simd/intrin.h>
#include <array>
#include <vector>
#include <data/container/column_array.h>
#include <simq/control/vector_builder/vector_view.h>
#include <simq/control/vector_builder/vector_builder.h>
#include <simq/control/vector_builder/build_variants/gather.h>

#define MAX_VECTOR_ELEMENT_COUNT 16
#define ELEMENT_COUNT 1024

template< typename T >
void print( __m128i a ) {
   std::array< T, 16/sizeof(T) > tmp;
   _mm_store_si128( reinterpret_cast< __m128i * >( tmp.data() ), a );
   for( std::size_t i = 0; i < 16/sizeof(T); ++i ) {
      std::cout << std::setw( 3 ) << (int)tmp[ 16/sizeof(T) - 1 -i ] << " ";
   }
   std::cout << "\n";
}

std::array< tuddbs::column< uint64_t > *, MAX_VECTOR_ELEMENT_COUNT > select_columns_arr;

template< typename T, int ColumnCount, int QueryCount >
bool test( void ) {
   using namespace tuddbs;
   column_array< sse< T >, ColumnCount > test_column_array;
   std::size_t data_count = 0;
   for( std::size_t i = 0; i < ColumnCount; ++i ) {
      data_count = select_columns_arr[ i ]->data_count * (sizeof( uint64_t ) / sizeof( T ) );
      test_column_array.set(
         i,
         new column< T >( (T*) select_columns_arr[ i ]->data_ptr, data_count )
      );
   }

   simq_vector_builder_t<
      simq_vector_builder_gather_t,
      column_array< sse< T >, ColumnCount >, QueryCount > a( test_column_array );

   T * const output_buffer_orig = ( T * ) acquire( data_count * sizeof( T ) * QueryCount, 16 );
   T * const should_be_buffer = ( T * ) acquire( data_count * sizeof( T ) * QueryCount, 16 );
   T * output_buffer = output_buffer_orig;
   std::size_t incrementor = a.get_incrementor();
   for( std::size_t i = 0; i < data_count; i+=incrementor ) {
      __m128i tmp_vec = a.get_and_increment();
      _mm_store_si128( reinterpret_cast< __m128i * >( output_buffer), tmp_vec );
      output_buffer += ( 16 / sizeof( T ) );
   }


   std::size_t element_count = 16 / sizeof( T );
   std::size_t lanes_per_column = element_count / ColumnCount;
   std::vector< std::size_t > col_id;
   std::vector< std::size_t > col_offset;
   for( std::size_t i = 0; i < ColumnCount; ++i ) {
      for( std::size_t j = 0; j < lanes_per_column; ++j ) {
         col_id.push_back( i );
      }
   }
   std::size_t lanes_per_query = element_count / QueryCount;
   for( std::size_t i = 0; i < QueryCount; ++i ) {
      for( std::size_t j = 0; j < lanes_per_query; ++j ) {
         col_offset.push_back( j );
      }
   }

   std::size_t out_offset = 0;

   while( out_offset < data_count * QueryCount ) {
      for( std::size_t i = 0; i < element_count; ++i ) {
         should_be_buffer[ out_offset++ ] = test_column_array.columns[ col_id[ i ] ]->data_ptr[ col_offset[ i ] ];
         col_offset[ i ] += lanes_per_query;
      }
   }


   bool result = true;
   for( std::size_t i = 0; i < data_count  * QueryCount; ++i ) {
      if( output_buffer_orig[ i ] != should_be_buffer[ i ] ) {
         result = false;
         std::cerr << "[" << i << "]: " << "Should be: " << (int) should_be_buffer[ i ] << ". Is: " << (int) output_buffer_orig[ i ] << "\n";
      }
   }
   release_ptr( ( void * ) should_be_buffer );
   release_ptr((void*)output_buffer_orig);
   return result;
}


void init( void ) {
   using namespace tuddbs;
   for( std::size_t i = 0; i < MAX_VECTOR_ELEMENT_COUNT; ++i ) {
      auto column = create_column( uint64_t, ELEMENT_COUNT );
      uint64_t * data = column->data_ptr;
      if( i == 0 )
         for( std::size_t j = 0; j < ELEMENT_COUNT; ++j ) {
            data[ j ] = ( i * ELEMENT_COUNT ) + j;
         }
      select_columns_arr[ i ] = column;
   }
}

int main( void ) {
   init();

   bool result = test< uint32_t, 1, 1 >();
   result &= test< uint32_t, 1, 2 >();
   result &= test< uint32_t, 2, 2 >();
   result &= test< uint32_t, 1, 4 >();
   result &= test< uint32_t, 2, 4 >();
   result &= test< uint32_t, 4, 4 >();
   if( result )
      std::cout << "uint32_t: OK\n";

   result &= test< uint64_t, 1, 1 >();
   result &= test< uint64_t, 1, 2 >();
   result &= test< uint64_t, 2, 2 >();
   if( result )
      std::cout << "uint64_t: OK\n";

   if( result )
      return 0;
   return 1;
}