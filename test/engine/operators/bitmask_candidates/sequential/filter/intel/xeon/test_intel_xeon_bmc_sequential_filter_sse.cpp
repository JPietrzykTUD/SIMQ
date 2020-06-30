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

#include <data/column.h>
#include <simd/intrin.h>
#include <engine/operators/bitmask_candidates/sequential/filter_bitmask_candidates.h>
#include <engine/operators/core/filter/point_filter_comparator_core.h>
#include <bitset>

template< typename T >
bool test( std::size_t data_count ) {
   using namespace tuddbs;
   column< T > * data_column = create_column( T, data_count );
   column< T > * result_column = create_bitmask( T, data_count );
   T const predicate = 4;
   T * data_ptr = data_column->data_ptr;
   T * result_ptr = result_column->data_ptr;
   column< T > * const expected_result_column = create_bitmask( T, data_count );
   T * const expected_result_ptr_orig = expected_result_column->data_ptr;
   T * expected_result_ptr = expected_result_ptr_orig;
   T mask = 0;
   std::size_t shift = 0;
   bool stored = false;
   for( std::size_t i = 0; i < data_count; ++i ) {
      stored = false;
      data_ptr[ i ] = i % 32;
      if( ( i % ( sizeof(T) * 8) == 0 ) && ( i != 0 ) ) {
         *( expected_result_ptr++ ) = mask;
         mask = 0;
         shift = 0;
         stored = true;
      }
      T tmp = ( data_ptr[ i ] < predicate ) ? 1 : 0;
      mask |= ( tmp << shift );
      ++shift;
   }
   if( !stored )
      *( expected_result_ptr++ ) = mask;

   sequential_filter_impl< sse< T >, point_filter_lt_core >::apply( result_column, data_column, broadcast< sse< T > >( predicate ) );

   bool result_val = true;
   expected_result_ptr = expected_result_ptr_orig;
   for( std::size_t i = 0; i < result_column->data_count; ++i ) {
      if( result_ptr[ i ] != *( expected_result_ptr++ ) ) {
         std::cerr << "ValueSize: " << sizeof( T ) * 8 << ".";
         std::cerr << "Error.";
         std::cerr << "[" << i << "/" << result_column->data_count << "]: " << std::bitset< sizeof( T ) * 8>{result_ptr[ i ]} << " != " << std::bitset< sizeof( T ) * 8 >{ *expected_result_ptr } << "\n";
         result_val = false;
      }
   }

   destroy_column( expected_result_column );
   destroy_column( result_column );
   destroy_column( data_column );
   return result_val;
}

int main( void ) {

   /**
    * @todo: if datacount % vector_element_count != 0, this fails (take care in remainder part of filter)
    */
   bool result = test< uint8_t >( 128 );
//   bool result = test< uint8_t >( 131 );
   result &= test< uint16_t >( 128 );
   result &= test< uint32_t >( 128 );
   result &= test< uint64_t >( 128 );

   if( result )
      return 0;
   return 1;
}
