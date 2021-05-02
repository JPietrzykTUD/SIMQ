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

#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_SET_IMPL_AVX512_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_SET_IMPL_AVX512_H
#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <cstdint>
#include <cstddef>
#include <type_traits>
namespace tuddbs{
   template<
      class ColumnContainer,
      std::size_t NumberOfQueries,
      typename DepT
   >
   struct simq_vector_builder_set_t< ColumnContainer, NumberOfQueries, DepT, avx512< DepT > > { 
      using VectorExtension = typename ColumnContainer::vector_extension_t;
      using T = typename VectorExtension::base_t;
      static constexpr char const * get_name( void ) { return "SET"; }
            
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 63 ] | { 0  }[ 62 ] | { 0  }[ 61 ] | { 0  }[ 60 ] | { 0  }[ 59 ] | { 0  }[ 58 ] | { 0  }[ 57 ] | { 0  }[ 56 ]|
          * | { 0  }[ 55 ] | { 0  }[ 54 ] | { 0  }[ 53 ] | { 0  }[ 52 ] | { 0  }[ 51 ] | { 0  }[ 50 ] | { 0  }[ 49 ] | { 0  }[ 48 ]|
          * | { 0  }[ 47 ] | { 0  }[ 46 ] | { 0  }[ 45 ] | { 0  }[ 44 ] | { 0  }[ 43 ] | { 0  }[ 42 ] | { 0  }[ 41 ] | { 0  }[ 40 ]|
          * | { 0  }[ 39 ] | { 0  }[ 38 ] | { 0  }[ 37 ] | { 0  }[ 36 ] | { 0  }[ 35 ] | { 0  }[ 34 ] | { 0  }[ 33 ] | { 0  }[ 32 ]|
          * | { 0  }[ 31 ] | { 0  }[ 30 ] | { 0  }[ 29 ] | { 0  }[ 28 ] | { 0  }[ 27 ] | { 0  }[ 26 ] | { 0  }[ 25 ] | { 0  }[ 24 ]|
          * | { 0  }[ 23 ] | { 0  }[ 22 ] | { 0  }[ 21 ] | { 0  }[ 20 ] | { 0  }[ 19 ] | { 0  }[ 18 ] | { 0  }[ 17 ] | { 0  }[ 16 ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 64;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 64;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 64;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 64;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 64;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 64;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 64;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 64;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 64;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 64;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 64;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 64;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 64;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 64;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 64;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 64;
         uint8_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 64;
         uint8_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 64;
         uint8_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 64;
         uint8_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 64;
         uint8_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 64;
         uint8_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 64;
         uint8_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 64;
         uint8_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 64;
         uint8_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 64;
         uint8_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 64;
         uint8_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 64;
         uint8_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 64;
         uint8_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 64;
         uint8_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 64;
         uint8_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 64;
         uint8_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 64;
         uint8_t val32 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 64;
         uint8_t val33 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 64;
         uint8_t val34 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 64;
         uint8_t val35 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 64;
         uint8_t val36 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 64;
         uint8_t val37 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 64;
         uint8_t val38 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 64;
         uint8_t val39 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 64;
         uint8_t val40 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 64;
         uint8_t val41 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 64;
         uint8_t val42 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 64;
         uint8_t val43 = *svw.column_data_ptr[ 43 ]; svw.column_data_ptr[ 43 ] += 64;
         uint8_t val44 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 64;
         uint8_t val45 = *svw.column_data_ptr[ 45 ]; svw.column_data_ptr[ 45 ] += 64;
         uint8_t val46 = *svw.column_data_ptr[ 46 ]; svw.column_data_ptr[ 46 ] += 64;
         uint8_t val47 = *svw.column_data_ptr[ 47 ]; svw.column_data_ptr[ 47 ] += 64;
         uint8_t val48 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 64;
         uint8_t val49 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 64;
         uint8_t val50 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 64;
         uint8_t val51 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 64;
         uint8_t val52 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 64;
         uint8_t val53 = *svw.column_data_ptr[ 53 ]; svw.column_data_ptr[ 53 ] += 64;
         uint8_t val54 = *svw.column_data_ptr[ 54 ]; svw.column_data_ptr[ 54 ] += 64;
         uint8_t val55 = *svw.column_data_ptr[ 55 ]; svw.column_data_ptr[ 55 ] += 64;
         uint8_t val56 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 64;
         uint8_t val57 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 64;
         uint8_t val58 = *svw.column_data_ptr[ 58 ]; svw.column_data_ptr[ 58 ] += 64;
         uint8_t val59 = *svw.column_data_ptr[ 59 ]; svw.column_data_ptr[ 59 ] += 64;
         uint8_t val60 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 64;
         uint8_t val61 = *svw.column_data_ptr[ 61 ]; svw.column_data_ptr[ 61 ] += 64;
         uint8_t val62 = *svw.column_data_ptr[ 62 ]; svw.column_data_ptr[ 62 ] += 64;
         uint8_t val63 = *svw.column_data_ptr[ 63 ]; svw.column_data_ptr[ 63 ] += 64;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val63, val62, val61, val60, val59, val58, val57, val56, val55, val54, val53, val52, val51, val50, val49, val48, val47, val46, val45, val44, val43, val42, val41, val40, val39, val38, val37, val36, val35, val34, val33, val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 31 ] | { 0  }[ 30 ] | { 0  }[ 29 ] | { 0  }[ 28 ] | { 0  }[ 27 ] | { 0  }[ 26 ] | { 0  }[ 25 ] | { 0  }[ 24 ]|
          * | { 0  }[ 23 ] | { 0  }[ 22 ] | { 0  }[ 21 ] | { 0  }[ 20 ] | { 0  }[ 19 ] | { 0  }[ 18 ] | { 0  }[ 17 ] | { 0  }[ 16 ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 31 ] | { 0  }[ 30 ] | { 0  }[ 29 ] | { 0  }[ 28 ] | { 0  }[ 27 ] | { 0  }[ 26 ] | { 0  }[ 25 ] | { 0  }[ 24 ]|
          * | { 0  }[ 23 ] | { 0  }[ 22 ] | { 0  }[ 21 ] | { 0  }[ 20 ] | { 0  }[ 19 ] | { 0  }[ 18 ] | { 0  }[ 17 ] | { 0  }[ 16 ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 32;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 32;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 32;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 32;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 32;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 32;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 32;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 32;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 32;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 32;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 32;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 32;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 32;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 32;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 32;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 32;
         uint8_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 32;
         uint8_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 32;
         uint8_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 32;
         uint8_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 32;
         uint8_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 32;
         uint8_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 32;
         uint8_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 32;
         uint8_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 32;
         uint8_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 32;
         uint8_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 32;
         uint8_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 32;
         uint8_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 32;
         uint8_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 32;
         uint8_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 32;
         uint8_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 32;
         uint8_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 32;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 31 ] | { 1  }[ 30 ] | { 1  }[ 29 ] | { 1  }[ 28 ] | { 1  }[ 27 ] | { 1  }[ 26 ] | { 1  }[ 25 ] | { 1  }[ 24 ]|
          * | { 1  }[ 23 ] | { 1  }[ 22 ] | { 1  }[ 21 ] | { 1  }[ 20 ] | { 1  }[ 19 ] | { 1  }[ 18 ] | { 1  }[ 17 ] | { 1  }[ 16 ]|
          * | { 1  }[ 15 ] | { 1  }[ 14 ] | { 1  }[ 13 ] | { 1  }[ 12 ] | { 1  }[ 11 ] | { 1  }[ 10 ] | { 1  }[ 9  ] | { 1  }[ 8  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 31 ] | { 0  }[ 30 ] | { 0  }[ 29 ] | { 0  }[ 28 ] | { 0  }[ 27 ] | { 0  }[ 26 ] | { 0  }[ 25 ] | { 0  }[ 24 ]|
          * | { 0  }[ 23 ] | { 0  }[ 22 ] | { 0  }[ 21 ] | { 0  }[ 20 ] | { 0  }[ 19 ] | { 0  }[ 18 ] | { 0  }[ 17 ] | { 0  }[ 16 ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 32;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 32;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 32;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 32;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 32;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 32;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 32;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 32;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 32;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 32;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 32;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 32;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 32;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 32;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 32;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 32;
         uint8_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 32;
         uint8_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 32;
         uint8_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 32;
         uint8_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 32;
         uint8_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 32;
         uint8_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 32;
         uint8_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 32;
         uint8_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 32;
         uint8_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 32;
         uint8_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 32;
         uint8_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 32;
         uint8_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 32;
         uint8_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 32;
         uint8_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 32;
         uint8_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 32;
         uint8_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 32;
         uint8_t val32 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 32;
         uint8_t val33 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 32;
         uint8_t val34 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 32;
         uint8_t val35 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 32;
         uint8_t val36 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 32;
         uint8_t val37 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 32;
         uint8_t val38 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 32;
         uint8_t val39 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 32;
         uint8_t val40 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 32;
         uint8_t val41 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 32;
         uint8_t val42 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 32;
         uint8_t val43 = *svw.column_data_ptr[ 43 ]; svw.column_data_ptr[ 43 ] += 32;
         uint8_t val44 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 32;
         uint8_t val45 = *svw.column_data_ptr[ 45 ]; svw.column_data_ptr[ 45 ] += 32;
         uint8_t val46 = *svw.column_data_ptr[ 46 ]; svw.column_data_ptr[ 46 ] += 32;
         uint8_t val47 = *svw.column_data_ptr[ 47 ]; svw.column_data_ptr[ 47 ] += 32;
         uint8_t val48 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 32;
         uint8_t val49 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 32;
         uint8_t val50 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 32;
         uint8_t val51 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 32;
         uint8_t val52 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 32;
         uint8_t val53 = *svw.column_data_ptr[ 53 ]; svw.column_data_ptr[ 53 ] += 32;
         uint8_t val54 = *svw.column_data_ptr[ 54 ]; svw.column_data_ptr[ 54 ] += 32;
         uint8_t val55 = *svw.column_data_ptr[ 55 ]; svw.column_data_ptr[ 55 ] += 32;
         uint8_t val56 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 32;
         uint8_t val57 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 32;
         uint8_t val58 = *svw.column_data_ptr[ 58 ]; svw.column_data_ptr[ 58 ] += 32;
         uint8_t val59 = *svw.column_data_ptr[ 59 ]; svw.column_data_ptr[ 59 ] += 32;
         uint8_t val60 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 32;
         uint8_t val61 = *svw.column_data_ptr[ 61 ]; svw.column_data_ptr[ 61 ] += 32;
         uint8_t val62 = *svw.column_data_ptr[ 62 ]; svw.column_data_ptr[ 62 ] += 32;
         uint8_t val63 = *svw.column_data_ptr[ 63 ]; svw.column_data_ptr[ 63 ] += 32;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val63, val62, val61, val60, val59, val58, val57, val56, val55, val54, val53, val52, val51, val50, val49, val48, val47, val46, val45, val44, val43, val42, val41, val40, val39, val38, val37, val36, val35, val34, val33, val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 16;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 16;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 16;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 16;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 16;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 16;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 16;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 16;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 16;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 16;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 16;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 16;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 16;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 16;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 16;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 16;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 15 ] | { 1  }[ 14 ] | { 1  }[ 13 ] | { 1  }[ 12 ] | { 1  }[ 11 ] | { 1  }[ 10 ] | { 1  }[ 9  ] | { 1  }[ 8  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 15 ] | { 1  }[ 14 ] | { 1  }[ 13 ] | { 1  }[ 12 ] | { 1  }[ 11 ] | { 1  }[ 10 ] | { 1  }[ 9  ] | { 1  }[ 8  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 16;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 16;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 16;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 16;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 16;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 16;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 16;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 16;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 16;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 16;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 16;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 16;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 16;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 16;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 16;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 16;
         uint8_t val16 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 16;
         uint8_t val17 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 16;
         uint8_t val18 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 16;
         uint8_t val19 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 16;
         uint8_t val20 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 16;
         uint8_t val21 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 16;
         uint8_t val22 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 16;
         uint8_t val23 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 16;
         uint8_t val24 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 16;
         uint8_t val25 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 16;
         uint8_t val26 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 16;
         uint8_t val27 = *svw.column_data_ptr[ 43 ]; svw.column_data_ptr[ 43 ] += 16;
         uint8_t val28 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 16;
         uint8_t val29 = *svw.column_data_ptr[ 45 ]; svw.column_data_ptr[ 45 ] += 16;
         uint8_t val30 = *svw.column_data_ptr[ 46 ]; svw.column_data_ptr[ 46 ] += 16;
         uint8_t val31 = *svw.column_data_ptr[ 47 ]; svw.column_data_ptr[ 47 ] += 16;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 15 ] | { 3  }[ 14 ] | { 3  }[ 13 ] | { 3  }[ 12 ] | { 3  }[ 11 ] | { 3  }[ 10 ] | { 3  }[ 9  ] | { 3  }[ 8  ]|
          * | { 3  }[ 7  ] | { 3  }[ 6  ] | { 3  }[ 5  ] | { 3  }[ 4  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 15 ] | { 2  }[ 14 ] | { 2  }[ 13 ] | { 2  }[ 12 ] | { 2  }[ 11 ] | { 2  }[ 10 ] | { 2  }[ 9  ] | { 2  }[ 8  ]|
          * | { 2  }[ 7  ] | { 2  }[ 6  ] | { 2  }[ 5  ] | { 2  }[ 4  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 15 ] | { 1  }[ 14 ] | { 1  }[ 13 ] | { 1  }[ 12 ] | { 1  }[ 11 ] | { 1  }[ 10 ] | { 1  }[ 9  ] | { 1  }[ 8  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 16;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 16;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 16;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 16;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 16;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 16;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 16;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 16;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 16;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 16;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 16;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 16;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 16;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 16;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 16;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 16;
         uint8_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 16;
         uint8_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 16;
         uint8_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 16;
         uint8_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 16;
         uint8_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 16;
         uint8_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 16;
         uint8_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 16;
         uint8_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 16;
         uint8_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 16;
         uint8_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 16;
         uint8_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 16;
         uint8_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 16;
         uint8_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 16;
         uint8_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 16;
         uint8_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 16;
         uint8_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 16;
         uint8_t val32 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 16;
         uint8_t val33 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 16;
         uint8_t val34 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 16;
         uint8_t val35 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 16;
         uint8_t val36 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 16;
         uint8_t val37 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 16;
         uint8_t val38 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 16;
         uint8_t val39 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 16;
         uint8_t val40 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 16;
         uint8_t val41 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 16;
         uint8_t val42 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 16;
         uint8_t val43 = *svw.column_data_ptr[ 43 ]; svw.column_data_ptr[ 43 ] += 16;
         uint8_t val44 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 16;
         uint8_t val45 = *svw.column_data_ptr[ 45 ]; svw.column_data_ptr[ 45 ] += 16;
         uint8_t val46 = *svw.column_data_ptr[ 46 ]; svw.column_data_ptr[ 46 ] += 16;
         uint8_t val47 = *svw.column_data_ptr[ 47 ]; svw.column_data_ptr[ 47 ] += 16;
         uint8_t val48 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 16;
         uint8_t val49 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 16;
         uint8_t val50 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 16;
         uint8_t val51 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 16;
         uint8_t val52 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 16;
         uint8_t val53 = *svw.column_data_ptr[ 53 ]; svw.column_data_ptr[ 53 ] += 16;
         uint8_t val54 = *svw.column_data_ptr[ 54 ]; svw.column_data_ptr[ 54 ] += 16;
         uint8_t val55 = *svw.column_data_ptr[ 55 ]; svw.column_data_ptr[ 55 ] += 16;
         uint8_t val56 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 16;
         uint8_t val57 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 16;
         uint8_t val58 = *svw.column_data_ptr[ 58 ]; svw.column_data_ptr[ 58 ] += 16;
         uint8_t val59 = *svw.column_data_ptr[ 59 ]; svw.column_data_ptr[ 59 ] += 16;
         uint8_t val60 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 16;
         uint8_t val61 = *svw.column_data_ptr[ 61 ]; svw.column_data_ptr[ 61 ] += 16;
         uint8_t val62 = *svw.column_data_ptr[ 62 ]; svw.column_data_ptr[ 62 ] += 16;
         uint8_t val63 = *svw.column_data_ptr[ 63 ]; svw.column_data_ptr[ 63 ] += 16;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val63, val62, val61, val60, val59, val58, val57, val56, val55, val54, val53, val52, val51, val50, val49, val48, val47, val46, val45, val44, val43, val42, val41, val40, val39, val38, val37, val36, val35, val34, val33, val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         uint8_t val8 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 8;
         uint8_t val9 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 8;
         uint8_t val10 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 8;
         uint8_t val11 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 8;
         uint8_t val12 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 8;
         uint8_t val13 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 8;
         uint8_t val14 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 8;
         uint8_t val15 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 8;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val15, val14, val13, val12, val11, val10, val9, val8, val15, val14, val13, val12, val11, val10, val9, val8, val15, val14, val13, val12, val11, val10, val9, val8, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 7  ] | { 3  }[ 6  ] | { 3  }[ 5  ] | { 3  }[ 4  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 3  }[ 7  ] | { 3  }[ 6  ] | { 3  }[ 5  ] | { 3  }[ 4  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 7  ] | { 2  }[ 6  ] | { 2  }[ 5  ] | { 2  }[ 4  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 2  }[ 7  ] | { 2  }[ 6  ] | { 2  }[ 5  ] | { 2  }[ 4  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         uint8_t val8 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 8;
         uint8_t val9 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 8;
         uint8_t val10 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 8;
         uint8_t val11 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 8;
         uint8_t val12 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 8;
         uint8_t val13 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 8;
         uint8_t val14 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 8;
         uint8_t val15 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 8;
         uint8_t val16 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 8;
         uint8_t val17 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 8;
         uint8_t val18 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 8;
         uint8_t val19 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 8;
         uint8_t val20 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 8;
         uint8_t val21 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 8;
         uint8_t val22 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 8;
         uint8_t val23 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 8;
         uint8_t val24 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 8;
         uint8_t val25 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 8;
         uint8_t val26 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 8;
         uint8_t val27 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 8;
         uint8_t val28 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 8;
         uint8_t val29 = *svw.column_data_ptr[ 53 ]; svw.column_data_ptr[ 53 ] += 8;
         uint8_t val30 = *svw.column_data_ptr[ 54 ]; svw.column_data_ptr[ 54 ] += 8;
         uint8_t val31 = *svw.column_data_ptr[ 55 ]; svw.column_data_ptr[ 55 ] += 8;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val31, val30, val29, val28, val27, val26, val25, val24, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 7  ] | { 7  }[ 6  ] | { 7  }[ 5  ] | { 7  }[ 4  ] | { 7  }[ 3  ] | { 7  }[ 2  ] | { 7  }[ 1  ] | { 7  }[ 0  ]|
          * | { 6  }[ 7  ] | { 6  }[ 6  ] | { 6  }[ 5  ] | { 6  }[ 4  ] | { 6  }[ 3  ] | { 6  }[ 2  ] | { 6  }[ 1  ] | { 6  }[ 0  ]|
          * | { 5  }[ 7  ] | { 5  }[ 6  ] | { 5  }[ 5  ] | { 5  }[ 4  ] | { 5  }[ 3  ] | { 5  }[ 2  ] | { 5  }[ 1  ] | { 5  }[ 0  ]|
          * | { 4  }[ 7  ] | { 4  }[ 6  ] | { 4  }[ 5  ] | { 4  }[ 4  ] | { 4  }[ 3  ] | { 4  }[ 2  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 7  ] | { 3  }[ 6  ] | { 3  }[ 5  ] | { 3  }[ 4  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 7  ] | { 2  }[ 6  ] | { 2  }[ 5  ] | { 2  }[ 4  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 8;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 8;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 8;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 8;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 8;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 8;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 8;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 8;
         uint8_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 8;
         uint8_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 8;
         uint8_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 8;
         uint8_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 8;
         uint8_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 8;
         uint8_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 8;
         uint8_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 8;
         uint8_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 8;
         uint8_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 8;
         uint8_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 8;
         uint8_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 8;
         uint8_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 8;
         uint8_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 8;
         uint8_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 8;
         uint8_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 8;
         uint8_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 8;
         uint8_t val32 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 8;
         uint8_t val33 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 8;
         uint8_t val34 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 8;
         uint8_t val35 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 8;
         uint8_t val36 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 8;
         uint8_t val37 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 8;
         uint8_t val38 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 8;
         uint8_t val39 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 8;
         uint8_t val40 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 8;
         uint8_t val41 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 8;
         uint8_t val42 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 8;
         uint8_t val43 = *svw.column_data_ptr[ 43 ]; svw.column_data_ptr[ 43 ] += 8;
         uint8_t val44 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 8;
         uint8_t val45 = *svw.column_data_ptr[ 45 ]; svw.column_data_ptr[ 45 ] += 8;
         uint8_t val46 = *svw.column_data_ptr[ 46 ]; svw.column_data_ptr[ 46 ] += 8;
         uint8_t val47 = *svw.column_data_ptr[ 47 ]; svw.column_data_ptr[ 47 ] += 8;
         uint8_t val48 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 8;
         uint8_t val49 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 8;
         uint8_t val50 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 8;
         uint8_t val51 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 8;
         uint8_t val52 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 8;
         uint8_t val53 = *svw.column_data_ptr[ 53 ]; svw.column_data_ptr[ 53 ] += 8;
         uint8_t val54 = *svw.column_data_ptr[ 54 ]; svw.column_data_ptr[ 54 ] += 8;
         uint8_t val55 = *svw.column_data_ptr[ 55 ]; svw.column_data_ptr[ 55 ] += 8;
         uint8_t val56 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 8;
         uint8_t val57 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 8;
         uint8_t val58 = *svw.column_data_ptr[ 58 ]; svw.column_data_ptr[ 58 ] += 8;
         uint8_t val59 = *svw.column_data_ptr[ 59 ]; svw.column_data_ptr[ 59 ] += 8;
         uint8_t val60 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 8;
         uint8_t val61 = *svw.column_data_ptr[ 61 ]; svw.column_data_ptr[ 61 ] += 8;
         uint8_t val62 = *svw.column_data_ptr[ 62 ]; svw.column_data_ptr[ 62 ] += 8;
         uint8_t val63 = *svw.column_data_ptr[ 63 ]; svw.column_data_ptr[ 63 ] += 8;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val63, val62, val61, val60, val59, val58, val57, val56, val55, val54, val53, val52, val51, val50, val49, val48, val47, val46, val45, val44, val43, val42, val41, val40, val39, val38, val37, val36, val35, val34, val33, val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint8_t val4 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 4;
         uint8_t val5 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 4;
         uint8_t val6 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 4;
         uint8_t val7 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 4;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint8_t val4 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 4;
         uint8_t val5 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 4;
         uint8_t val6 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 4;
         uint8_t val7 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 4;
         uint8_t val8 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 4;
         uint8_t val9 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 4;
         uint8_t val10 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 4;
         uint8_t val11 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 4;
         uint8_t val12 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 4;
         uint8_t val13 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 4;
         uint8_t val14 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 4;
         uint8_t val15 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 4;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val15, val14, val13, val12, val15, val14, val13, val12, val15, val14, val13, val12, val15, val14, val13, val12, val11, val10, val9, val8, val11, val10, val9, val8, val11, val10, val9, val8, val11, val10, val9, val8, val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 3  ] | { 7  }[ 2  ] | { 7  }[ 1  ] | { 7  }[ 0  ] | { 7  }[ 3  ] | { 7  }[ 2  ] | { 7  }[ 1  ] | { 7  }[ 0  ]|
          * | { 6  }[ 3  ] | { 6  }[ 2  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 6  }[ 3  ] | { 6  }[ 2  ] | { 6  }[ 1  ] | { 6  }[ 0  ]|
          * | { 5  }[ 3  ] | { 5  }[ 2  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 5  }[ 3  ] | { 5  }[ 2  ] | { 5  }[ 1  ] | { 5  }[ 0  ]|
          * | { 4  }[ 3  ] | { 4  }[ 2  ] | { 4  }[ 1  ] | { 4  }[ 0  ] | { 4  }[ 3  ] | { 4  }[ 2  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint8_t val4 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 4;
         uint8_t val5 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 4;
         uint8_t val6 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 4;
         uint8_t val7 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 4;
         uint8_t val8 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 4;
         uint8_t val9 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 4;
         uint8_t val10 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 4;
         uint8_t val11 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 4;
         uint8_t val12 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 4;
         uint8_t val13 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 4;
         uint8_t val14 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 4;
         uint8_t val15 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 4;
         uint8_t val16 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 4;
         uint8_t val17 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 4;
         uint8_t val18 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 4;
         uint8_t val19 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 4;
         uint8_t val20 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 4;
         uint8_t val21 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 4;
         uint8_t val22 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 4;
         uint8_t val23 = *svw.column_data_ptr[ 43 ]; svw.column_data_ptr[ 43 ] += 4;
         uint8_t val24 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 4;
         uint8_t val25 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 4;
         uint8_t val26 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 4;
         uint8_t val27 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 4;
         uint8_t val28 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 4;
         uint8_t val29 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 4;
         uint8_t val30 = *svw.column_data_ptr[ 58 ]; svw.column_data_ptr[ 58 ] += 4;
         uint8_t val31 = *svw.column_data_ptr[ 59 ]; svw.column_data_ptr[ 59 ] += 4;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val31, val30, val29, val28, val31, val30, val29, val28, val27, val26, val25, val24, val27, val26, val25, val24, val23, val22, val21, val20, val23, val22, val21, val20, val19, val18, val17, val16, val19, val18, val17, val16, val15, val14, val13, val12, val15, val14, val13, val12, val11, val10, val9, val8, val11, val10, val9, val8, val7, val6, val5, val4, val7, val6, val5, val4, val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 16 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 15 }[ 3  ] | { 15 }[ 2  ] | { 15 }[ 1  ] | { 15 }[ 0  ] | { 14 }[ 3  ] | { 14 }[ 2  ] | { 14 }[ 1  ] | { 14 }[ 0  ]|
          * | { 13 }[ 3  ] | { 13 }[ 2  ] | { 13 }[ 1  ] | { 13 }[ 0  ] | { 12 }[ 3  ] | { 12 }[ 2  ] | { 12 }[ 1  ] | { 12 }[ 0  ]|
          * | { 11 }[ 3  ] | { 11 }[ 2  ] | { 11 }[ 1  ] | { 11 }[ 0  ] | { 10 }[ 3  ] | { 10 }[ 2  ] | { 10 }[ 1  ] | { 10 }[ 0  ]|
          * | { 9  }[ 3  ] | { 9  }[ 2  ] | { 9  }[ 1  ] | { 9  }[ 0  ] | { 8  }[ 3  ] | { 8  }[ 2  ] | { 8  }[ 1  ] | { 8  }[ 0  ]|
          * | { 7  }[ 3  ] | { 7  }[ 2  ] | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 3  ] | { 6  }[ 2  ] | { 6  }[ 1  ] | { 6  }[ 0  ]|
          * | { 5  }[ 3  ] | { 5  }[ 2  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 3  ] | { 4  }[ 2  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 4;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 4;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 4;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 4;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 4;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 4;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 4;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 4;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 4;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 4;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 4;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 4;
         uint8_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 4;
         uint8_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 4;
         uint8_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 4;
         uint8_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 4;
         uint8_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 4;
         uint8_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 4;
         uint8_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 4;
         uint8_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 4;
         uint8_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 4;
         uint8_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 4;
         uint8_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 4;
         uint8_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 4;
         uint8_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 4;
         uint8_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 4;
         uint8_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 4;
         uint8_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 4;
         uint8_t val32 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 4;
         uint8_t val33 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 4;
         uint8_t val34 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 4;
         uint8_t val35 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 4;
         uint8_t val36 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 4;
         uint8_t val37 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 4;
         uint8_t val38 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 4;
         uint8_t val39 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 4;
         uint8_t val40 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 4;
         uint8_t val41 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 4;
         uint8_t val42 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 4;
         uint8_t val43 = *svw.column_data_ptr[ 43 ]; svw.column_data_ptr[ 43 ] += 4;
         uint8_t val44 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 4;
         uint8_t val45 = *svw.column_data_ptr[ 45 ]; svw.column_data_ptr[ 45 ] += 4;
         uint8_t val46 = *svw.column_data_ptr[ 46 ]; svw.column_data_ptr[ 46 ] += 4;
         uint8_t val47 = *svw.column_data_ptr[ 47 ]; svw.column_data_ptr[ 47 ] += 4;
         uint8_t val48 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 4;
         uint8_t val49 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 4;
         uint8_t val50 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 4;
         uint8_t val51 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 4;
         uint8_t val52 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 4;
         uint8_t val53 = *svw.column_data_ptr[ 53 ]; svw.column_data_ptr[ 53 ] += 4;
         uint8_t val54 = *svw.column_data_ptr[ 54 ]; svw.column_data_ptr[ 54 ] += 4;
         uint8_t val55 = *svw.column_data_ptr[ 55 ]; svw.column_data_ptr[ 55 ] += 4;
         uint8_t val56 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 4;
         uint8_t val57 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 4;
         uint8_t val58 = *svw.column_data_ptr[ 58 ]; svw.column_data_ptr[ 58 ] += 4;
         uint8_t val59 = *svw.column_data_ptr[ 59 ]; svw.column_data_ptr[ 59 ] += 4;
         uint8_t val60 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 4;
         uint8_t val61 = *svw.column_data_ptr[ 61 ]; svw.column_data_ptr[ 61 ] += 4;
         uint8_t val62 = *svw.column_data_ptr[ 62 ]; svw.column_data_ptr[ 62 ] += 4;
         uint8_t val63 = *svw.column_data_ptr[ 63 ]; svw.column_data_ptr[ 63 ] += 4;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val63, val62, val61, val60, val59, val58, val57, val56, val55, val54, val53, val52, val51, val50, val49, val48, val47, val46, val45, val44, val43, val42, val41, val40, val39, val38, val37, val36, val35, val34, val33, val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint8_t val2 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 2;
         uint8_t val3 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 2;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint8_t val2 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 2;
         uint8_t val3 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 2;
         uint8_t val4 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 2;
         uint8_t val5 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 2;
         uint8_t val6 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 2;
         uint8_t val7 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 2;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val7, val6, val7, val6, val7, val6, val7, val6, val7, val6, val7, val6, val7, val6, val7, val6, val5, val4, val5, val4, val5, val4, val5, val4, val5, val4, val5, val4, val5, val4, val5, val4, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 7  }[ 1  ] | { 7  }[ 0  ] | { 7  }[ 1  ] | { 7  }[ 0  ] | { 7  }[ 1  ] | { 7  }[ 0  ]|
          * | { 6  }[ 1  ] | { 6  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ]|
          * | { 5  }[ 1  ] | { 5  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ]|
          * | { 4  }[ 1  ] | { 4  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint8_t val2 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 2;
         uint8_t val3 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 2;
         uint8_t val4 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 2;
         uint8_t val5 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 2;
         uint8_t val6 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 2;
         uint8_t val7 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 2;
         uint8_t val8 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 2;
         uint8_t val9 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 2;
         uint8_t val10 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 2;
         uint8_t val11 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 2;
         uint8_t val12 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 2;
         uint8_t val13 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 2;
         uint8_t val14 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 2;
         uint8_t val15 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 2;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val15, val14, val15, val14, val15, val14, val15, val14, val13, val12, val13, val12, val13, val12, val13, val12, val11, val10, val11, val10, val11, val10, val11, val10, val9, val8, val9, val8, val9, val8, val9, val8, val7, val6, val7, val6, val7, val6, val7, val6, val5, val4, val5, val4, val5, val4, val5, val4, val3, val2, val3, val2, val3, val2, val3, val2, val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 16 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 15 }[ 1  ] | { 15 }[ 0  ] | { 15 }[ 1  ] | { 15 }[ 0  ] | { 14 }[ 1  ] | { 14 }[ 0  ] | { 14 }[ 1  ] | { 14 }[ 0  ]|
          * | { 13 }[ 1  ] | { 13 }[ 0  ] | { 13 }[ 1  ] | { 13 }[ 0  ] | { 12 }[ 1  ] | { 12 }[ 0  ] | { 12 }[ 1  ] | { 12 }[ 0  ]|
          * | { 11 }[ 1  ] | { 11 }[ 0  ] | { 11 }[ 1  ] | { 11 }[ 0  ] | { 10 }[ 1  ] | { 10 }[ 0  ] | { 10 }[ 1  ] | { 10 }[ 0  ]|
          * | { 9  }[ 1  ] | { 9  }[ 0  ] | { 9  }[ 1  ] | { 9  }[ 0  ] | { 8  }[ 1  ] | { 8  }[ 0  ] | { 8  }[ 1  ] | { 8  }[ 0  ]|
          * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ]|
          * | { 5  }[ 1  ] | { 5  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint8_t val2 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 2;
         uint8_t val3 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 2;
         uint8_t val4 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 2;
         uint8_t val5 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 2;
         uint8_t val6 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 2;
         uint8_t val7 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 2;
         uint8_t val8 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 2;
         uint8_t val9 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 2;
         uint8_t val10 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 2;
         uint8_t val11 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 2;
         uint8_t val12 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 2;
         uint8_t val13 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 2;
         uint8_t val14 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 2;
         uint8_t val15 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 2;
         uint8_t val16 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 2;
         uint8_t val17 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 2;
         uint8_t val18 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 2;
         uint8_t val19 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 2;
         uint8_t val20 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 2;
         uint8_t val21 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 2;
         uint8_t val22 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 2;
         uint8_t val23 = *svw.column_data_ptr[ 45 ]; svw.column_data_ptr[ 45 ] += 2;
         uint8_t val24 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 2;
         uint8_t val25 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 2;
         uint8_t val26 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 2;
         uint8_t val27 = *svw.column_data_ptr[ 53 ]; svw.column_data_ptr[ 53 ] += 2;
         uint8_t val28 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 2;
         uint8_t val29 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 2;
         uint8_t val30 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 2;
         uint8_t val31 = *svw.column_data_ptr[ 61 ]; svw.column_data_ptr[ 61 ] += 2;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val31, val30, val31, val30, val29, val28, val29, val28, val27, val26, val27, val26, val25, val24, val25, val24, val23, val22, val23, val22, val21, val20, val21, val20, val19, val18, val19, val18, val17, val16, val17, val16, val15, val14, val15, val14, val13, val12, val13, val12, val11, val10, val11, val10, val9, val8, val9, val8, val7, val6, val7, val6, val5, val4, val5, val4, val3, val2, val3, val2, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 32 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 31 }[ 1  ] | { 31 }[ 0  ] | { 30 }[ 1  ] | { 30 }[ 0  ] | { 29 }[ 1  ] | { 29 }[ 0  ] | { 28 }[ 1  ] | { 28 }[ 0  ]|
          * | { 27 }[ 1  ] | { 27 }[ 0  ] | { 26 }[ 1  ] | { 26 }[ 0  ] | { 25 }[ 1  ] | { 25 }[ 0  ] | { 24 }[ 1  ] | { 24 }[ 0  ]|
          * | { 23 }[ 1  ] | { 23 }[ 0  ] | { 22 }[ 1  ] | { 22 }[ 0  ] | { 21 }[ 1  ] | { 21 }[ 0  ] | { 20 }[ 1  ] | { 20 }[ 0  ]|
          * | { 19 }[ 1  ] | { 19 }[ 0  ] | { 18 }[ 1  ] | { 18 }[ 0  ] | { 17 }[ 1  ] | { 17 }[ 0  ] | { 16 }[ 1  ] | { 16 }[ 0  ]|
          * | { 15 }[ 1  ] | { 15 }[ 0  ] | { 14 }[ 1  ] | { 14 }[ 0  ] | { 13 }[ 1  ] | { 13 }[ 0  ] | { 12 }[ 1  ] | { 12 }[ 0  ]|
          * | { 11 }[ 1  ] | { 11 }[ 0  ] | { 10 }[ 1  ] | { 10 }[ 0  ] | { 9  }[ 1  ] | { 9  }[ 0  ] | { 8  }[ 1  ] | { 8  }[ 0  ]|
          * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 2;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 2;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 2;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 2;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 2;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 2;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 2;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 2;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 2;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 2;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 2;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 2;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 2;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 2;
         uint8_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 2;
         uint8_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 2;
         uint8_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 2;
         uint8_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 2;
         uint8_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 2;
         uint8_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 2;
         uint8_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 2;
         uint8_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 2;
         uint8_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 2;
         uint8_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 2;
         uint8_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 2;
         uint8_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 2;
         uint8_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 2;
         uint8_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 2;
         uint8_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 2;
         uint8_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 2;
         uint8_t val32 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 2;
         uint8_t val33 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 2;
         uint8_t val34 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 2;
         uint8_t val35 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 2;
         uint8_t val36 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 2;
         uint8_t val37 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 2;
         uint8_t val38 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 2;
         uint8_t val39 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 2;
         uint8_t val40 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 2;
         uint8_t val41 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 2;
         uint8_t val42 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 2;
         uint8_t val43 = *svw.column_data_ptr[ 43 ]; svw.column_data_ptr[ 43 ] += 2;
         uint8_t val44 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 2;
         uint8_t val45 = *svw.column_data_ptr[ 45 ]; svw.column_data_ptr[ 45 ] += 2;
         uint8_t val46 = *svw.column_data_ptr[ 46 ]; svw.column_data_ptr[ 46 ] += 2;
         uint8_t val47 = *svw.column_data_ptr[ 47 ]; svw.column_data_ptr[ 47 ] += 2;
         uint8_t val48 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 2;
         uint8_t val49 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 2;
         uint8_t val50 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 2;
         uint8_t val51 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 2;
         uint8_t val52 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 2;
         uint8_t val53 = *svw.column_data_ptr[ 53 ]; svw.column_data_ptr[ 53 ] += 2;
         uint8_t val54 = *svw.column_data_ptr[ 54 ]; svw.column_data_ptr[ 54 ] += 2;
         uint8_t val55 = *svw.column_data_ptr[ 55 ]; svw.column_data_ptr[ 55 ] += 2;
         uint8_t val56 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 2;
         uint8_t val57 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 2;
         uint8_t val58 = *svw.column_data_ptr[ 58 ]; svw.column_data_ptr[ 58 ] += 2;
         uint8_t val59 = *svw.column_data_ptr[ 59 ]; svw.column_data_ptr[ 59 ] += 2;
         uint8_t val60 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 2;
         uint8_t val61 = *svw.column_data_ptr[ 61 ]; svw.column_data_ptr[ 61 ] += 2;
         uint8_t val62 = *svw.column_data_ptr[ 62 ]; svw.column_data_ptr[ 62 ] += 2;
         uint8_t val63 = *svw.column_data_ptr[ 63 ]; svw.column_data_ptr[ 63 ] += 2;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val63, val62, val61, val60, val59, val58, val57, val56, val55, val54, val53, val52, val51, val50, val49, val48, val47, val46, val45, val44, val43, val42, val41, val40, val39, val38, val37, val36, val35, val34, val33, val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 64 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 64 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint8_t val1 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 1;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 64 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ]|
          * | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint8_t val1 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         uint8_t val2 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 1;
         uint8_t val3 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 1;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val3, val3, val3, val3, val3, val3, val3, val3, val3, val3, val3, val3, val3, val3, val3, val3, val2, val2, val2, val2, val2, val2, val2, val2, val2, val2, val2, val2, val2, val2, val2, val2, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 64 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ]|
          * | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ]|
          * | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ]|
          * | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ]|
          * | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint8_t val1 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint8_t val2 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         uint8_t val3 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 1;
         uint8_t val4 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 1;
         uint8_t val5 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 1;
         uint8_t val6 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 1;
         uint8_t val7 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 1;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val7, val7, val7, val7, val7, val7, val7, val7, val6, val6, val6, val6, val6, val6, val6, val6, val5, val5, val5, val5, val5, val5, val5, val5, val4, val4, val4, val4, val4, val4, val4, val4, val3, val3, val3, val3, val3, val3, val3, val3, val2, val2, val2, val2, val2, val2, val2, val2, val1, val1, val1, val1, val1, val1, val1, val1, val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 64 ) && ( NoC == 16 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 15 }[ 0  ] | { 15 }[ 0  ] | { 15 }[ 0  ] | { 15 }[ 0  ] | { 14 }[ 0  ] | { 14 }[ 0  ] | { 14 }[ 0  ] | { 14 }[ 0  ]|
          * | { 13 }[ 0  ] | { 13 }[ 0  ] | { 13 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 12 }[ 0  ] | { 12 }[ 0  ] | { 12 }[ 0  ]|
          * | { 11 }[ 0  ] | { 11 }[ 0  ] | { 11 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 10 }[ 0  ] | { 10 }[ 0  ] | { 10 }[ 0  ]|
          * | { 9  }[ 0  ] | { 9  }[ 0  ] | { 9  }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ] | { 8  }[ 0  ] | { 8  }[ 0  ] | { 8  }[ 0  ]|
          * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ]|
          * | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint8_t val1 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint8_t val2 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint8_t val3 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 1;
         uint8_t val4 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         uint8_t val5 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 1;
         uint8_t val6 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 1;
         uint8_t val7 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 1;
         uint8_t val8 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 1;
         uint8_t val9 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 1;
         uint8_t val10 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 1;
         uint8_t val11 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 1;
         uint8_t val12 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 1;
         uint8_t val13 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 1;
         uint8_t val14 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 1;
         uint8_t val15 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 1;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val15, val15, val15, val15, val14, val14, val14, val14, val13, val13, val13, val13, val12, val12, val12, val12, val11, val11, val11, val11, val10, val10, val10, val10, val9, val9, val9, val9, val8, val8, val8, val8, val7, val7, val7, val7, val6, val6, val6, val6, val5, val5, val5, val5, val4, val4, val4, val4, val3, val3, val3, val3, val2, val2, val2, val2, val1, val1, val1, val1, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 64 ) && ( NoC == 32 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 31 }[ 0  ] | { 31 }[ 0  ] | { 30 }[ 0  ] | { 30 }[ 0  ] | { 29 }[ 0  ] | { 29 }[ 0  ] | { 28 }[ 0  ] | { 28 }[ 0  ]|
          * | { 27 }[ 0  ] | { 27 }[ 0  ] | { 26 }[ 0  ] | { 26 }[ 0  ] | { 25 }[ 0  ] | { 25 }[ 0  ] | { 24 }[ 0  ] | { 24 }[ 0  ]|
          * | { 23 }[ 0  ] | { 23 }[ 0  ] | { 22 }[ 0  ] | { 22 }[ 0  ] | { 21 }[ 0  ] | { 21 }[ 0  ] | { 20 }[ 0  ] | { 20 }[ 0  ]|
          * | { 19 }[ 0  ] | { 19 }[ 0  ] | { 18 }[ 0  ] | { 18 }[ 0  ] | { 17 }[ 0  ] | { 17 }[ 0  ] | { 16 }[ 0  ] | { 16 }[ 0  ]|
          * | { 15 }[ 0  ] | { 15 }[ 0  ] | { 14 }[ 0  ] | { 14 }[ 0  ] | { 13 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 12 }[ 0  ]|
          * | { 11 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 10 }[ 0  ] | { 9  }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ] | { 8  }[ 0  ]|
          * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint8_t val1 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 1;
         uint8_t val2 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint8_t val3 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 1;
         uint8_t val4 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint8_t val5 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 1;
         uint8_t val6 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 1;
         uint8_t val7 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 1;
         uint8_t val8 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         uint8_t val9 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 1;
         uint8_t val10 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 1;
         uint8_t val11 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 1;
         uint8_t val12 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 1;
         uint8_t val13 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 1;
         uint8_t val14 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 1;
         uint8_t val15 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 1;
         uint8_t val16 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 1;
         uint8_t val17 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 1;
         uint8_t val18 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 1;
         uint8_t val19 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 1;
         uint8_t val20 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 1;
         uint8_t val21 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 1;
         uint8_t val22 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 1;
         uint8_t val23 = *svw.column_data_ptr[ 46 ]; svw.column_data_ptr[ 46 ] += 1;
         uint8_t val24 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 1;
         uint8_t val25 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 1;
         uint8_t val26 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 1;
         uint8_t val27 = *svw.column_data_ptr[ 54 ]; svw.column_data_ptr[ 54 ] += 1;
         uint8_t val28 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 1;
         uint8_t val29 = *svw.column_data_ptr[ 58 ]; svw.column_data_ptr[ 58 ] += 1;
         uint8_t val30 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 1;
         uint8_t val31 = *svw.column_data_ptr[ 62 ]; svw.column_data_ptr[ 62 ] += 1;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val31, val31, val30, val30, val29, val29, val28, val28, val27, val27, val26, val26, val25, val25, val24, val24, val23, val23, val22, val22, val21, val21, val20, val20, val19, val19, val18, val18, val17, val17, val16, val16, val15, val15, val14, val14, val13, val13, val12, val12, val11, val11, val10, val10, val9, val9, val8, val8, val7, val7, val6, val6, val5, val5, val4, val4, val3, val3, val2, val2, val1, val1, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 64 ) && ( NoC == 64 ) && ( std::is_same< VecExt, avx512< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 63 }[ 0  ] | { 62 }[ 0  ] | { 61 }[ 0  ] | { 60 }[ 0  ] | { 59 }[ 0  ] | { 58 }[ 0  ] | { 57 }[ 0  ] | { 56 }[ 0  ]|
          * | { 55 }[ 0  ] | { 54 }[ 0  ] | { 53 }[ 0  ] | { 52 }[ 0  ] | { 51 }[ 0  ] | { 50 }[ 0  ] | { 49 }[ 0  ] | { 48 }[ 0  ]|
          * | { 47 }[ 0  ] | { 46 }[ 0  ] | { 45 }[ 0  ] | { 44 }[ 0  ] | { 43 }[ 0  ] | { 42 }[ 0  ] | { 41 }[ 0  ] | { 40 }[ 0  ]|
          * | { 39 }[ 0  ] | { 38 }[ 0  ] | { 37 }[ 0  ] | { 36 }[ 0  ] | { 35 }[ 0  ] | { 34 }[ 0  ] | { 33 }[ 0  ] | { 32 }[ 0  ]|
          * | { 31 }[ 0  ] | { 30 }[ 0  ] | { 29 }[ 0  ] | { 28 }[ 0  ] | { 27 }[ 0  ] | { 26 }[ 0  ] | { 25 }[ 0  ] | { 24 }[ 0  ]|
          * | { 23 }[ 0  ] | { 22 }[ 0  ] | { 21 }[ 0  ] | { 20 }[ 0  ] | { 19 }[ 0  ] | { 18 }[ 0  ] | { 17 }[ 0  ] | { 16 }[ 0  ]|
          * | { 15 }[ 0  ] | { 14 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ]|
          * | { 7  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint8_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint8_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 1;
         uint8_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 1;
         uint8_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 1;
         uint8_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint8_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 1;
         uint8_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 1;
         uint8_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 1;
         uint8_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint8_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 1;
         uint8_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 1;
         uint8_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 1;
         uint8_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 1;
         uint8_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 1;
         uint8_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 1;
         uint8_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 1;
         uint8_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         uint8_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 1;
         uint8_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 1;
         uint8_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 1;
         uint8_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 1;
         uint8_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 1;
         uint8_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 1;
         uint8_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 1;
         uint8_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 1;
         uint8_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 1;
         uint8_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 1;
         uint8_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 1;
         uint8_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 1;
         uint8_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 1;
         uint8_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 1;
         uint8_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 1;
         uint8_t val32 = *svw.column_data_ptr[ 32 ]; svw.column_data_ptr[ 32 ] += 1;
         uint8_t val33 = *svw.column_data_ptr[ 33 ]; svw.column_data_ptr[ 33 ] += 1;
         uint8_t val34 = *svw.column_data_ptr[ 34 ]; svw.column_data_ptr[ 34 ] += 1;
         uint8_t val35 = *svw.column_data_ptr[ 35 ]; svw.column_data_ptr[ 35 ] += 1;
         uint8_t val36 = *svw.column_data_ptr[ 36 ]; svw.column_data_ptr[ 36 ] += 1;
         uint8_t val37 = *svw.column_data_ptr[ 37 ]; svw.column_data_ptr[ 37 ] += 1;
         uint8_t val38 = *svw.column_data_ptr[ 38 ]; svw.column_data_ptr[ 38 ] += 1;
         uint8_t val39 = *svw.column_data_ptr[ 39 ]; svw.column_data_ptr[ 39 ] += 1;
         uint8_t val40 = *svw.column_data_ptr[ 40 ]; svw.column_data_ptr[ 40 ] += 1;
         uint8_t val41 = *svw.column_data_ptr[ 41 ]; svw.column_data_ptr[ 41 ] += 1;
         uint8_t val42 = *svw.column_data_ptr[ 42 ]; svw.column_data_ptr[ 42 ] += 1;
         uint8_t val43 = *svw.column_data_ptr[ 43 ]; svw.column_data_ptr[ 43 ] += 1;
         uint8_t val44 = *svw.column_data_ptr[ 44 ]; svw.column_data_ptr[ 44 ] += 1;
         uint8_t val45 = *svw.column_data_ptr[ 45 ]; svw.column_data_ptr[ 45 ] += 1;
         uint8_t val46 = *svw.column_data_ptr[ 46 ]; svw.column_data_ptr[ 46 ] += 1;
         uint8_t val47 = *svw.column_data_ptr[ 47 ]; svw.column_data_ptr[ 47 ] += 1;
         uint8_t val48 = *svw.column_data_ptr[ 48 ]; svw.column_data_ptr[ 48 ] += 1;
         uint8_t val49 = *svw.column_data_ptr[ 49 ]; svw.column_data_ptr[ 49 ] += 1;
         uint8_t val50 = *svw.column_data_ptr[ 50 ]; svw.column_data_ptr[ 50 ] += 1;
         uint8_t val51 = *svw.column_data_ptr[ 51 ]; svw.column_data_ptr[ 51 ] += 1;
         uint8_t val52 = *svw.column_data_ptr[ 52 ]; svw.column_data_ptr[ 52 ] += 1;
         uint8_t val53 = *svw.column_data_ptr[ 53 ]; svw.column_data_ptr[ 53 ] += 1;
         uint8_t val54 = *svw.column_data_ptr[ 54 ]; svw.column_data_ptr[ 54 ] += 1;
         uint8_t val55 = *svw.column_data_ptr[ 55 ]; svw.column_data_ptr[ 55 ] += 1;
         uint8_t val56 = *svw.column_data_ptr[ 56 ]; svw.column_data_ptr[ 56 ] += 1;
         uint8_t val57 = *svw.column_data_ptr[ 57 ]; svw.column_data_ptr[ 57 ] += 1;
         uint8_t val58 = *svw.column_data_ptr[ 58 ]; svw.column_data_ptr[ 58 ] += 1;
         uint8_t val59 = *svw.column_data_ptr[ 59 ]; svw.column_data_ptr[ 59 ] += 1;
         uint8_t val60 = *svw.column_data_ptr[ 60 ]; svw.column_data_ptr[ 60 ] += 1;
         uint8_t val61 = *svw.column_data_ptr[ 61 ]; svw.column_data_ptr[ 61 ] += 1;
         uint8_t val62 = *svw.column_data_ptr[ 62 ]; svw.column_data_ptr[ 62 ] += 1;
         uint8_t val63 = *svw.column_data_ptr[ 63 ]; svw.column_data_ptr[ 63 ] += 1;
         typename avx512< uint8_t >::vector_t result = set< avx512< uint8_t > >( val63, val62, val61, val60, val59, val58, val57, val56, val55, val54, val53, val52, val51, val50, val49, val48, val47, val46, val45, val44, val43, val42, val41, val40, val39, val38, val37, val36, val35, val34, val33, val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 31 ] | { 0  }[ 30 ] | { 0  }[ 29 ] | { 0  }[ 28 ] | { 0  }[ 27 ] | { 0  }[ 26 ] | { 0  }[ 25 ] | { 0  }[ 24 ]|
          * | { 0  }[ 23 ] | { 0  }[ 22 ] | { 0  }[ 21 ] | { 0  }[ 20 ] | { 0  }[ 19 ] | { 0  }[ 18 ] | { 0  }[ 17 ] | { 0  }[ 16 ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 32;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 32;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 32;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 32;
         uint16_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 32;
         uint16_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 32;
         uint16_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 32;
         uint16_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 32;
         uint16_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 32;
         uint16_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 32;
         uint16_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 32;
         uint16_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 32;
         uint16_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 32;
         uint16_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 32;
         uint16_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 32;
         uint16_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 32;
         uint16_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 32;
         uint16_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 32;
         uint16_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 32;
         uint16_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 32;
         uint16_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 32;
         uint16_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 32;
         uint16_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 32;
         uint16_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 32;
         uint16_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 32;
         uint16_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 32;
         uint16_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 32;
         uint16_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 32;
         uint16_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 32;
         uint16_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 32;
         uint16_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 32;
         uint16_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 32;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 16;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 16;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 16;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 16;
         uint16_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 16;
         uint16_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 16;
         uint16_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 16;
         uint16_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 16;
         uint16_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 16;
         uint16_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 16;
         uint16_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 16;
         uint16_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 16;
         uint16_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 16;
         uint16_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 16;
         uint16_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 16;
         uint16_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 16;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 15 ] | { 1  }[ 14 ] | { 1  }[ 13 ] | { 1  }[ 12 ] | { 1  }[ 11 ] | { 1  }[ 10 ] | { 1  }[ 9  ] | { 1  }[ 8  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 16;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 16;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 16;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 16;
         uint16_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 16;
         uint16_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 16;
         uint16_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 16;
         uint16_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 16;
         uint16_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 16;
         uint16_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 16;
         uint16_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 16;
         uint16_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 16;
         uint16_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 16;
         uint16_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 16;
         uint16_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 16;
         uint16_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 16;
         uint16_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 16;
         uint16_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 16;
         uint16_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 16;
         uint16_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 16;
         uint16_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 16;
         uint16_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 16;
         uint16_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 16;
         uint16_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 16;
         uint16_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 16;
         uint16_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 16;
         uint16_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 16;
         uint16_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 16;
         uint16_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 16;
         uint16_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 16;
         uint16_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 16;
         uint16_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 16;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint16_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint16_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint16_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint16_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint16_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint16_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint16_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint16_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         uint16_t val8 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 8;
         uint16_t val9 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 8;
         uint16_t val10 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 8;
         uint16_t val11 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 8;
         uint16_t val12 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 8;
         uint16_t val13 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 8;
         uint16_t val14 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 8;
         uint16_t val15 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 8;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val15, val14, val13, val12, val11, val10, val9, val8, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 7  ] | { 3  }[ 6  ] | { 3  }[ 5  ] | { 3  }[ 4  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 7  ] | { 2  }[ 6  ] | { 2  }[ 5  ] | { 2  }[ 4  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint16_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint16_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint16_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint16_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         uint16_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 8;
         uint16_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 8;
         uint16_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 8;
         uint16_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 8;
         uint16_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 8;
         uint16_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 8;
         uint16_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 8;
         uint16_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 8;
         uint16_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 8;
         uint16_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 8;
         uint16_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 8;
         uint16_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 8;
         uint16_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 8;
         uint16_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 8;
         uint16_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 8;
         uint16_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 8;
         uint16_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 8;
         uint16_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 8;
         uint16_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 8;
         uint16_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 8;
         uint16_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 8;
         uint16_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 8;
         uint16_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 8;
         uint16_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 8;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint16_t val4 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 4;
         uint16_t val5 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 4;
         uint16_t val6 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 4;
         uint16_t val7 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 4;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val7, val6, val5, val4, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint16_t val4 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 4;
         uint16_t val5 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 4;
         uint16_t val6 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 4;
         uint16_t val7 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 4;
         uint16_t val8 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 4;
         uint16_t val9 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 4;
         uint16_t val10 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 4;
         uint16_t val11 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 4;
         uint16_t val12 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 4;
         uint16_t val13 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 4;
         uint16_t val14 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 4;
         uint16_t val15 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 4;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val15, val14, val13, val12, val15, val14, val13, val12, val11, val10, val9, val8, val11, val10, val9, val8, val7, val6, val5, val4, val7, val6, val5, val4, val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 3  ] | { 7  }[ 2  ] | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 3  ] | { 6  }[ 2  ] | { 6  }[ 1  ] | { 6  }[ 0  ]|
          * | { 5  }[ 3  ] | { 5  }[ 2  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 3  ] | { 4  }[ 2  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint16_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 4;
         uint16_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 4;
         uint16_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 4;
         uint16_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 4;
         uint16_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 4;
         uint16_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 4;
         uint16_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 4;
         uint16_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 4;
         uint16_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 4;
         uint16_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 4;
         uint16_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 4;
         uint16_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 4;
         uint16_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 4;
         uint16_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 4;
         uint16_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 4;
         uint16_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 4;
         uint16_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 4;
         uint16_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 4;
         uint16_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 4;
         uint16_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 4;
         uint16_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 4;
         uint16_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 4;
         uint16_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 4;
         uint16_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 4;
         uint16_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 4;
         uint16_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 4;
         uint16_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 4;
         uint16_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 4;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint16_t val2 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 2;
         uint16_t val3 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 2;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val3, val2, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint16_t val2 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 2;
         uint16_t val3 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 2;
         uint16_t val4 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 2;
         uint16_t val5 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 2;
         uint16_t val6 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 2;
         uint16_t val7 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 2;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val7, val6, val7, val6, val7, val6, val7, val6, val5, val4, val5, val4, val5, val4, val5, val4, val3, val2, val3, val2, val3, val2, val3, val2, val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ]|
          * | { 5  }[ 1  ] | { 5  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint16_t val2 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 2;
         uint16_t val3 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 2;
         uint16_t val4 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 2;
         uint16_t val5 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 2;
         uint16_t val6 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 2;
         uint16_t val7 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 2;
         uint16_t val8 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 2;
         uint16_t val9 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 2;
         uint16_t val10 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 2;
         uint16_t val11 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 2;
         uint16_t val12 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 2;
         uint16_t val13 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 2;
         uint16_t val14 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 2;
         uint16_t val15 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 2;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val15, val14, val15, val14, val13, val12, val13, val12, val11, val10, val11, val10, val9, val8, val9, val8, val7, val6, val7, val6, val5, val4, val5, val4, val3, val2, val3, val2, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 16 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 15 }[ 1  ] | { 15 }[ 0  ] | { 14 }[ 1  ] | { 14 }[ 0  ] | { 13 }[ 1  ] | { 13 }[ 0  ] | { 12 }[ 1  ] | { 12 }[ 0  ]|
          * | { 11 }[ 1  ] | { 11 }[ 0  ] | { 10 }[ 1  ] | { 10 }[ 0  ] | { 9  }[ 1  ] | { 9  }[ 0  ] | { 8  }[ 1  ] | { 8  }[ 0  ]|
          * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 2;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 2;
         uint16_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 2;
         uint16_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 2;
         uint16_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 2;
         uint16_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 2;
         uint16_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 2;
         uint16_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 2;
         uint16_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 2;
         uint16_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 2;
         uint16_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 2;
         uint16_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 2;
         uint16_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 2;
         uint16_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 2;
         uint16_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 2;
         uint16_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 2;
         uint16_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 2;
         uint16_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 2;
         uint16_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 2;
         uint16_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 2;
         uint16_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 2;
         uint16_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 2;
         uint16_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 2;
         uint16_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 2;
         uint16_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 2;
         uint16_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 2;
         uint16_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 2;
         uint16_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 2;
         uint16_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 2;
         uint16_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 2;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint16_t val1 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val1, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ]|
          * | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint16_t val1 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint16_t val2 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         uint16_t val3 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 1;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val3, val3, val3, val3, val3, val3, val3, val3, val2, val2, val2, val2, val2, val2, val2, val2, val1, val1, val1, val1, val1, val1, val1, val1, val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ]|
          * | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint16_t val1 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint16_t val2 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint16_t val3 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 1;
         uint16_t val4 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         uint16_t val5 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 1;
         uint16_t val6 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 1;
         uint16_t val7 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 1;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val7, val7, val7, val7, val6, val6, val6, val6, val5, val5, val5, val5, val4, val4, val4, val4, val3, val3, val3, val3, val2, val2, val2, val2, val1, val1, val1, val1, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 16 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 15 }[ 0  ] | { 15 }[ 0  ] | { 14 }[ 0  ] | { 14 }[ 0  ] | { 13 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 12 }[ 0  ]|
          * | { 11 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 10 }[ 0  ] | { 9  }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ] | { 8  }[ 0  ]|
          * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint16_t val1 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 1;
         uint16_t val2 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint16_t val3 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 1;
         uint16_t val4 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint16_t val5 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 1;
         uint16_t val6 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 1;
         uint16_t val7 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 1;
         uint16_t val8 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         uint16_t val9 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 1;
         uint16_t val10 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 1;
         uint16_t val11 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 1;
         uint16_t val12 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 1;
         uint16_t val13 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 1;
         uint16_t val14 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 1;
         uint16_t val15 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 1;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val15, val15, val14, val14, val13, val13, val12, val12, val11, val11, val10, val10, val9, val9, val8, val8, val7, val7, val6, val6, val5, val5, val4, val4, val3, val3, val2, val2, val1, val1, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 32 ) && ( std::is_same< VecExt, avx512< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 31 }[ 0  ] | { 30 }[ 0  ] | { 29 }[ 0  ] | { 28 }[ 0  ] | { 27 }[ 0  ] | { 26 }[ 0  ] | { 25 }[ 0  ] | { 24 }[ 0  ]|
          * | { 23 }[ 0  ] | { 22 }[ 0  ] | { 21 }[ 0  ] | { 20 }[ 0  ] | { 19 }[ 0  ] | { 18 }[ 0  ] | { 17 }[ 0  ] | { 16 }[ 0  ]|
          * | { 15 }[ 0  ] | { 14 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ]|
          * | { 7  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint16_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint16_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 1;
         uint16_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 1;
         uint16_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 1;
         uint16_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint16_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 1;
         uint16_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 1;
         uint16_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 1;
         uint16_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint16_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 1;
         uint16_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 1;
         uint16_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 1;
         uint16_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 1;
         uint16_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 1;
         uint16_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 1;
         uint16_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 1;
         uint16_t val16 = *svw.column_data_ptr[ 16 ]; svw.column_data_ptr[ 16 ] += 1;
         uint16_t val17 = *svw.column_data_ptr[ 17 ]; svw.column_data_ptr[ 17 ] += 1;
         uint16_t val18 = *svw.column_data_ptr[ 18 ]; svw.column_data_ptr[ 18 ] += 1;
         uint16_t val19 = *svw.column_data_ptr[ 19 ]; svw.column_data_ptr[ 19 ] += 1;
         uint16_t val20 = *svw.column_data_ptr[ 20 ]; svw.column_data_ptr[ 20 ] += 1;
         uint16_t val21 = *svw.column_data_ptr[ 21 ]; svw.column_data_ptr[ 21 ] += 1;
         uint16_t val22 = *svw.column_data_ptr[ 22 ]; svw.column_data_ptr[ 22 ] += 1;
         uint16_t val23 = *svw.column_data_ptr[ 23 ]; svw.column_data_ptr[ 23 ] += 1;
         uint16_t val24 = *svw.column_data_ptr[ 24 ]; svw.column_data_ptr[ 24 ] += 1;
         uint16_t val25 = *svw.column_data_ptr[ 25 ]; svw.column_data_ptr[ 25 ] += 1;
         uint16_t val26 = *svw.column_data_ptr[ 26 ]; svw.column_data_ptr[ 26 ] += 1;
         uint16_t val27 = *svw.column_data_ptr[ 27 ]; svw.column_data_ptr[ 27 ] += 1;
         uint16_t val28 = *svw.column_data_ptr[ 28 ]; svw.column_data_ptr[ 28 ] += 1;
         uint16_t val29 = *svw.column_data_ptr[ 29 ]; svw.column_data_ptr[ 29 ] += 1;
         uint16_t val30 = *svw.column_data_ptr[ 30 ]; svw.column_data_ptr[ 30 ] += 1;
         uint16_t val31 = *svw.column_data_ptr[ 31 ]; svw.column_data_ptr[ 31 ] += 1;
         typename avx512< uint16_t >::vector_t result = set< avx512< uint16_t > >( val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 16;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 16;
         uint32_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 16;
         uint32_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 16;
         uint32_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 16;
         uint32_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 16;
         uint32_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 16;
         uint32_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 16;
         uint32_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 16;
         uint32_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 16;
         uint32_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 16;
         uint32_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 16;
         uint32_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 16;
         uint32_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 16;
         uint32_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 16;
         uint32_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 16;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint32_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint32_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint32_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint32_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint32_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint32_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val7, val6, val5, val4, val3, val2, val1, val0, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint32_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint32_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint32_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint32_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint32_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint32_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         uint32_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 8;
         uint32_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 8;
         uint32_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 8;
         uint32_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 8;
         uint32_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 8;
         uint32_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 8;
         uint32_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 8;
         uint32_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 8;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint32_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint32_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint32_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint32_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint32_t val4 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 4;
         uint32_t val5 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 4;
         uint32_t val6 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 4;
         uint32_t val7 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 4;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val7, val6, val5, val4, val7, val6, val5, val4, val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint32_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint32_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint32_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 4;
         uint32_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 4;
         uint32_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 4;
         uint32_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 4;
         uint32_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 4;
         uint32_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 4;
         uint32_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 4;
         uint32_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 4;
         uint32_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 4;
         uint32_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 4;
         uint32_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 4;
         uint32_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 4;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint32_t val2 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 2;
         uint32_t val3 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 2;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val3, val2, val3, val2, val3, val2, val3, val2, val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint32_t val2 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 2;
         uint32_t val3 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 2;
         uint32_t val4 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 2;
         uint32_t val5 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 2;
         uint32_t val6 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 2;
         uint32_t val7 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 2;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val7, val6, val7, val6, val5, val4, val5, val4, val3, val2, val3, val2, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint32_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 2;
         uint32_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 2;
         uint32_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 2;
         uint32_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 2;
         uint32_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 2;
         uint32_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 2;
         uint32_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 2;
         uint32_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 2;
         uint32_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 2;
         uint32_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 2;
         uint32_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 2;
         uint32_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 2;
         uint32_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 2;
         uint32_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 2;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint32_t val1 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val1, val1, val1, val1, val1, val1, val1, val1, val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint32_t val1 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint32_t val2 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint32_t val3 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 1;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val3, val3, val3, val3, val2, val2, val2, val2, val1, val1, val1, val1, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint32_t val1 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 1;
         uint32_t val2 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint32_t val3 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 1;
         uint32_t val4 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint32_t val5 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 1;
         uint32_t val6 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 1;
         uint32_t val7 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 1;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val7, val7, val6, val6, val5, val5, val4, val4, val3, val3, val2, val2, val1, val1, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 16 ) && ( std::is_same< VecExt, avx512< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 15 }[ 0  ] | { 14 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ]|
          * | { 7  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint32_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint32_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 1;
         uint32_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 1;
         uint32_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 1;
         uint32_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint32_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 1;
         uint32_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 1;
         uint32_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 1;
         uint32_t val8 = *svw.column_data_ptr[ 8 ]; svw.column_data_ptr[ 8 ] += 1;
         uint32_t val9 = *svw.column_data_ptr[ 9 ]; svw.column_data_ptr[ 9 ] += 1;
         uint32_t val10 = *svw.column_data_ptr[ 10 ]; svw.column_data_ptr[ 10 ] += 1;
         uint32_t val11 = *svw.column_data_ptr[ 11 ]; svw.column_data_ptr[ 11 ] += 1;
         uint32_t val12 = *svw.column_data_ptr[ 12 ]; svw.column_data_ptr[ 12 ] += 1;
         uint32_t val13 = *svw.column_data_ptr[ 13 ]; svw.column_data_ptr[ 13 ] += 1;
         uint32_t val14 = *svw.column_data_ptr[ 14 ]; svw.column_data_ptr[ 14 ] += 1;
         uint32_t val15 = *svw.column_data_ptr[ 15 ]; svw.column_data_ptr[ 15 ] += 1;
         typename avx512< uint32_t >::vector_t result = set< avx512< uint32_t > >( val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 8;
         uint64_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 8;
         uint64_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 8;
         uint64_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 8;
         uint64_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 8;
         uint64_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 8;
         uint64_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 8;
         uint64_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 8;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint64_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint64_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint64_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val3, val2, val1, val0, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 4;
         uint64_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 4;
         uint64_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 4;
         uint64_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 4;
         uint64_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 4;
         uint64_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 4;
         uint64_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 4;
         uint64_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 4;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint64_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val1, val0, val1, val0, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint64_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint64_t val2 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 2;
         uint64_t val3 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 2;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val3, val2, val3, val2, val1, val0, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 2;
         uint64_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 2;
         uint64_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 2;
         uint64_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 2;
         uint64_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 2;
         uint64_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 2;
         uint64_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 2;
         uint64_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 2;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val0, val0, val0, val0, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint64_t val1 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val1, val1, val1, val1, val0, val0, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint64_t val1 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 1;
         uint64_t val2 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint64_t val3 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 1;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val3, val3, val2, val2, val1, val1, val0, val0 );
         return result;
      }
                      
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx512< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx512< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         uint64_t val0 = *svw.column_data_ptr[ 0 ]; svw.column_data_ptr[ 0 ] += 1;
         uint64_t val1 = *svw.column_data_ptr[ 1 ]; svw.column_data_ptr[ 1 ] += 1;
         uint64_t val2 = *svw.column_data_ptr[ 2 ]; svw.column_data_ptr[ 2 ] += 1;
         uint64_t val3 = *svw.column_data_ptr[ 3 ]; svw.column_data_ptr[ 3 ] += 1;
         uint64_t val4 = *svw.column_data_ptr[ 4 ]; svw.column_data_ptr[ 4 ] += 1;
         uint64_t val5 = *svw.column_data_ptr[ 5 ]; svw.column_data_ptr[ 5 ] += 1;
         uint64_t val6 = *svw.column_data_ptr[ 6 ]; svw.column_data_ptr[ 6 ] += 1;
         uint64_t val7 = *svw.column_data_ptr[ 7 ]; svw.column_data_ptr[ 7 ] += 1;
         typename avx512< uint64_t >::vector_t result = set< avx512< uint64_t > >( val7, val6, val5, val4, val3, val2, val1, val0 );
         return result;
      }
                      
   };
} 
#endif
        