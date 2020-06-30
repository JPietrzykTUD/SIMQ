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

#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_MASK_BROADCAST_INTEL_IMPL_AVX2_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_MASK_BROADCAST_INTEL_IMPL_AVX2_H
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
   struct simq_vector_builder_mask_broadcast_t< ColumnContainer, NumberOfQueries, DepT, avx2< DepT > > { 
      using VectorExtension = typename ColumnContainer::vector_extension_t;
      using T = typename VectorExtension::base_t;
      static constexpr char const * get_name( void ) { return "BROADCAST"; }
            
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 31 ] | { 0  }[ 30 ] | { 0  }[ 29 ] | { 0  }[ 28 ] | { 0  }[ 27 ] | { 0  }[ 26 ] | { 0  }[ 25 ] | { 0  }[ 24 ]|
          * | { 0  }[ 23 ] | { 0  }[ 22 ] | { 0  }[ 21 ] | { 0  }[ 20 ] | { 0  }[ 19 ] | { 0  }[ 18 ] | { 0  }[ 17 ] | { 0  }[ 16 ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000000000000010, result);
         svw.column_data_ptr[ 1 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000000000000000100, result);
         svw.column_data_ptr[ 2 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000000000000000000001000, result);
         svw.column_data_ptr[ 3 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000000000000010000, result);
         svw.column_data_ptr[ 4 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00000000000000000000000000100000, result);
         svw.column_data_ptr[ 5 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b00000000000000000000000001000000, result);
         svw.column_data_ptr[ 6 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b00000000000000000000000010000000, result);
         svw.column_data_ptr[ 7 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000000000100000000, result);
         svw.column_data_ptr[ 8 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000000000000000000001000000000, result);
         svw.column_data_ptr[ 9 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b00000000000000000000010000000000, result);
         svw.column_data_ptr[ 10 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b00000000000000000000100000000000, result);
         svw.column_data_ptr[ 11 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00000000000000000001000000000000, result);
         svw.column_data_ptr[ 12 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b00000000000000000010000000000000, result);
         svw.column_data_ptr[ 13 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b00000000000000000100000000000000, result);
         svw.column_data_ptr[ 14 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b00000000000000001000000000000000, result);
         svw.column_data_ptr[ 15 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000000010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000000000000100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b00000000000001000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[19], 0b00000000000010000000000000000000, result);
         svw.column_data_ptr[ 19 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00000000000100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[21], 0b00000000001000000000000000000000, result);
         svw.column_data_ptr[ 21 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[22], 0b00000000010000000000000000000000, result);
         svw.column_data_ptr[ 22 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[23], 0b00000000100000000000000000000000, result);
         svw.column_data_ptr[ 23 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00000001000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[25], 0b00000010000000000000000000000000, result);
         svw.column_data_ptr[ 25 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[26], 0b00000100000000000000000000000000, result);
         svw.column_data_ptr[ 26 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[27], 0b00001000000000000000000000000000, result);
         svw.column_data_ptr[ 27 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[28], 0b00010000000000000000000000000000, result);
         svw.column_data_ptr[ 28 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[29], 0b00100000000000000000000000000000, result);
         svw.column_data_ptr[ 29 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[30], 0b01000000000000000000000000000000, result);
         svw.column_data_ptr[ 30 ] += 32;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[31], 0b10000000000000000000000000000000, result);
         svw.column_data_ptr[ 31 ] += 32;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000100000000000000010, result);
         svw.column_data_ptr[ 1 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000001000000000000000100, result);
         svw.column_data_ptr[ 2 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000010000000000000001000, result);
         svw.column_data_ptr[ 3 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000100000000000000010000, result);
         svw.column_data_ptr[ 4 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00000000001000000000000000100000, result);
         svw.column_data_ptr[ 5 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b00000000010000000000000001000000, result);
         svw.column_data_ptr[ 6 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b00000000100000000000000010000000, result);
         svw.column_data_ptr[ 7 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000001000000000000000100000000, result);
         svw.column_data_ptr[ 8 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000010000000000000001000000000, result);
         svw.column_data_ptr[ 9 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b00000100000000000000010000000000, result);
         svw.column_data_ptr[ 10 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b00001000000000000000100000000000, result);
         svw.column_data_ptr[ 11 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00010000000000000001000000000000, result);
         svw.column_data_ptr[ 12 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b00100000000000000010000000000000, result);
         svw.column_data_ptr[ 13 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b01000000000000000100000000000000, result);
         svw.column_data_ptr[ 14 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b10000000000000001000000000000000, result);
         svw.column_data_ptr[ 15 ] += 16;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 15 ] | { 1  }[ 14 ] | { 1  }[ 13 ] | { 1  }[ 12 ] | { 1  }[ 11 ] | { 1  }[ 10 ] | { 1  }[ 9  ] | { 1  }[ 8  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000000000000010, result);
         svw.column_data_ptr[ 1 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000000000000000100, result);
         svw.column_data_ptr[ 2 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000000000000000000001000, result);
         svw.column_data_ptr[ 3 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000000000000010000, result);
         svw.column_data_ptr[ 4 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00000000000000000000000000100000, result);
         svw.column_data_ptr[ 5 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b00000000000000000000000001000000, result);
         svw.column_data_ptr[ 6 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b00000000000000000000000010000000, result);
         svw.column_data_ptr[ 7 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000000000100000000, result);
         svw.column_data_ptr[ 8 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000000000000000000001000000000, result);
         svw.column_data_ptr[ 9 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b00000000000000000000010000000000, result);
         svw.column_data_ptr[ 10 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b00000000000000000000100000000000, result);
         svw.column_data_ptr[ 11 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00000000000000000001000000000000, result);
         svw.column_data_ptr[ 12 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b00000000000000000010000000000000, result);
         svw.column_data_ptr[ 13 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b00000000000000000100000000000000, result);
         svw.column_data_ptr[ 14 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b00000000000000001000000000000000, result);
         svw.column_data_ptr[ 15 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000000010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000000000000100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b00000000000001000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[19], 0b00000000000010000000000000000000, result);
         svw.column_data_ptr[ 19 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00000000000100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[21], 0b00000000001000000000000000000000, result);
         svw.column_data_ptr[ 21 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[22], 0b00000000010000000000000000000000, result);
         svw.column_data_ptr[ 22 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[23], 0b00000000100000000000000000000000, result);
         svw.column_data_ptr[ 23 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00000001000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[25], 0b00000010000000000000000000000000, result);
         svw.column_data_ptr[ 25 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[26], 0b00000100000000000000000000000000, result);
         svw.column_data_ptr[ 26 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[27], 0b00001000000000000000000000000000, result);
         svw.column_data_ptr[ 27 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[28], 0b00010000000000000000000000000000, result);
         svw.column_data_ptr[ 28 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[29], 0b00100000000000000000000000000000, result);
         svw.column_data_ptr[ 29 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[30], 0b01000000000000000000000000000000, result);
         svw.column_data_ptr[ 30 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[31], 0b10000000000000000000000000000000, result);
         svw.column_data_ptr[ 31 ] += 16;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000010000000100000001000000010, result);
         svw.column_data_ptr[ 1 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000100000001000000010000000100, result);
         svw.column_data_ptr[ 2 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00001000000010000000100000001000, result);
         svw.column_data_ptr[ 3 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00010000000100000001000000010000, result);
         svw.column_data_ptr[ 4 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00100000001000000010000000100000, result);
         svw.column_data_ptr[ 5 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b01000000010000000100000001000000, result);
         svw.column_data_ptr[ 6 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b10000000100000001000000010000000, result);
         svw.column_data_ptr[ 7 ] += 8;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000001000000010, result);
         svw.column_data_ptr[ 1 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000000010000000100, result);
         svw.column_data_ptr[ 2 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000000000000100000001000, result);
         svw.column_data_ptr[ 3 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000001000000010000, result);
         svw.column_data_ptr[ 4 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00000000000000000010000000100000, result);
         svw.column_data_ptr[ 5 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b00000000000000000100000001000000, result);
         svw.column_data_ptr[ 6 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b00000000000000001000000010000000, result);
         svw.column_data_ptr[ 7 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000001000000010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000010000000100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b00000100000001000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[19], 0b00001000000010000000000000000000, result);
         svw.column_data_ptr[ 19 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00010000000100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[21], 0b00100000001000000000000000000000, result);
         svw.column_data_ptr[ 21 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[22], 0b01000000010000000000000000000000, result);
         svw.column_data_ptr[ 22 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[23], 0b10000000100000000000000000000000, result);
         svw.column_data_ptr[ 23 ] += 8;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 7  ] | { 3  }[ 6  ] | { 3  }[ 5  ] | { 3  }[ 4  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 7  ] | { 2  }[ 6  ] | { 2  }[ 5  ] | { 2  }[ 4  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000000000000010, result);
         svw.column_data_ptr[ 1 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000000000000000100, result);
         svw.column_data_ptr[ 2 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000000000000000000001000, result);
         svw.column_data_ptr[ 3 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000000000000010000, result);
         svw.column_data_ptr[ 4 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00000000000000000000000000100000, result);
         svw.column_data_ptr[ 5 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b00000000000000000000000001000000, result);
         svw.column_data_ptr[ 6 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b00000000000000000000000010000000, result);
         svw.column_data_ptr[ 7 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000000000100000000, result);
         svw.column_data_ptr[ 8 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000000000000000000001000000000, result);
         svw.column_data_ptr[ 9 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b00000000000000000000010000000000, result);
         svw.column_data_ptr[ 10 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b00000000000000000000100000000000, result);
         svw.column_data_ptr[ 11 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00000000000000000001000000000000, result);
         svw.column_data_ptr[ 12 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b00000000000000000010000000000000, result);
         svw.column_data_ptr[ 13 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b00000000000000000100000000000000, result);
         svw.column_data_ptr[ 14 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b00000000000000001000000000000000, result);
         svw.column_data_ptr[ 15 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000000010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000000000000100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b00000000000001000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[19], 0b00000000000010000000000000000000, result);
         svw.column_data_ptr[ 19 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00000000000100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[21], 0b00000000001000000000000000000000, result);
         svw.column_data_ptr[ 21 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[22], 0b00000000010000000000000000000000, result);
         svw.column_data_ptr[ 22 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[23], 0b00000000100000000000000000000000, result);
         svw.column_data_ptr[ 23 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00000001000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[25], 0b00000010000000000000000000000000, result);
         svw.column_data_ptr[ 25 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[26], 0b00000100000000000000000000000000, result);
         svw.column_data_ptr[ 26 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[27], 0b00001000000000000000000000000000, result);
         svw.column_data_ptr[ 27 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[28], 0b00010000000000000000000000000000, result);
         svw.column_data_ptr[ 28 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[29], 0b00100000000000000000000000000000, result);
         svw.column_data_ptr[ 29 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[30], 0b01000000000000000000000000000000, result);
         svw.column_data_ptr[ 30 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[31], 0b10000000000000000000000000000000, result);
         svw.column_data_ptr[ 31 ] += 8;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00100010001000100010001000100010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b01000100010001000100010001000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b10001000100010001000100010001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000010001000100010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000100010001000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000000001000100010001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00010001000100010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00100010001000100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b01000100010001000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[19], 0b10001000100010000000000000000000, result);
         svw.column_data_ptr[ 19 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000000000100010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000000000001000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000000000000000010001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000001000100000000, result);
         svw.column_data_ptr[ 8 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000000000000000010001000000000, result);
         svw.column_data_ptr[ 9 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b00000000000000000100010000000000, result);
         svw.column_data_ptr[ 10 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b00000000000000001000100000000000, result);
         svw.column_data_ptr[ 11 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000100010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000000001000100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b00000000010001000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[19], 0b00000000100010000000000000000000, result);
         svw.column_data_ptr[ 19 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00010001000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[25], 0b00100010000000000000000000000000, result);
         svw.column_data_ptr[ 25 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[26], 0b01000100000000000000000000000000, result);
         svw.column_data_ptr[ 26 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[27], 0b10001000000000000000000000000000, result);
         svw.column_data_ptr[ 27 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 3  ] | { 7  }[ 2  ] | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 3  ] | { 6  }[ 2  ] | { 6  }[ 1  ] | { 6  }[ 0  ]|
          * | { 5  }[ 3  ] | { 5  }[ 2  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 3  ] | { 4  }[ 2  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000000000000010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000000000000000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000000000000000000001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000000000000010000, result);
         svw.column_data_ptr[ 4 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00000000000000000000000000100000, result);
         svw.column_data_ptr[ 5 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b00000000000000000000000001000000, result);
         svw.column_data_ptr[ 6 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b00000000000000000000000010000000, result);
         svw.column_data_ptr[ 7 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000000000100000000, result);
         svw.column_data_ptr[ 8 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000000000000000000001000000000, result);
         svw.column_data_ptr[ 9 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b00000000000000000000010000000000, result);
         svw.column_data_ptr[ 10 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b00000000000000000000100000000000, result);
         svw.column_data_ptr[ 11 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00000000000000000001000000000000, result);
         svw.column_data_ptr[ 12 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b00000000000000000010000000000000, result);
         svw.column_data_ptr[ 13 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b00000000000000000100000000000000, result);
         svw.column_data_ptr[ 14 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b00000000000000001000000000000000, result);
         svw.column_data_ptr[ 15 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000000010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000000000000100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b00000000000001000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[19], 0b00000000000010000000000000000000, result);
         svw.column_data_ptr[ 19 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00000000000100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[21], 0b00000000001000000000000000000000, result);
         svw.column_data_ptr[ 21 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[22], 0b00000000010000000000000000000000, result);
         svw.column_data_ptr[ 22 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[23], 0b00000000100000000000000000000000, result);
         svw.column_data_ptr[ 23 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00000001000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[25], 0b00000010000000000000000000000000, result);
         svw.column_data_ptr[ 25 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[26], 0b00000100000000000000000000000000, result);
         svw.column_data_ptr[ 26 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[27], 0b00001000000000000000000000000000, result);
         svw.column_data_ptr[ 27 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[28], 0b00010000000000000000000000000000, result);
         svw.column_data_ptr[ 28 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[29], 0b00100000000000000000000000000000, result);
         svw.column_data_ptr[ 29 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[30], 0b01000000000000000000000000000000, result);
         svw.column_data_ptr[ 30 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[31], 0b10000000000000000000000000000000, result);
         svw.column_data_ptr[ 31 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b10101010101010101010101010101010, result);
         svw.column_data_ptr[ 1 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000001010101010101010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b01010101010101010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b10101010101010100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ]|
          * | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000000010101010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000101010100000000, result);
         svw.column_data_ptr[ 8 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000000000000001010101000000000, result);
         svw.column_data_ptr[ 9 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000010101010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000000101010100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b01010101000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[25], 0b10101010000000000000000000000000, result);
         svw.column_data_ptr[ 25 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ]|
          * | { 5  }[ 1  ] | { 5  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000000000001010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000000000001010000, result);
         svw.column_data_ptr[ 4 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00000000000000000000000010100000, result);
         svw.column_data_ptr[ 5 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000000010100000000, result);
         svw.column_data_ptr[ 8 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000000000000000000101000000000, result);
         svw.column_data_ptr[ 9 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00000000000000000101000000000000, result);
         svw.column_data_ptr[ 12 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b00000000000000001010000000000000, result);
         svw.column_data_ptr[ 13 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000001010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000000000010100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00000000010100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[21], 0b00000000101000000000000000000000, result);
         svw.column_data_ptr[ 21 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00000101000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[25], 0b00001010000000000000000000000000, result);
         svw.column_data_ptr[ 25 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[28], 0b01010000000000000000000000000000, result);
         svw.column_data_ptr[ 28 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[29], 0b10100000000000000000000000000000, result);
         svw.column_data_ptr[ 29 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 16 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 15 }[ 1  ] | { 15 }[ 0  ] | { 14 }[ 1  ] | { 14 }[ 0  ] | { 13 }[ 1  ] | { 13 }[ 0  ] | { 12 }[ 1  ] | { 12 }[ 0  ]|
          * | { 11 }[ 1  ] | { 11 }[ 0  ] | { 10 }[ 1  ] | { 10 }[ 0  ] | { 9  }[ 1  ] | { 9  }[ 0  ] | { 8  }[ 1  ] | { 8  }[ 0  ]|
          * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000000000000010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000000000000000100, result);
         svw.column_data_ptr[ 2 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000000000000000000001000, result);
         svw.column_data_ptr[ 3 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000000000000010000, result);
         svw.column_data_ptr[ 4 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00000000000000000000000000100000, result);
         svw.column_data_ptr[ 5 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b00000000000000000000000001000000, result);
         svw.column_data_ptr[ 6 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b00000000000000000000000010000000, result);
         svw.column_data_ptr[ 7 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000000000100000000, result);
         svw.column_data_ptr[ 8 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000000000000000000001000000000, result);
         svw.column_data_ptr[ 9 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b00000000000000000000010000000000, result);
         svw.column_data_ptr[ 10 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b00000000000000000000100000000000, result);
         svw.column_data_ptr[ 11 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00000000000000000001000000000000, result);
         svw.column_data_ptr[ 12 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b00000000000000000010000000000000, result);
         svw.column_data_ptr[ 13 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b00000000000000000100000000000000, result);
         svw.column_data_ptr[ 14 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b00000000000000001000000000000000, result);
         svw.column_data_ptr[ 15 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000000010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000000000000100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b00000000000001000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[19], 0b00000000000010000000000000000000, result);
         svw.column_data_ptr[ 19 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00000000000100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[21], 0b00000000001000000000000000000000, result);
         svw.column_data_ptr[ 21 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[22], 0b00000000010000000000000000000000, result);
         svw.column_data_ptr[ 22 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[23], 0b00000000100000000000000000000000, result);
         svw.column_data_ptr[ 23 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00000001000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[25], 0b00000010000000000000000000000000, result);
         svw.column_data_ptr[ 25 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[26], 0b00000100000000000000000000000000, result);
         svw.column_data_ptr[ 26 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[27], 0b00001000000000000000000000000000, result);
         svw.column_data_ptr[ 27 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[28], 0b00010000000000000000000000000000, result);
         svw.column_data_ptr[ 28 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[29], 0b00100000000000000000000000000000, result);
         svw.column_data_ptr[ 29 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[30], 0b01000000000000000000000000000000, result);
         svw.column_data_ptr[ 30 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[31], 0b10000000000000000000000000000000, result);
         svw.column_data_ptr[ 31 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
      
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b11111111111111110000000000000000, result);
         svw.column_data_ptr[ 16 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ]|
          * | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000001111111100000000, result);
         svw.column_data_ptr[ 8 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000111111110000000000000000, result);
         svw.column_data_ptr[ 16 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b11111111000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 7  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ]|
          * | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000000000011110000, result);
         svw.column_data_ptr[ 4 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000000111100000000, result);
         svw.column_data_ptr[ 8 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00000000000000001111000000000000, result);
         svw.column_data_ptr[ 12 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000011110000000000000000, result);
         svw.column_data_ptr[ 16 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00000000111100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00001111000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[28], 0b11110000000000000000000000000000, result);
         svw.column_data_ptr[ 28 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 16 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 15 }[ 0  ] | { 15 }[ 0  ] | { 14 }[ 0  ] | { 14 }[ 0  ] | { 13 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 12 }[ 0  ]|
          * | { 11 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 10 }[ 0  ] | { 9  }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ] | { 8  }[ 0  ]|
          * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000000000000001100, result);
         svw.column_data_ptr[ 2 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000000000000110000, result);
         svw.column_data_ptr[ 4 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b00000000000000000000000011000000, result);
         svw.column_data_ptr[ 6 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000000001100000000, result);
         svw.column_data_ptr[ 8 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b00000000000000000000110000000000, result);
         svw.column_data_ptr[ 10 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00000000000000000011000000000000, result);
         svw.column_data_ptr[ 12 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b00000000000000001100000000000000, result);
         svw.column_data_ptr[ 14 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000000110000000000000000, result);
         svw.column_data_ptr[ 16 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b00000000000011000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00000000001100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[22], 0b00000000110000000000000000000000, result);
         svw.column_data_ptr[ 22 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00000011000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[26], 0b00001100000000000000000000000000, result);
         svw.column_data_ptr[ 26 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[28], 0b00110000000000000000000000000000, result);
         svw.column_data_ptr[ 28 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[30], 0b11000000000000000000000000000000, result);
         svw.column_data_ptr[ 30 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 32 ) && ( NoC == 32 ) && ( std::is_same< VecExt, avx2< uint8_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint8_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 31 }[ 0  ] | { 30 }[ 0  ] | { 29 }[ 0  ] | { 28 }[ 0  ] | { 27 }[ 0  ] | { 26 }[ 0  ] | { 25 }[ 0  ] | { 24 }[ 0  ]|
          * | { 23 }[ 0  ] | { 22 }[ 0  ] | { 21 }[ 0  ] | { 20 }[ 0  ] | { 19 }[ 0  ] | { 18 }[ 0  ] | { 17 }[ 0  ] | { 16 }[ 0  ]|
          * | { 15 }[ 0  ] | { 14 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ]|
          * | { 7  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint8_t >::vector_t result = broadcast< avx2< uint8_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000000000000000000000000000010, result);
         svw.column_data_ptr[ 1 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000000000000000000000000000100, result);
         svw.column_data_ptr[ 2 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00000000000000000000000000001000, result);
         svw.column_data_ptr[ 3 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00000000000000000000000000010000, result);
         svw.column_data_ptr[ 4 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00000000000000000000000000100000, result);
         svw.column_data_ptr[ 5 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b00000000000000000000000001000000, result);
         svw.column_data_ptr[ 6 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b00000000000000000000000010000000, result);
         svw.column_data_ptr[ 7 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b00000000000000000000000100000000, result);
         svw.column_data_ptr[ 8 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b00000000000000000000001000000000, result);
         svw.column_data_ptr[ 9 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b00000000000000000000010000000000, result);
         svw.column_data_ptr[ 10 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b00000000000000000000100000000000, result);
         svw.column_data_ptr[ 11 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b00000000000000000001000000000000, result);
         svw.column_data_ptr[ 12 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b00000000000000000010000000000000, result);
         svw.column_data_ptr[ 13 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b00000000000000000100000000000000, result);
         svw.column_data_ptr[ 14 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b00000000000000001000000000000000, result);
         svw.column_data_ptr[ 15 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[16], 0b00000000000000010000000000000000, result);
         svw.column_data_ptr[ 16 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[17], 0b00000000000000100000000000000000, result);
         svw.column_data_ptr[ 17 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[18], 0b00000000000001000000000000000000, result);
         svw.column_data_ptr[ 18 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[19], 0b00000000000010000000000000000000, result);
         svw.column_data_ptr[ 19 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[20], 0b00000000000100000000000000000000, result);
         svw.column_data_ptr[ 20 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[21], 0b00000000001000000000000000000000, result);
         svw.column_data_ptr[ 21 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[22], 0b00000000010000000000000000000000, result);
         svw.column_data_ptr[ 22 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[23], 0b00000000100000000000000000000000, result);
         svw.column_data_ptr[ 23 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[24], 0b00000001000000000000000000000000, result);
         svw.column_data_ptr[ 24 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[25], 0b00000010000000000000000000000000, result);
         svw.column_data_ptr[ 25 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[26], 0b00000100000000000000000000000000, result);
         svw.column_data_ptr[ 26 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[27], 0b00001000000000000000000000000000, result);
         svw.column_data_ptr[ 27 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[28], 0b00010000000000000000000000000000, result);
         svw.column_data_ptr[ 28 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[29], 0b00100000000000000000000000000000, result);
         svw.column_data_ptr[ 29 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[30], 0b01000000000000000000000000000000, result);
         svw.column_data_ptr[ 30 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[31], 0b10000000000000000000000000000000, result);
         svw.column_data_ptr[ 31 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 15 ] | { 0  }[ 14 ] | { 0  }[ 13 ] | { 0  }[ 12 ] | { 0  }[ 11 ] | { 0  }[ 10 ] | { 0  }[ 9  ] | { 0  }[ 8  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0000000000000010, result);
         svw.column_data_ptr[ 1 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b0000000000000100, result);
         svw.column_data_ptr[ 2 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b0000000000001000, result);
         svw.column_data_ptr[ 3 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b0000000000010000, result);
         svw.column_data_ptr[ 4 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b0000000000100000, result);
         svw.column_data_ptr[ 5 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b0000000001000000, result);
         svw.column_data_ptr[ 6 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b0000000010000000, result);
         svw.column_data_ptr[ 7 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0000000100000000, result);
         svw.column_data_ptr[ 8 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b0000001000000000, result);
         svw.column_data_ptr[ 9 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b0000010000000000, result);
         svw.column_data_ptr[ 10 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b0000100000000000, result);
         svw.column_data_ptr[ 11 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b0001000000000000, result);
         svw.column_data_ptr[ 12 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b0010000000000000, result);
         svw.column_data_ptr[ 13 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b0100000000000000, result);
         svw.column_data_ptr[ 14 ] += 16;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b1000000000000000, result);
         svw.column_data_ptr[ 15 ] += 16;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0000001000000010, result);
         svw.column_data_ptr[ 1 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b0000010000000100, result);
         svw.column_data_ptr[ 2 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b0000100000001000, result);
         svw.column_data_ptr[ 3 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b0001000000010000, result);
         svw.column_data_ptr[ 4 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b0010000000100000, result);
         svw.column_data_ptr[ 5 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b0100000001000000, result);
         svw.column_data_ptr[ 6 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b1000000010000000, result);
         svw.column_data_ptr[ 7 ] += 8;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 7  ] | { 1  }[ 6  ] | { 1  }[ 5  ] | { 1  }[ 4  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0000000000000010, result);
         svw.column_data_ptr[ 1 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b0000000000000100, result);
         svw.column_data_ptr[ 2 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b0000000000001000, result);
         svw.column_data_ptr[ 3 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b0000000000010000, result);
         svw.column_data_ptr[ 4 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b0000000000100000, result);
         svw.column_data_ptr[ 5 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b0000000001000000, result);
         svw.column_data_ptr[ 6 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b0000000010000000, result);
         svw.column_data_ptr[ 7 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0000000100000000, result);
         svw.column_data_ptr[ 8 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b0000001000000000, result);
         svw.column_data_ptr[ 9 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b0000010000000000, result);
         svw.column_data_ptr[ 10 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b0000100000000000, result);
         svw.column_data_ptr[ 11 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b0001000000000000, result);
         svw.column_data_ptr[ 12 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b0010000000000000, result);
         svw.column_data_ptr[ 13 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b0100000000000000, result);
         svw.column_data_ptr[ 14 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b1000000000000000, result);
         svw.column_data_ptr[ 15 ] += 8;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0010001000100010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b0100010001000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b1000100010001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0000000000100010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b0000000001000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b0000000010001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0001000100000000, result);
         svw.column_data_ptr[ 8 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b0010001000000000, result);
         svw.column_data_ptr[ 9 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b0100010000000000, result);
         svw.column_data_ptr[ 10 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b1000100000000000, result);
         svw.column_data_ptr[ 11 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 3  ] | { 3  }[ 2  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 3  ] | { 2  }[ 2  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0000000000000010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b0000000000000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b0000000000001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b0000000000010000, result);
         svw.column_data_ptr[ 4 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b0000000000100000, result);
         svw.column_data_ptr[ 5 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b0000000001000000, result);
         svw.column_data_ptr[ 6 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b0000000010000000, result);
         svw.column_data_ptr[ 7 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0000000100000000, result);
         svw.column_data_ptr[ 8 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b0000001000000000, result);
         svw.column_data_ptr[ 9 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b0000010000000000, result);
         svw.column_data_ptr[ 10 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b0000100000000000, result);
         svw.column_data_ptr[ 11 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b0001000000000000, result);
         svw.column_data_ptr[ 12 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b0010000000000000, result);
         svw.column_data_ptr[ 13 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b0100000000000000, result);
         svw.column_data_ptr[ 14 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b1000000000000000, result);
         svw.column_data_ptr[ 15 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b1010101010101010, result);
         svw.column_data_ptr[ 1 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ]|
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0000000010101010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0101010100000000, result);
         svw.column_data_ptr[ 8 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b1010101000000000, result);
         svw.column_data_ptr[ 9 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ]|
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0000000000001010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b0000000001010000, result);
         svw.column_data_ptr[ 4 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b0000000010100000, result);
         svw.column_data_ptr[ 5 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0000010100000000, result);
         svw.column_data_ptr[ 8 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b0000101000000000, result);
         svw.column_data_ptr[ 9 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b0101000000000000, result);
         svw.column_data_ptr[ 12 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b1010000000000000, result);
         svw.column_data_ptr[ 13 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 1  ] | { 7  }[ 0  ] | { 6  }[ 1  ] | { 6  }[ 0  ] | { 5  }[ 1  ] | { 5  }[ 0  ] | { 4  }[ 1  ] | { 4  }[ 0  ]|
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0000000000000010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b0000000000000100, result);
         svw.column_data_ptr[ 2 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b0000000000001000, result);
         svw.column_data_ptr[ 3 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b0000000000010000, result);
         svw.column_data_ptr[ 4 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b0000000000100000, result);
         svw.column_data_ptr[ 5 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b0000000001000000, result);
         svw.column_data_ptr[ 6 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b0000000010000000, result);
         svw.column_data_ptr[ 7 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0000000100000000, result);
         svw.column_data_ptr[ 8 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b0000001000000000, result);
         svw.column_data_ptr[ 9 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b0000010000000000, result);
         svw.column_data_ptr[ 10 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b0000100000000000, result);
         svw.column_data_ptr[ 11 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b0001000000000000, result);
         svw.column_data_ptr[ 12 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b0010000000000000, result);
         svw.column_data_ptr[ 13 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b0100000000000000, result);
         svw.column_data_ptr[ 14 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b1000000000000000, result);
         svw.column_data_ptr[ 15 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
      
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ]|
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b1111111100000000, result);
         svw.column_data_ptr[ 8 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ]|
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b0000000011110000, result);
         svw.column_data_ptr[ 4 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0000111100000000, result);
         svw.column_data_ptr[ 8 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b1111000000000000, result);
         svw.column_data_ptr[ 12 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 0  ] | { 7  }[ 0  ] | { 6  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 4  }[ 0  ]|
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b0000000000001100, result);
         svw.column_data_ptr[ 2 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b0000000000110000, result);
         svw.column_data_ptr[ 4 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b0000000011000000, result);
         svw.column_data_ptr[ 6 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0000001100000000, result);
         svw.column_data_ptr[ 8 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b0000110000000000, result);
         svw.column_data_ptr[ 10 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b0011000000000000, result);
         svw.column_data_ptr[ 12 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b1100000000000000, result);
         svw.column_data_ptr[ 14 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 16 ) && ( NoC == 16 ) && ( std::is_same< VecExt, avx2< uint16_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint16_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 15 }[ 0  ] | { 14 }[ 0  ] | { 13 }[ 0  ] | { 12 }[ 0  ] | { 11 }[ 0  ] | { 10 }[ 0  ] | { 9  }[ 0  ] | { 8  }[ 0  ]|
          * | { 7  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint16_t >::vector_t result = broadcast< avx2< uint16_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b0000000000000010, result);
         svw.column_data_ptr[ 1 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b0000000000000100, result);
         svw.column_data_ptr[ 2 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b0000000000001000, result);
         svw.column_data_ptr[ 3 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b0000000000010000, result);
         svw.column_data_ptr[ 4 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b0000000000100000, result);
         svw.column_data_ptr[ 5 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b0000000001000000, result);
         svw.column_data_ptr[ 6 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b0000000010000000, result);
         svw.column_data_ptr[ 7 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[8], 0b0000000100000000, result);
         svw.column_data_ptr[ 8 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[9], 0b0000001000000000, result);
         svw.column_data_ptr[ 9 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[10], 0b0000010000000000, result);
         svw.column_data_ptr[ 10 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[11], 0b0000100000000000, result);
         svw.column_data_ptr[ 11 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[12], 0b0001000000000000, result);
         svw.column_data_ptr[ 12 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[13], 0b0010000000000000, result);
         svw.column_data_ptr[ 13 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[14], 0b0100000000000000, result);
         svw.column_data_ptr[ 14 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[15], 0b1000000000000000, result);
         svw.column_data_ptr[ 15 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 7  ] | { 0  }[ 6  ] | { 0  }[ 5  ] | { 0  }[ 4  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000010, result);
         svw.column_data_ptr[ 1 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000100, result);
         svw.column_data_ptr[ 2 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00001000, result);
         svw.column_data_ptr[ 3 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00010000, result);
         svw.column_data_ptr[ 4 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00100000, result);
         svw.column_data_ptr[ 5 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b01000000, result);
         svw.column_data_ptr[ 6 ] += 8;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b10000000, result);
         svw.column_data_ptr[ 7 ] += 8;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00100010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b01000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b10001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 3  ] | { 1  }[ 2  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00010000, result);
         svw.column_data_ptr[ 4 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00100000, result);
         svw.column_data_ptr[ 5 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b01000000, result);
         svw.column_data_ptr[ 6 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b10000000, result);
         svw.column_data_ptr[ 7 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b10101010, result);
         svw.column_data_ptr[ 1 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00001010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b01010000, result);
         svw.column_data_ptr[ 4 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b10100000, result);
         svw.column_data_ptr[ 5 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 1  ] | { 3  }[ 0  ] | { 2  }[ 1  ] | { 2  }[ 0  ] | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000100, result);
         svw.column_data_ptr[ 2 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00001000, result);
         svw.column_data_ptr[ 3 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00010000, result);
         svw.column_data_ptr[ 4 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00100000, result);
         svw.column_data_ptr[ 5 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b01000000, result);
         svw.column_data_ptr[ 6 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b10000000, result);
         svw.column_data_ptr[ 7 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
      
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b11110000, result);
         svw.column_data_ptr[ 4 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00001100, result);
         svw.column_data_ptr[ 2 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00110000, result);
         svw.column_data_ptr[ 4 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b11000000, result);
         svw.column_data_ptr[ 6 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 8 ) && ( NoC == 8 ) && ( std::is_same< VecExt, avx2< uint32_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint32_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 7  }[ 0  ] | { 6  }[ 0  ] | { 5  }[ 0  ] | { 4  }[ 0  ] | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ]|
          * | 
          */
         typename avx2< uint32_t >::vector_t result = broadcast< avx2< uint32_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000010, result);
         svw.column_data_ptr[ 1 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000100, result);
         svw.column_data_ptr[ 2 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00001000, result);
         svw.column_data_ptr[ 3 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[4], 0b00010000, result);
         svw.column_data_ptr[ 4 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[5], 0b00100000, result);
         svw.column_data_ptr[ 5 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[6], 0b01000000, result);
         svw.column_data_ptr[ 6 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[7], 0b10000000, result);
         svw.column_data_ptr[ 7 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 1 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 3  ] | { 0  }[ 2  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | 
          */
         typename avx2< uint64_t >::vector_t result = broadcast< avx2< uint64_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000010, result);
         svw.column_data_ptr[ 1 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000100, result);
         svw.column_data_ptr[ 2 ] += 4;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00001000, result);
         svw.column_data_ptr[ 3 ] += 4;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 1  ] | { 0  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | 
          */
         typename avx2< uint64_t >::vector_t result = broadcast< avx2< uint64_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00001010, result);
         svw.column_data_ptr[ 1 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 2 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 1  ] | { 1  }[ 0  ] | { 0  }[ 1  ] | { 0  }[ 0  ] | 
          */
         typename avx2< uint64_t >::vector_t result = broadcast< avx2< uint64_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000010, result);
         svw.column_data_ptr[ 1 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000100, result);
         svw.column_data_ptr[ 2 ] += 2;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00001000, result);
         svw.column_data_ptr[ 3 ] += 2;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 1 ) && ( std::is_same< VecExt, avx2< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | 
          */
         typename avx2< uint64_t >::vector_t result = broadcast< avx2< uint64_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
      
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 2 ) && ( std::is_same< VecExt, avx2< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 1  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | { 0  }[ 0  ] | 
          */
         typename avx2< uint64_t >::vector_t result = broadcast< avx2< uint64_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00001100, result);
         svw.column_data_ptr[ 2 ] += 1;
         return result;
      }
              
      template< 
         std::size_t NoQ = NumberOfQueries, 
         std::size_t NoC = ColumnContainer::number_or_columns_t::value,
         class VecExt = VectorExtension,
         typename std::enable_if< ( ( NoQ == 4 ) && ( NoC == 4 ) && ( std::is_same< VecExt, avx2< uint64_t > >::value )), std::nullptr_t >::type = nullptr 
      >  
      FORCE_INLINE
      static
      typename avx2< uint64_t >::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {
         /* { col_id }[ col_offset ]
          * | { 3  }[ 0  ] | { 2  }[ 0  ] | { 1  }[ 0  ] | { 0  }[ 0  ] | 
          */
         typename avx2< uint64_t >::vector_t result = broadcast< avx2< uint64_t > >( *svw.column_data_ptr[ 0 ] );
         svw.column_data_ptr[ 0 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[1], 0b00000010, result);
         svw.column_data_ptr[ 1 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[2], 0b00000100, result);
         svw.column_data_ptr[ 2 ] += 1;
         result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[3], 0b00001000, result);
         svw.column_data_ptr[ 3 ] += 1;
         return result;
      }
              
   };
} 
#endif
        