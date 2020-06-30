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
#include <engine/operators/bitmask_candidates/sequential/aggregate_bitmask_candidates.h>
#include <engine/operators/core/aggregate/aggregate_sum_core.h>
#include <utils/random.h>
#include <bitset>

template< typename T >
bool test( std::size_t data_count ) {
   using namespace tuddbs;
   T const expected_result = 14;

   column< T > * data_column = create_column( T, data_count );
   column< T > * bitmask_column = create_bitmask( T, data_count );
   column< T > * result_column = create_column( T, vector_constants_t< avx2< T > >::vector_element_count_t::value );

   for( std::size_t i = 0; i < data_count; ++i ) {
      data_column->data_ptr[ i ] = ( T ) 1;
   }
   for( std::size_t i = 0; i < bitmask_column->data_count; ++i ) {
      bitmask_column->data_ptr[ i ] = ( T ) 0;
   }

   typename rng< T >::engine_t engine( 0xC004C0FEEBADC0DE );
   std::uniform_int_distribution< T > dist1(0, bitmask_column->data_count - 1 );
   std::uniform_int_distribution< T > dist2(0, sizeof( T ) * 8 - 1 );

   std::size_t to_set = expected_result;
   while( to_set != 0 ) {
      std::size_t pos_in_bitmask = dist1( engine );
      std::size_t bit_pos = dist2( engine );
      T new_val = ( 1 << bit_pos );
      if( ( bitmask_column->data_ptr[ pos_in_bitmask ] & new_val ) == 0 ) {
         --to_set;
         bitmask_column->data_ptr[ pos_in_bitmask ] |= new_val;
      }
   }

   sequential_aggregate_impl< avx2< T >, aggregate_mask_add >::apply( result_column, data_column, bitmask_column );

   bool result_val = true;
   std::cout << (uint64_t) result_column->data_ptr[ 0 ] << "\n";
   if( result_column->data_ptr[ 0 ] != expected_result )
      result_val = false;

   destroy_column( result_column );
   destroy_column( bitmask_column );
   destroy_column( data_column );
   if( !result_val ) {
      std::cerr << "Error: Processing " << data_count << " values with a size of " << sizeof( T ) << "\n";
   }
   return result_val;
}

int main( void ) {

   /**
    * @todo: if datacount % vector_element_count != 0, this fails (take care in remainder part of filter)
    */
   bool result = test< uint8_t >( 128 );
   result &= test< uint16_t >( 128 );
   result &= test< uint32_t >( 128 );
   result &= test< uint64_t >( 128 );
   if( result )
      return 0;
   return 1;
}
