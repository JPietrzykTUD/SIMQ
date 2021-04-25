/*
 * This file is part of the SIMQ Project (https://github.com/JPietrzykTUD/SIMQ).
 * Copyright (c) 2021 Johannes Pietrzyk.
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

#ifndef TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_BITMASK_COMPLEX_BITMASK_H
#define TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_BITMASK_COMPLEX_BITMASK_H


#include <cstdint>
#include <cstddef>



#include <cstddef>
#include <type_traits>
#include <limits>

#include <utils/preprocessor.h>
#include <simd/intrin.h>



namespace tuddbs {
   
   template< typename T >
   uint64_t interleave_with_one_zero( T a ) {
      auto _a = _mm_set1_epi64x( a );
      return _mm_extract_epi64( _mm_clmulepi64_si128( _a, _a, 0 ), 0 );
   }
   
   template< typename T >
   uint64_t interleave_with_three_zeroes( T a ) {
      auto _a = _mm_set1_epi64x( a );
      auto _b = _mm_clmulepi64_si128( _a, _a, 0 );
      return _mm_extract_epi64( _mm_clmulepi64_si128( _b, _b, 0 ), 0 );
   }
   
   template< typename T >
   uint64_t interleave_with_seven_zeroes( T a ) {
      auto _a = _mm_set1_epi64x( a );
      auto _b = _mm_clmulepi64_si128( _a, _a, 0 );
      auto _c = _mm_clmulepi64_si128( _b, _b, 0 );
      return _mm_extract_epi64( _mm_clmulepi64_si128( _c, _c, 0 ), 0 );
   }
   
   
   template< typename T, std::size_t NumberOfBits >
   constexpr T get_all_bits_set( ) {
      if constexpr( NumberOfBits == ( sizeof( T ) * 8 ) ) {
         return std::numeric_limits< T >::max();
      } else {
         return (( (T)1 << NumberOfBits ) - 1);
      }
   }
   
   /**
    * @brief Helper class for complex masks (where not all bits are relevant for the caller).
    * We assume, that relevant bits are clustered (not interrupted by irrelevant bits)
    * @tparam VectorExtension
    * @tparam NumberOfParticipants Allowed Values so far: 1, 2, 3 (Because we only have 3 successor-operators)
    * @tparam NumberOfBits
    */
   template<
      class VectorExtension,
      std::size_t NumberOfBits = 0,
      std::size_t BitPositionOffset = 0
   >
   struct complex_bitmask_helper_t {
   
      using mask_t = typename VectorExtension::mask_t;
      using bits_per_mask_t = std::integral_constant< std::size_t, sizeof( mask_t ) << 3 >;
      using vecs_per_mask_t = typename vector_constants_t< VectorExtension >::number_of_vectors_per_mask_t;
      using number_of_bits_per_mask =
      std::integral_constant<
         std::size_t, NumberOfBits * vecs_per_mask_t::value
      >;
   
      using incrementor_t =
      std::integral_constant<
         std::size_t, bits_per_mask_t::value / number_of_bits_per_mask::value
      >;

      using bits_of_interest_t = std::integral_constant< mask_t, get_all_bits_set< mask_t, NumberOfBits >() >;
      using offset_t = std::integral_constant< std::size_t, bits_per_mask_t::value / vecs_per_mask_t::value >;
      using has_to_be_applied_t = std::integral_constant< bool, NumberOfBits != 0 >;
   
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 1, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
      std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple(
               (
                  ( *mask_ptr ) & bits_of_interest_t::value
               ),
               mask_ptr + 1
            );
         } else if constexpr( vecs_per_mask_t::value == 2 )
         {
            auto tmp0 = ( *mask_ptr ) >> BitPositionOffset;
            auto tmp1 = ( tmp0 >> offset_t::value );
            
            return std::make_tuple(
               (
                  interleave_with_one_zero( tmp0 & bits_of_interest_t::value ) |
                  ( interleave_with_one_zero( tmp1 & bits_of_interest_t::value ) << 1 )
               ),
               mask_ptr + 1
            );
            
         } else if constexpr( vecs_per_mask_t::value == 4 )
         {
            auto tmp0 = ( *mask_ptr ) >> BitPositionOffset;
            auto tmp1 = ( tmp0 >> offset_t::value );
            auto tmp2 = ( tmp0 >> ( offset_t::value + offset_t::value ) );
            auto tmp3 = ( tmp0 >> ( offset_t::value + offset_t::value + offset_t::value) );
            
            return std::make_tuple(
               (
                  interleave_with_three_zeroes( tmp0 & bits_of_interest_t::value ) |
                  ( interleave_with_three_zeroes( tmp1 & bits_of_interest_t::value ) << 1 ) |
                  ( interleave_with_three_zeroes( tmp2 & bits_of_interest_t::value ) << 2 ) |
                  ( interleave_with_three_zeroes( tmp3 & bits_of_interest_t::value ) << 3 )
               ),
               mask_ptr +1
            );
         }
      }
   
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 2, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
      std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         auto m0 = ( *mask_ptr ) >> BitPositionOffset;
         auto m1 = ( *( mask_ptr +1 ) ) >> BitPositionOffset;
         
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple(
               (
                  interleave_with_one_zero( m0 & bits_of_interest_t::value ) |
                  ( interleave_with_one_zero( m1 & bits_of_interest_t::value ) << 1 )
               ),
               mask_ptr + 2
            );
         } else if constexpr( vecs_per_mask_t::value == 2 )
         {
            auto tmp0 = m0 & bits_of_interest_t::value;
            auto tmp1 = ( m0 >> offset_t::value ) & bits_of_interest_t::value;
            auto tmp2 = m1 & bits_of_interest_t::value;
            auto tmp3 = ( m1 >> offset_t::value ) & bits_of_interest_t::value;
            
            return std::make_tuple(
               (
                  interleave_with_three_zeroes( tmp0 ) |
                  ( interleave_with_three_zeroes( tmp1 ) << 1 ) |
                  ( interleave_with_three_zeroes( tmp2 ) << 2 ) |
                  ( interleave_with_three_zeroes( tmp3 ) << 3 )
               ),
               mask_ptr + 2
            );
            
         } else if constexpr( vecs_per_mask_t::value == 4 )
         {
            auto tmp0 = m0 & bits_of_interest_t::value;
            auto tmp1 = ( m0 >> offset_t::value ) & bits_of_interest_t::value;
            auto tmp2 = ( m0 >> ( offset_t::value + offset_t::value ) ) & bits_of_interest_t::value;
            auto tmp3 = ( m0 >> ( offset_t::value + offset_t::value + offset_t::value ) ) & bits_of_interest_t::value;
            auto tmp4 = m1 & bits_of_interest_t::value;
            auto tmp5 = ( m1 >> offset_t::value ) & bits_of_interest_t::value;
            auto tmp6 = ( m1 >> ( offset_t::value + offset_t::value ) ) & bits_of_interest_t::value;
            auto tmp7 = ( m1 >> ( offset_t::value + offset_t::value + offset_t::value ) ) & bits_of_interest_t::value;
            return std::make_tuple(
               (
                  interleave_with_seven_zeroes( tmp0 ) |
                  ( interleave_with_seven_zeroes( tmp1 ) << 1 ) |
                  ( interleave_with_seven_zeroes( tmp2 ) << 2 ) |
                  ( interleave_with_seven_zeroes( tmp3 ) << 3 ) |
                  ( interleave_with_seven_zeroes( tmp4 ) << 4 ) |
                  ( interleave_with_seven_zeroes( tmp5 ) << 5 ) |
                  ( interleave_with_seven_zeroes( tmp6 ) << 6 ) |
                  ( interleave_with_seven_zeroes( tmp7 ) << 7 )
               ),
               mask_ptr + 2
            );
         }
      }
   
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 4, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
      std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         auto m0 = ( *mask_ptr ) >> BitPositionOffset;
         auto m1 = ( *( mask_ptr + 1 ) ) >> BitPositionOffset;
         auto m2 = ( *( mask_ptr + 2 ) ) >> BitPositionOffset;
         auto m3 = ( *( mask_ptr + 3 ) ) >> BitPositionOffset;
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple(
               (
                  interleave_with_three_zeroes( m0 & bits_of_interest_t::value ) |
                  ( interleave_with_three_zeroes( m1 & bits_of_interest_t::value ) << 1 ) |
                  ( interleave_with_three_zeroes( m2 & bits_of_interest_t::value ) << 2 ) |
                  ( interleave_with_three_zeroes( m3 & bits_of_interest_t::value ) << 3 )
               ),
               mask_ptr + 4
            );
         } else if constexpr( vecs_per_mask_t::value == 2 )
         {
            auto tmp0 = m0 & bits_of_interest_t::value;
            auto tmp1 = ( m0 >> offset_t::value ) & bits_of_interest_t::value;
            auto tmp2 = m1 & bits_of_interest_t::value;
            auto tmp3 = ( m1 >> offset_t::value ) & bits_of_interest_t::value;
            auto tmp4 = m2 & bits_of_interest_t::value;
            auto tmp5 = ( m2 >> offset_t::value ) & bits_of_interest_t::value;
            auto tmp6 = m3 & bits_of_interest_t::value;
            auto tmp7 = ( m3 >> offset_t::value ) & bits_of_interest_t::value;
   
            return std::make_tuple(
               (
                  interleave_with_seven_zeroes( tmp0 ) |
                  ( interleave_with_seven_zeroes( tmp1 ) << 1 ) |
                  ( interleave_with_seven_zeroes( tmp2 ) << 2 ) |
                  ( interleave_with_seven_zeroes( tmp3 ) << 3 ) |
                  ( interleave_with_seven_zeroes( tmp4 ) << 4 ) |
                  ( interleave_with_seven_zeroes( tmp5 ) << 5 ) |
                  ( interleave_with_seven_zeroes( tmp6 ) << 6 ) |
                  ( interleave_with_seven_zeroes( tmp7 ) << 7 )
               ),
               mask_ptr + 4
            );
         }
      }
      
   
   
   };
}
#endif //TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_BITMASK_COMPLEX_BITMASK_H
