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
#include <engine/operators/bitmask_candidates/simq/filter_bitmask_candidates.h>
#include <engine/operators/core/filter/point_filter_comparator_core.h>
#include <data/container/column_array.h>
#include <simq/control/vector_builder/vector_view.h>
#include <simq/control/vector_builder/vector_builder.h>
#include <simq/control/vector_builder/build_variants/buffer.h>
#include <simq/control/vector_builder/build_variants/mask_broadcast.h>
#include <bitset>


template<
   typename T,
   std::size_t ColumnCount,
   std::size_t QueryCount
>
bool test( std::size_t data_count ) {
   using namespace tuddbs;

   using value_array_t = value_array< avx2< T >, QueryCount >;
   value_array_t mb_value_array;
   for( std::size_t i = 0; i < QueryCount; ++i ) {
      mb_value_array.set( i, i+1 );
   }
   typename avx2< T >::vector_t predicate_vec =
      simq_value_vector_view_t< value_array_t, ColumnCount >::apply( mb_value_array );

   using column_array_t = column_array< avx2< T >, ColumnCount >;
   column_array_t mb_column_array;
   for( std::size_t i = 0; i < ColumnCount; ++i ) {
      auto column = create_column( T, data_count );
      T * data = column->data_ptr;
      for( std::size_t j = 0; j < data_count; ++j ) {
         data[ j ] = j % 32;
      }
      mb_column_array.set( i, column );
   }

   using svb_t =
   simq_vector_builder_t<
      simq_vector_builder_mask_broadcast_t,
      column_array_t,
      QueryCount
   >;

   /**
    * Prepare sequential buffer - BEGIN
    */
   column< T > * sequential_column = create_column( T, data_count * QueryCount );
   column< T > * expected_column = create_bitmask( T, data_count * QueryCount );
   T * sequential_buffer = sequential_column->data_ptr;
   svb_t svb_for_gather( mb_column_array );
   std::size_t incrementor = svb_t::get_incrementor( );
   for( std::size_t i = 0; i < data_count; i += incrementor ) {
      sequential_buffer = store< avx2< T > >( sequential_buffer, svb_for_gather.get_and_increment( ) );
   }
   sequential_filter_impl< avx2< T >, point_filter_lt_core >::apply( expected_column, sequential_column, predicate_vec );
   /**
    * Prepare sequential buffer - END
    */


   svb_t svb( mb_column_array );
   auto result_column = create_bitmask( T, data_count * QueryCount );
   filter_impl< avx2< T >, svb_t, point_filter_lt_core >::apply( result_column, svb, predicate_vec );


   bool result_val = true;
   T * expected_result_ptr = expected_column->data_ptr;
   T * result_ptr = result_column->data_ptr;
   for( std::size_t i = 0; i < result_column->data_count; ++i ) {
      if( result_ptr[ i ] != *( expected_result_ptr++ ) ) {
         std::cerr << "ERR\n";
         std::cerr << "[" << i << "]: " << std::bitset< sizeof( T ) * 8>{result_ptr[ i ]} << " != " << std::bitset< sizeof( T ) * 8 >{ *expected_result_ptr } << "\n";
         result_val = false;
      }
   }

   destroy_column( result_column );
   destroy_column( expected_column );
   destroy_column( sequential_column );
   for( std::size_t i = ColumnCount; i > 0; --i ) {
      destroy_column( mb_column_array.columns[ i-1 ] );
   }
   return result_val;
}

int main( void ) {

   /**
    * @todo: if datacount % vector_element_count != 0, this fails (take care in remainder part of filter)
    */
   bool result = test< uint8_t, 1, 1 >( 128 );
   result &= test< uint8_t, 1, 2 >( 128 );
   result &= test< uint8_t, 2, 2 >( 128 );
   result &= test< uint8_t, 1, 4 >( 128 );
   result &= test< uint8_t, 2, 4 >( 128 );
   result &= test< uint8_t, 4, 4 >( 128 );
   result &= test< uint8_t, 1, 8 >( 128 );
   result &= test< uint8_t, 2, 8 >( 128 );
   result &= test< uint8_t, 4, 8 >( 128 );
   result &= test< uint8_t, 8, 8 >( 128 );
   result &= test< uint8_t, 1, 16 >( 128 );
   result &= test< uint8_t, 2, 16 >( 128 );
   result &= test< uint8_t, 4, 16 >( 128 );
   result &= test< uint8_t, 8, 16 >( 128 );
   result &= test< uint8_t, 16, 16 >( 128 );
   result &= test< uint8_t, 1, 32 >( 128 );
   result &= test< uint8_t, 2, 32 >( 128 );
   result &= test< uint8_t, 4, 32 >( 128 );
   result &= test< uint8_t, 8, 32 >( 128 );
   result &= test< uint8_t, 16, 32 >( 128 );
   result &= test< uint8_t, 32, 32 >( 128 );

   result &= test< uint16_t, 1, 1 >( 128 );
   result &= test< uint16_t, 1, 2 >( 128 );
   result &= test< uint16_t, 2, 2 >( 128 );
   result &= test< uint16_t, 1, 4 >( 128 );
   result &= test< uint16_t, 2, 4 >( 128 );
   result &= test< uint16_t, 4, 4 >( 128 );
   result &= test< uint16_t, 1, 8 >( 128 );
   result &= test< uint16_t, 2, 8 >( 128 );
   result &= test< uint16_t, 4, 8 >( 128 );
   result &= test< uint16_t, 8, 8 >( 128 );
   result &= test< uint16_t, 1, 16 >( 128 );
   result &= test< uint16_t, 2, 16 >( 128 );
   result &= test< uint16_t, 4, 16 >( 128 );
   result &= test< uint16_t, 8, 16 >( 128 );
   result &= test< uint16_t, 16, 16 >( 128 );

   result &= test< uint32_t, 1, 1 >( 128 );
   result &= test< uint32_t, 1, 2 >( 128 );
   result &= test< uint32_t, 2, 2 >( 128 );
   result &= test< uint32_t, 1, 4 >( 128 );
   result &= test< uint32_t, 2, 4 >( 128 );
   result &= test< uint32_t, 4, 4 >( 128 );
   result &= test< uint32_t, 1, 8 >( 128 );
   result &= test< uint32_t, 2, 8 >( 128 );
   result &= test< uint32_t, 4, 8 >( 128 );
   result &= test< uint32_t, 8, 8 >( 128 );

   result &= test< uint64_t, 1, 1 >( 128 );
   result &= test< uint64_t, 1, 2 >( 128 );
   result &= test< uint64_t, 2, 2 >( 128 );
   result &= test< uint64_t, 1, 4 >( 128 );
   result &= test< uint64_t, 2, 4 >( 128 );
   result &= test< uint64_t, 4, 4 >( 128 );

   if( result )
      return 0;
   return 1;
}
