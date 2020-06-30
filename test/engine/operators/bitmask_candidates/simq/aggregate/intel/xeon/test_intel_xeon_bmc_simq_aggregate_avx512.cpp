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
#include <engine/operators/bitmask_candidates/simq/aggregate_bitmask_candidates.h>
#include <engine/operators/bitmask_candidates/simq/filter_bitmask_candidates.h>
#include <engine/operators/core/filter/point_filter_comparator_core.h>
#include <engine/operators/core/aggregate/aggregate_sum_core.h>
#include <utils/random.h>
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

   typename rng< T >::engine_t engine( 0xC004C0FEEBADC0DE );

   /**
    * create filter data with the following pattern:
    * 2 * 0x0, 2 * 0x1, ... 2 * 0x40, data_count-128 * 0x80
    * This is shuffled.
    * Processing such a column with <64? will lead to a maximum of 128 hits.
    *
    * create sum data consisting of value 2.
    *
    * Thus <64? will lead to an aggregated sum of 128
    * query0( <1 ? ) => 2 values => sum = 2
    * query1( <2 ? ) => 4 values => sum = 1
    * query64( <64 ? ) => 128 values => sum = 128
    *
    */
   using column_array_t = column_array< avx512< T >, ColumnCount >;
   column_array_t mb_column_filter_array;
   column_array_t mb_column_to_sum_array;
   for( std::size_t column_id = 0; column_id < ColumnCount; ++column_id ) {
      auto filter_column = create_column( T, data_count );
      for( std::size_t i = 0; i < data_count; ++i ) {
         filter_column->data_ptr[ i ] = ( T ) 128;
      }
      std::size_t pos = 0;
      for( std::size_t i = 0; i < 64; ++i ) {
         for( std::size_t j = 0; j < 2; ++j ) {
            filter_column->data_ptr[ pos++ ] = i;
         }
      }
      std::shuffle( filter_column->data_ptr, filter_column->data_ptr + ( filter_column->data_count ), engine );
      mb_column_filter_array.set( column_id, filter_column );

      auto sum_column = create_column( T, data_count );
      for( std::size_t i = 0; i < data_count; ++i ) {
         sum_column->data_ptr[ i ] = ( T ) 1;
      }
      mb_column_to_sum_array.set( column_id, sum_column );
   }

   using predicate_array_t = value_array< avx512< T >, QueryCount >;
   predicate_array_t mb_value_array;
   for( std::size_t i = 0; i < QueryCount; ++i ) {
      mb_value_array.set( i, i+1 );
   }
   typename avx512< T >::vector_t predicate_vec =
      simq_value_vector_view_t< predicate_array_t, ColumnCount >::apply( mb_value_array );
//   print< avx512 < T > >( std::cout, predicate_vec, "Pred" );

   column< T > * bitmask_column = create_bitmask( T, data_count * QueryCount );
   column< T > * result_column = create_column( T, vector_constants_t< avx512< T > >::vector_element_count_t::value );
   using svb_t =
   simq_vector_builder_t<
      simq_vector_builder_mask_broadcast_t,
      column_array_t,
      QueryCount
   >;
   svb_t svb_for_filter( mb_column_filter_array );
   svb_t svb_for_aggregation( mb_column_to_sum_array );

   filter_impl< avx512< T >, svb_t, point_filter_lt_core >::apply( bitmask_column, svb_for_filter, predicate_vec );

//   for( std::size_t i = 0; i < bitmask_column->data_count; ++i ) {
//      std::cout << "[" << std::setw( 4 ) << i << "]: " << std::bitset< sizeof( T ) * 8 >{ bitmask_column->data_ptr[ i ] } << "\n";
//   }

   aggregate_impl< avx512< T >, svb_t, aggregate_mask_add >::apply(  result_column, svb_for_aggregation, bitmask_column );
   [[maybe_unused]]typename avx512< T >::base_t * tmp = store< avx512< T > >(
      result_column->data_ptr,
      aggregate_mask_add< avx512< T > >::template finalize< svb_t::lanes_per_query_t::value >(
         load< avx512< T > >( result_column->data_ptr )
      )
   );
   bool result_val = true;
   for( std::size_t i = 0; i < QueryCount; ++i ) {
      if( result_column->data_ptr[ i ] != ( (i+1) * 2 ) ) {
         std::cerr << "ValueSize: " << sizeof( T ) * 8 << ". [ColumnCount, QueryCount] == [" << ColumnCount << ", " << QueryCount << "]. ";
         std::cerr << "Query #" << i << ". ";
         std::cerr << "Error.";
         std::cerr << "Expected: " << ( (i+1) * 2 ) << ". Is: " << ( uint64_t ) result_column->data_ptr[ i ] << "\n";
         result_val = false;
      }
   }

   destroy_column( result_column );
   destroy_column( bitmask_column );
   for( std::size_t i = ColumnCount; i > 0; --i ) {
      destroy_column( mb_column_to_sum_array.columns[ i - 1 ] );
      destroy_column( mb_column_filter_array.columns[ i - 1 ] );
   }

   return result_val;
}

int main( void ) {

   /**
    * @todo: if datacount % vector_element_count != 0, this fails (take care in remainder part of filter)
    */
   bool result = test< uint8_t, 1, 1 >( 512 );
   result &= test< uint8_t, 1, 2 >( 512 );
   result &= test< uint8_t, 2, 2 >( 512 );
   result &= test< uint8_t, 1, 4 >( 512 );
   result &= test< uint8_t, 2, 4 >( 512 );
   result &= test< uint8_t, 4, 4 >( 512 );
   result &= test< uint8_t, 1, 8 >( 512 );
   result &= test< uint8_t, 2, 8 >( 512 );
   result &= test< uint8_t, 4, 8 >( 512 );
   result &= test< uint8_t, 8, 8 >( 512 );
   result &= test< uint8_t, 1, 16 >( 512 );
   result &= test< uint8_t, 2, 16 >( 512 );
   result &= test< uint8_t, 4, 16 >( 512 );
   result &= test< uint8_t, 8, 16 >( 512 );
   result &= test< uint8_t, 16, 16 >( 512 );
   result &= test< uint8_t, 1, 32 >( 512 );
   result &= test< uint8_t, 2, 32 >( 512 );
   result &= test< uint8_t, 4, 32 >( 512 );
   result &= test< uint8_t, 8, 32 >( 512 );
   result &= test< uint8_t, 16, 32 >( 512 );
   result &= test< uint8_t, 32, 32 >( 512 );
   result &= test< uint8_t, 1, 64 >( 512 );
   result &= test< uint8_t, 2, 64 >( 512 );
   result &= test< uint8_t, 4, 64 >( 512 );
   result &= test< uint8_t, 8, 64 >( 512 );
   result &= test< uint8_t, 16, 64 >( 512 );
   result &= test< uint8_t, 32, 64 >( 512 );
   result &= test< uint8_t, 64, 64 >( 512 );

   result &= test< uint16_t, 1, 1 >( 512 );
   result &= test< uint16_t, 1, 2 >( 512 );
   result &= test< uint16_t, 2, 2 >( 512 );
   result &= test< uint16_t, 1, 4 >( 512 );
   result &= test< uint16_t, 2, 4 >( 512 );
   result &= test< uint16_t, 4, 4 >( 512 );
   result &= test< uint16_t, 1, 8 >( 512 );
   result &= test< uint16_t, 2, 8 >( 512 );
   result &= test< uint16_t, 4, 8 >( 512 );
   result &= test< uint16_t, 8, 8 >( 512 );
   result &= test< uint16_t, 1, 16 >( 512 );
   result &= test< uint16_t, 2, 16 >( 512 );
   result &= test< uint16_t, 4, 16 >( 512 );
   result &= test< uint16_t, 8, 16 >( 512 );
   result &= test< uint16_t, 16, 16 >( 512 );
   result &= test< uint16_t, 1, 32 >( 512 );
   result &= test< uint16_t, 2, 32 >( 512 );
   result &= test< uint16_t, 4, 32 >( 512 );
   result &= test< uint16_t, 8, 32 >( 512 );
   result &= test< uint16_t, 16, 32 >( 512 );
   result &= test< uint16_t, 32, 32 >( 512 );

   result &= test< uint32_t, 1, 1 >( 512 );
   result &= test< uint32_t, 1, 2 >( 512 );
   result &= test< uint32_t, 2, 2 >( 512 );
   result &= test< uint32_t, 1, 4 >( 512 );
   result &= test< uint32_t, 2, 4 >( 512 );
   result &= test< uint32_t, 4, 4 >( 512 );
   result &= test< uint32_t, 1, 8 >( 512 );
   result &= test< uint32_t, 2, 8 >( 512 );
   result &= test< uint32_t, 4, 8 >( 512 );
   result &= test< uint32_t, 8, 8 >( 512 );
   result &= test< uint32_t, 1, 16 >( 512 );
   result &= test< uint32_t, 2, 16 >( 512 );
   result &= test< uint32_t, 4, 16 >( 512 );
   result &= test< uint32_t, 8, 16 >( 512 );
   result &= test< uint32_t, 16, 16 >( 512 );

   result &= test< uint64_t, 1, 1 >( 512 );
   result &= test< uint64_t, 1, 2 >( 512 );
   result &= test< uint64_t, 2, 2 >( 512 );
   result &= test< uint64_t, 1, 4 >( 512 );
   result &= test< uint64_t, 2, 4 >( 512 );
   result &= test< uint64_t, 4, 4 >( 512 );
   result &= test< uint64_t, 1, 8 >( 512 );
   result &= test< uint64_t, 2, 8 >( 512 );
   result &= test< uint64_t, 4, 8 >( 512 );
   result &= test< uint64_t, 8, 8 >( 512 );

   if( result )
      return 0;
   return 1;
}
