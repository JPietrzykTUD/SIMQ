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

#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_SET_INTEL_IMPL_SSE_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_SET_INTEL_IMPL_SSE_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace tuddbs {
   template<
      class ColumnContainer,
      std::size_t NumberOfQueries,
      typename DepT
   >
   struct simq_vector_builder_set_t< ColumnContainer, NumberOfQueries, DepT, sse < DepT > > {
   using VectorExtension = typename ColumnContainer::vector_extension_t;
   using T = typename VectorExtension::base_t;
   
   static constexpr char const * get_name( void ) { return "SET"; }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
         std::nullptr_t
      >::type = nullptr
   >
   FORCE_INLINE
   static
   typename sse< uint8_t >::vector_t
   get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
   & svw ) {
   /* { col_id }[ col_offset ]
    * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
    * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
    * |
    */
   uint8_t val0 = *svw.column_data_ptr[ 0 ];
   svw.column_data_ptr[ 0 ] += 16;
   uint8_t val1 = *svw.column_data_ptr[ 1 ];
   svw.column_data_ptr[ 1 ] += 16;
   uint8_t val2 = *svw.column_data_ptr[ 2 ];
   svw.column_data_ptr[ 2 ] += 16;
   uint8_t val3 = *svw.column_data_ptr[ 3 ];
   svw.column_data_ptr[ 3 ] += 16;
   uint8_t val4 = *svw.column_data_ptr[ 4 ];
   svw.column_data_ptr[ 4 ] += 16;
   uint8_t val5 = *svw.column_data_ptr[ 5 ];
   svw.column_data_ptr[ 5 ] += 16;
   uint8_t val6 = *svw.column_data_ptr[ 6 ];
   svw.column_data_ptr[ 6 ] += 16;
   uint8_t val7 = *svw.column_data_ptr[ 7 ];
   svw.column_data_ptr[ 7 ] += 16;
   uint8_t val8 = *svw.column_data_ptr[ 8 ];
   svw.column_data_ptr[ 8 ] += 16;
   uint8_t val9 = *svw.column_data_ptr[ 9 ];
   svw.column_data_ptr[ 9 ] += 16;
   uint8_t val10 = *svw.column_data_ptr[ 10 ];
   svw.column_data_ptr[ 10 ] += 16;
   uint8_t val11 = *svw.column_data_ptr[ 11 ];
   svw.column_data_ptr[ 11 ] += 16;
   uint8_t val12 = *svw.column_data_ptr[ 12 ];
   svw.column_data_ptr[ 12 ] += 16;
   uint8_t val13 = *svw.column_data_ptr[ 13 ];
   svw.column_data_ptr[ 13 ] += 16;
   uint8_t val14 = *svw.column_data_ptr[ 14 ];
   svw.column_data_ptr[ 14 ] += 16;
   uint8_t val15 = *svw.column_data_ptr[ 15 ];
   svw.column_data_ptr[ 15 ] += 16;
   typename sse< uint8_t >::vector_t
      result =
      set
      < sse
      < uint8_t
      >
      > ( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
   return
   result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 8;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 8;
uint8_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 8;
uint8_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 8;
uint8_t val4 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 8;
uint8_t val5 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 8;
uint8_t val6 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 8;
uint8_t val7 = *svw.column_data_ptr[ 7 ];
svw.column_data_ptr[ 7 ] += 8;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
 * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 8;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 8;
uint8_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 8;
uint8_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 8;
uint8_t val4 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 8;
uint8_t val5 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 8;
uint8_t val6 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 8;
uint8_t val7 = *svw.column_data_ptr[ 7 ];
svw.column_data_ptr[ 7 ] += 8;
uint8_t val8 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 8;
uint8_t val9 = *svw.column_data_ptr[ 9 ];
svw.column_data_ptr[ 9 ] += 8;
uint8_t val10 = *svw.column_data_ptr[ 10 ];
svw.column_data_ptr[ 10 ] += 8;
uint8_t val11 = *svw.column_data_ptr[ 11 ];
svw.column_data_ptr[ 11 ] += 8;
uint8_t val12 = *svw.column_data_ptr[ 12 ];
svw.column_data_ptr[ 12 ] += 8;
uint8_t val13 = *svw.column_data_ptr[ 13 ];
svw.column_data_ptr[ 13 ] += 8;
uint8_t val14 = *svw.column_data_ptr[ 14 ];
svw.column_data_ptr[ 14 ] += 8;
uint8_t val15 = *svw.column_data_ptr[ 15 ];
svw.column_data_ptr[ 15 ] += 8;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 4;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 4;
uint8_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 4;
uint8_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 4;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
 * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 4;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 4;
uint8_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 4;
uint8_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 4;
uint8_t val4 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 4;
uint8_t val5 = *svw.column_data_ptr[ 9 ];
svw.column_data_ptr[ 9 ] += 4;
uint8_t val6 = *svw.column_data_ptr[ 10 ];
svw.column_data_ptr[ 10 ] += 4;
uint8_t val7 = *svw.column_data_ptr[ 11 ];
svw.column_data_ptr[ 11 ] += 4;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val7, val6, val5, val4, val7, val6, val5, val4, val3, val2, val1, val0, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
 * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 4;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 4;
uint8_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 4;
uint8_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 4;
uint8_t val4 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 4;
uint8_t val5 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 4;
uint8_t val6 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 4;
uint8_t val7 = *svw.column_data_ptr[ 7 ];
svw.column_data_ptr[ 7 ] += 4;
uint8_t val8 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 4;
uint8_t val9 = *svw.column_data_ptr[ 9 ];
svw.column_data_ptr[ 9 ] += 4;
uint8_t val10 = *svw.column_data_ptr[ 10 ];
svw.column_data_ptr[ 10 ] += 4;
uint8_t val11 = *svw.column_data_ptr[ 11 ];
svw.column_data_ptr[ 11 ] += 4;
uint8_t val12 = *svw.column_data_ptr[ 12 ];
svw.column_data_ptr[ 12 ] += 4;
uint8_t val13 = *svw.column_data_ptr[ 13 ];
svw.column_data_ptr[ 13 ] += 4;
uint8_t val14 = *svw.column_data_ptr[ 14 ];
svw.column_data_ptr[ 14 ] += 4;
uint8_t val15 = *svw.column_data_ptr[ 15 ];
svw.column_data_ptr[ 15 ] += 4;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 8 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 8 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
 * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
uint8_t val2 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 2;
uint8_t val3 = *svw.column_data_ptr[ 9 ];
svw.column_data_ptr[ 9 ] += 2;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val3, val2, val3, val2, val3, val2, val3, val2, val1, val0, val1, val0, val1, val0, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 8 ) && ( NoC == 4 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
 * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
uint8_t val2 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 2;
uint8_t val3 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 2;
uint8_t val4 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 2;
uint8_t val5 = *svw.column_data_ptr[ 9 ];
svw.column_data_ptr[ 9 ] += 2;
uint8_t val6 = *svw.column_data_ptr[ 12 ];
svw.column_data_ptr[ 12 ] += 2;
uint8_t val7 = *svw.column_data_ptr[ 13 ];
svw.column_data_ptr[ 13 ] += 2;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val7, val6, val7, val6, val5, val4, val5, val4, val3, val2, val3, val2, val1, val0, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 8 ) && ( NoC == 8 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
 * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
uint8_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 2;
uint8_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 2;
uint8_t val4 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 2;
uint8_t val5 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 2;
uint8_t val6 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 2;
uint8_t val7 = *svw.column_data_ptr[ 7 ];
svw.column_data_ptr[ 7 ] += 2;
uint8_t val8 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 2;
uint8_t val9 = *svw.column_data_ptr[ 9 ];
svw.column_data_ptr[ 9 ] += 2;
uint8_t val10 = *svw.column_data_ptr[ 10 ];
svw.column_data_ptr[ 10 ] += 2;
uint8_t val11 = *svw.column_data_ptr[ 11 ];
svw.column_data_ptr[ 11 ] += 2;
uint8_t val12 = *svw.column_data_ptr[ 12 ];
svw.column_data_ptr[ 12 ] += 2;
uint8_t val13 = *svw.column_data_ptr[ 13 ];
svw.column_data_ptr[ 13 ] += 2;
uint8_t val14 = *svw.column_data_ptr[ 14 ];
svw.column_data_ptr[ 14 ] += 2;
uint8_t val15 = *svw.column_data_ptr[ 15 ];
svw.column_data_ptr[ 15 ] += 2;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 16 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
 * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 16 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
 * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint8_t val1 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 1;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val1, val1, val1, val1, val1, val1, val1, val1, val0, val0, val0, val0, val0, val0, val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 16 ) && ( NoC == 4 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
 * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint8_t val1 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 1;
uint8_t val2 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 1;
uint8_t val3 = *svw.column_data_ptr[ 12 ];
svw.column_data_ptr[ 12 ] += 1;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val3, val3, val3, val3, val2, val2, val2, val2, val1, val1, val1, val1, val0, val0, val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 16 ) && ( NoC == 8 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
 * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint8_t val1 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 1;
uint8_t val2 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 1;
uint8_t val3 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 1;
uint8_t val4 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 1;
uint8_t val5 = *svw.column_data_ptr[ 10 ];
svw.column_data_ptr[ 10 ] += 1;
uint8_t val6 = *svw.column_data_ptr[ 12 ];
svw.column_data_ptr[ 12 ] += 1;
uint8_t val7 = *svw.column_data_ptr[ 14 ];
svw.column_data_ptr[ 14 ] += 1;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val7, val7, val6, val6, val5, val5, val4, val4, val3, val3, val2, val2, val1, val1, val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 16 ) && ( NoC == 16 ) && ( std::is_same < VecExt, sse < uint8_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint8_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 15 }[ 0  ] | { 14 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ]|
 * | { 7  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ]|
 * |
 */
uint8_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint8_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 1;
uint8_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 1;
uint8_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 1;
uint8_t val4 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 1;
uint8_t val5 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 1;
uint8_t val6 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 1;
uint8_t val7 = *svw.column_data_ptr[ 7 ];
svw.column_data_ptr[ 7 ] += 1;
uint8_t val8 = *svw.column_data_ptr[ 8 ];
svw.column_data_ptr[ 8 ] += 1;
uint8_t val9 = *svw.column_data_ptr[ 9 ];
svw.column_data_ptr[ 9 ] += 1;
uint8_t val10 = *svw.column_data_ptr[ 10 ];
svw.column_data_ptr[ 10 ] += 1;
uint8_t val11 = *svw.column_data_ptr[ 11 ];
svw.column_data_ptr[ 11 ] += 1;
uint8_t val12 = *svw.column_data_ptr[ 12 ];
svw.column_data_ptr[ 12 ] += 1;
uint8_t val13 = *svw.column_data_ptr[ 13 ];
svw.column_data_ptr[ 13 ] += 1;
uint8_t val14 = *svw.column_data_ptr[ 14 ];
svw.column_data_ptr[ 14 ] += 1;
uint8_t val15 = *svw.column_data_ptr[ 15 ];
svw.column_data_ptr[ 15 ] += 1;
typename sse< uint8_t >::vector_t
   result =
   set
   < sse
   < uint8_t
   >
   > ( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 8;
uint16_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 8;
uint16_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 8;
uint16_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 8;
uint16_t val4 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 8;
uint16_t val5 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 8;
uint16_t val6 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 8;
uint16_t val7 = *svw.column_data_ptr[ 7 ];
svw.column_data_ptr[ 7 ] += 8;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val7, val6, val5, val4, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 4;
uint16_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 4;
uint16_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 4;
uint16_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 4;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val3, val2, val1, val0, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 4;
uint16_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 4;
uint16_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 4;
uint16_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 4;
uint16_t val4 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 4;
uint16_t val5 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 4;
uint16_t val6 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 4;
uint16_t val7 = *svw.column_data_ptr[ 7 ];
svw.column_data_ptr[ 7 ] += 4;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val7, val6, val5, val4, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint16_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val1, val0, val1, val0, val1, val0, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint16_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
uint16_t val2 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 2;
uint16_t val3 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 2;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val3, val2, val3, val2, val1, val0, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint16_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
uint16_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 2;
uint16_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 2;
uint16_t val4 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 2;
uint16_t val5 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 2;
uint16_t val6 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 2;
uint16_t val7 = *svw.column_data_ptr[ 7 ];
svw.column_data_ptr[ 7 ] += 2;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val7, val6, val5, val4, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 8 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val0, val0, val0, val0, val0, val0, val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 8 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint16_t val1 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 1;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val1, val1, val1, val1, val0, val0, val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 8 ) && ( NoC == 4 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint16_t val1 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 1;
uint16_t val2 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 1;
uint16_t val3 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 1;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val3, val3, val2, val2, val1, val1, val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 8 ) && ( NoC == 8 ) && ( std::is_same < VecExt, sse < uint16_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint16_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 7  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ]|
 * |
 */
uint16_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint16_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 1;
uint16_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 1;
uint16_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 1;
uint16_t val4 = *svw.column_data_ptr[ 4 ];
svw.column_data_ptr[ 4 ] += 1;
uint16_t val5 = *svw.column_data_ptr[ 5 ];
svw.column_data_ptr[ 5 ] += 1;
uint16_t val6 = *svw.column_data_ptr[ 6 ];
svw.column_data_ptr[ 6 ] += 1;
uint16_t val7 = *svw.column_data_ptr[ 7 ];
svw.column_data_ptr[ 7 ] += 1;
typename sse< uint16_t >::vector_t result = set < sse < uint16_t > > ( val7, val6, val5, val4, val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint32_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint32_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] |
 */
uint32_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 4;
uint32_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 4;
uint32_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 4;
uint32_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 4;
typename sse< uint32_t >::vector_t result = set < sse < uint32_t > > ( val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint32_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint32_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] |
 */
uint32_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint32_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
typename sse< uint32_t >::vector_t result = set < sse < uint32_t > > ( val1, val0, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint32_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint32_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] |
 */
uint32_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint32_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
uint32_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 2;
uint32_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 2;
typename sse< uint32_t >::vector_t result = set < sse < uint32_t > > ( val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint32_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint32_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] |
 */
uint32_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
typename sse< uint32_t >::vector_t result = set < sse < uint32_t > > ( val0, val0, val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint32_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint32_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] |
 */
uint32_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint32_t val1 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 1;
typename sse< uint32_t >::vector_t result = set < sse < uint32_t > > ( val1, val1, val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same < VecExt, sse < uint32_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint32_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] |
 */
uint32_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint32_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 1;
uint32_t val2 = *svw.column_data_ptr[ 2 ];
svw.column_data_ptr[ 2 ] += 1;
uint32_t val3 = *svw.column_data_ptr[ 3 ];
svw.column_data_ptr[ 3 ] += 1;
typename sse< uint32_t >::vector_t result = set < sse < uint32_t > > ( val3, val2, val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint64_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint64_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 1  ] | { 0  }[ 0  ] |
 */
uint64_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 2;
uint64_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 2;
typename sse< uint64_t >::vector_t result = set < sse < uint64_t > > ( val1, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same < VecExt, sse < uint64_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint64_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 0  }[ 0  ] | { 0  }[ 0  ] |
 */
uint64_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
typename sse< uint64_t >::vector_t result = set < sse < uint64_t > > ( val0, val0 );
return
result;
}

template<
   std::size_t NoQ = NumberOfQueries,
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if<
      ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same < VecExt, sse < uint64_t > > ::value ) ),
      std::nullptr_t
   >::type = nullptr
>
FORCE_INLINE
static
typename sse< uint64_t >::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
& svw ) {
/* { col_id }[ col_offset ]
 * | { 1  }[ 0  ] | { 0  }[ 0  ] |
 */
uint64_t val0 = *svw.column_data_ptr[ 0 ];
svw.column_data_ptr[ 0 ] += 1;
uint64_t val1 = *svw.column_data_ptr[ 1 ];
svw.column_data_ptr[ 1 ] += 1;
typename sse< uint64_t >::vector_t result = set < sse < uint64_t > > ( val1, val0 );
return
result;
}

};
}
#endif
        