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
   NO_DISCARD FORCE_INLINE
   uint64_t interleave_with_one_zero( T a ) {
#ifdef INTEL_SIMDI
      auto _a = _mm_set1_epi64x( a );
      return _mm_extract_epi64( _mm_clmulepi64_si128( _a, _a, 0 ), 0 );
#elif defined(ARM_SIMDI)
      auto _a = vmull_p64( a, a );
      return vreinterpretq_s64_p128(_a)[0];
#endif
   }
   
   template< typename T >
   NO_DISCARD FORCE_INLINE
   uint64_t interleave_with_three_zeroes( T a ) {
#ifdef INTEL_SIMDI
      auto _a = _mm_set1_epi64x( a );
      auto _b = _mm_clmulepi64_si128( _a, _a, 0 );
      return _mm_extract_epi64( _mm_clmulepi64_si128( _b, _b, 0 ), 0 );
#elif defined(ARM_SIMDI)
      uint64_t _a = vreinterpretq_s64_p128(vmull_p64( a, a ))[0];
      auto _b = vmull_p64( _a, _a );
      return vreinterpretq_s64_p128(_b)[0];
#endif
   }
   
   template< typename T >
   NO_DISCARD FORCE_INLINE
   uint64_t interleave_with_seven_zeroes( T a ) {
#ifdef INTEL_SIMDI
      auto _a = _mm_set1_epi64x( a );
      auto _b = _mm_clmulepi64_si128( _a, _a, 0 );
      auto _c = _mm_clmulepi64_si128( _b, _b, 0 );
      return _mm_extract_epi64( _mm_clmulepi64_si128( _c, _c, 0 ), 0 );
#elif defined(ARM_SIMDI)
      uint64_t _a = vreinterpretq_s64_p128(vmull_p64( a, a ) )[0];
      uint64_t _b = vreinterpretq_s64_p128(vmull_p64( _a, _a ) )[0];
      auto _c = vmull_p64( _b, _b );
      return vreinterpretq_s64_p128(_c)[0];
#endif
   }
   
   template< typename T >
   NO_DISCARD FORCE_INLINE
   uint64_t interleave_with_15_zeroes( T a ) {
#ifdef INTEL_SIMDI
      auto _a = _mm_set1_epi64x( a );
      auto _b = _mm_clmulepi64_si128( _a, _a, 0 );
      auto _c = _mm_clmulepi64_si128( _b, _b, 0 );
      auto _d = _mm_clmulepi64_si128( _c, _c, 0 );
      return _mm_extract_epi64( _mm_clmulepi64_si128( _d, _d, 0 ), 0 );
#elif defined(ARM_SIMDI)
      uint64_t _a = vreinterpretq_s64_p128(vmull_p64( a, a ) )[0];
      uint64_t _b = vreinterpretq_s64_p128(vmull_p64( _a, _a ) )[0];
      uint64_t _c = vreinterpretq_s64_p128(vmull_p64( _b, _b ) )[0];
      auto _d = vmull_p64( _c, _c );
      return vreinterpretq_s64_p128(_d)[0];
#endif
   }
   
   template< typename T >
   NO_DISCARD FORCE_INLINE
   uint64_t interleave_with_31_zeroes( T a ) {
      return ( a & 0b1 ) | ( ( a & 0b01 ) << 32 );
   }
   
   template< typename T >
   NO_DISCARD FORCE_INLINE
   uint64_t interleave_with_63_zeroes( T a ) {
      return ( a & 0b1 );
   }
   
   template< typename T, std::size_t NumberOfBits >
   constexpr T
   
   get_all_bits_set( ) {
      if constexpr( NumberOfBits == ( sizeof( T ) * 8 ) )
      {
         return std::numeric_limits< T >::max( );
      } else {
         return ( ( ( T )
         1 << NumberOfBits ) -1);
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
      
      using bits_of_interest_t = std::integral_constant< mask_t, get_all_bits_set < mask_t, NumberOfBits >( ) >;
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
            auto tmp3 = ( tmp0 >> ( offset_t::value + offset_t::value + offset_t::value ) );
            
            return std::make_tuple(
               (
                  interleave_with_three_zeroes( tmp0 & bits_of_interest_t::value ) |
                  ( interleave_with_three_zeroes( tmp1 & bits_of_interest_t::value ) << 1 ) |
                  ( interleave_with_three_zeroes( tmp2 & bits_of_interest_t::value ) << 2 ) |
                  ( interleave_with_three_zeroes( tmp3 & bits_of_interest_t::value ) << 3 )
               ),
               mask_ptr + 1
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
         auto m1 = ( *( mask_ptr + 1 ) ) >> BitPositionOffset;
         
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
      
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 8, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         auto m0 = ( *mask_ptr ) >> BitPositionOffset;
         auto m1 = ( *( mask_ptr + 1 ) ) >> BitPositionOffset;
         auto m2 = ( *( mask_ptr + 2 ) ) >> BitPositionOffset;
         auto m3 = ( *( mask_ptr + 3 ) ) >> BitPositionOffset;
         auto m4 = ( *( mask_ptr + 4 ) ) >> BitPositionOffset;
         auto m5 = ( *( mask_ptr + 5 ) ) >> BitPositionOffset;
         auto m6 = ( *( mask_ptr + 6 ) ) >> BitPositionOffset;
         auto m7 = ( *( mask_ptr + 7 ) ) >> BitPositionOffset;
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple(
               (
                  interleave_with_seven_zeroes( m0 ) |
                  ( interleave_with_seven_zeroes( m1 ) << 1 ) |
                  ( interleave_with_seven_zeroes( m2 ) << 2 ) |
                  ( interleave_with_seven_zeroes( m3 ) << 3 ) |
                  ( interleave_with_seven_zeroes( m4 ) << 4 ) |
                  ( interleave_with_seven_zeroes( m5 ) << 5 ) |
                  ( interleave_with_seven_zeroes( m6 ) << 6 ) |
                  ( interleave_with_seven_zeroes( m7 ) << 7 )
               ),
               mask_ptr + 8
            );
         }
      }
      
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 16, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         auto m0  = ( *mask_ptr ) >> BitPositionOffset;
         auto m1  = ( *( mask_ptr + 1 ) ) >> BitPositionOffset;
         auto m2  = ( *( mask_ptr + 2 ) ) >> BitPositionOffset;
         auto m3  = ( *( mask_ptr + 3 ) ) >> BitPositionOffset;
         auto m4  = ( *( mask_ptr + 4 ) ) >> BitPositionOffset;
         auto m5  = ( *( mask_ptr + 5 ) ) >> BitPositionOffset;
         auto m6  = ( *( mask_ptr + 6 ) ) >> BitPositionOffset;
         auto m7  = ( *( mask_ptr + 7 ) ) >> BitPositionOffset;
         auto m8  = ( *( mask_ptr + 8 ) ) >> BitPositionOffset;
         auto m9  = ( *( mask_ptr + 9 ) ) >> BitPositionOffset;
         auto m10 = ( *( mask_ptr + 10 ) ) >> BitPositionOffset;
         auto m11 = ( *( mask_ptr + 11 ) ) >> BitPositionOffset;
         auto m12 = ( *( mask_ptr + 12 ) ) >> BitPositionOffset;
         auto m13 = ( *( mask_ptr + 13 ) ) >> BitPositionOffset;
         auto m14 = ( *( mask_ptr + 14 ) ) >> BitPositionOffset;
         auto m15 = ( *( mask_ptr + 15 ) ) >> BitPositionOffset;
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple(
               (
                  interleave_with_15_zeroes( m0 ) |
                  ( interleave_with_15_zeroes( m1 ) << 1 ) |
                  ( interleave_with_15_zeroes( m2 ) << 2 ) |
                  ( interleave_with_15_zeroes( m3 ) << 3 ) |
                  ( interleave_with_15_zeroes( m4 ) << 4 ) |
                  ( interleave_with_15_zeroes( m5 ) << 5 ) |
                  ( interleave_with_15_zeroes( m6 ) << 6 ) |
                  ( interleave_with_15_zeroes( m7 ) << 7 ) |
                  ( interleave_with_15_zeroes( m8 ) << 8 ) |
                  ( interleave_with_15_zeroes( m9 ) << 9 ) |
                  ( interleave_with_15_zeroes( m10 ) << 10 ) |
                  ( interleave_with_15_zeroes( m11 ) << 11 ) |
                  ( interleave_with_15_zeroes( m12 ) << 12 ) |
                  ( interleave_with_15_zeroes( m13 ) << 13 ) |
                  ( interleave_with_15_zeroes( m14 ) << 14 ) |
                  ( interleave_with_15_zeroes( m15 ) << 15 )
               
               ),
               mask_ptr + 16
            );
         }
      }
      
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 32, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         auto m0  = ( *mask_ptr ) >> BitPositionOffset;
         auto m1  = ( *( mask_ptr + 1 ) ) >> BitPositionOffset;
         auto m2  = ( *( mask_ptr + 2 ) ) >> BitPositionOffset;
         auto m3  = ( *( mask_ptr + 3 ) ) >> BitPositionOffset;
         auto m4  = ( *( mask_ptr + 4 ) ) >> BitPositionOffset;
         auto m5  = ( *( mask_ptr + 5 ) ) >> BitPositionOffset;
         auto m6  = ( *( mask_ptr + 6 ) ) >> BitPositionOffset;
         auto m7  = ( *( mask_ptr + 7 ) ) >> BitPositionOffset;
         auto m8  = ( *( mask_ptr + 8 ) ) >> BitPositionOffset;
         auto m9  = ( *( mask_ptr + 9 ) ) >> BitPositionOffset;
         auto m10 = ( *( mask_ptr + 10 ) ) >> BitPositionOffset;
         auto m11 = ( *( mask_ptr + 11 ) ) >> BitPositionOffset;
         auto m12 = ( *( mask_ptr + 12 ) ) >> BitPositionOffset;
         auto m13 = ( *( mask_ptr + 13 ) ) >> BitPositionOffset;
         auto m14 = ( *( mask_ptr + 14 ) ) >> BitPositionOffset;
         auto m15 = ( *( mask_ptr + 15 ) ) >> BitPositionOffset;
         auto m16 = ( *( mask_ptr + 16 ) ) >> BitPositionOffset;
         auto m17 = ( *( mask_ptr + 17 ) ) >> BitPositionOffset;
         auto m18 = ( *( mask_ptr + 18 ) ) >> BitPositionOffset;
         auto m19 = ( *( mask_ptr + 19 ) ) >> BitPositionOffset;
         auto m20 = ( *( mask_ptr + 20 ) ) >> BitPositionOffset;
         auto m21 = ( *( mask_ptr + 21 ) ) >> BitPositionOffset;
         auto m22 = ( *( mask_ptr + 22 ) ) >> BitPositionOffset;
         auto m23 = ( *( mask_ptr + 23 ) ) >> BitPositionOffset;
         auto m24 = ( *( mask_ptr + 24 ) ) >> BitPositionOffset;
         auto m25 = ( *( mask_ptr + 25 ) ) >> BitPositionOffset;
         auto m26 = ( *( mask_ptr + 26 ) ) >> BitPositionOffset;
         auto m27 = ( *( mask_ptr + 27 ) ) >> BitPositionOffset;
         auto m28 = ( *( mask_ptr + 28 ) ) >> BitPositionOffset;
         auto m29 = ( *( mask_ptr + 29 ) ) >> BitPositionOffset;
         auto m30 = ( *( mask_ptr + 30 ) ) >> BitPositionOffset;
         auto m31 = ( *( mask_ptr + 31 ) ) >> BitPositionOffset;
         
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple(
               (
                  interleave_with_31_zeroes( m0 ) |
                  ( interleave_with_31_zeroes( m1 ) << 1 ) |
                  ( interleave_with_31_zeroes( m2 ) << 2 ) |
                  ( interleave_with_31_zeroes( m3 ) << 3 ) |
                  ( interleave_with_31_zeroes( m4 ) << 4 ) |
                  ( interleave_with_31_zeroes( m5 ) << 5 ) |
                  ( interleave_with_31_zeroes( m6 ) << 6 ) |
                  ( interleave_with_31_zeroes( m7 ) << 7 ) |
                  ( interleave_with_31_zeroes( m8 ) << 8 ) |
                  ( interleave_with_31_zeroes( m9 ) << 9 ) |
                  ( interleave_with_31_zeroes( m10 ) << 10 ) |
                  ( interleave_with_31_zeroes( m11 ) << 11 ) |
                  ( interleave_with_31_zeroes( m12 ) << 12 ) |
                  ( interleave_with_31_zeroes( m13 ) << 13 ) |
                  ( interleave_with_31_zeroes( m14 ) << 14 ) |
                  ( interleave_with_31_zeroes( m15 ) << 15 ) |
                  ( interleave_with_31_zeroes( m16 ) << 16 ) |
                  ( interleave_with_31_zeroes( m17 ) << 17 ) |
                  ( interleave_with_31_zeroes( m18 ) << 18 ) |
                  ( interleave_with_31_zeroes( m19 ) << 19 ) |
                  ( interleave_with_31_zeroes( m20 ) << 20 ) |
                  ( interleave_with_31_zeroes( m21 ) << 21 ) |
                  ( interleave_with_31_zeroes( m22 ) << 22 ) |
                  ( interleave_with_31_zeroes( m23 ) << 23 ) |
                  ( interleave_with_31_zeroes( m24 ) << 24 ) |
                  ( interleave_with_31_zeroes( m25 ) << 25 ) |
                  ( interleave_with_31_zeroes( m26 ) << 26 ) |
                  ( interleave_with_31_zeroes( m27 ) << 27 ) |
                  ( interleave_with_31_zeroes( m28 ) << 28 ) |
                  ( interleave_with_31_zeroes( m29 ) << 29 ) |
                  ( interleave_with_31_zeroes( m20 ) << 30 ) |
                  ( interleave_with_31_zeroes( m31 ) << 31 )
               ),
               mask_ptr + 32
            );
         }
      }
      
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 64, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         auto m0  = ( *mask_ptr ) >> BitPositionOffset;
         auto m1  = ( *( mask_ptr + 1 ) ) >> BitPositionOffset;
         auto m2  = ( *( mask_ptr + 2 ) ) >> BitPositionOffset;
         auto m3  = ( *( mask_ptr + 3 ) ) >> BitPositionOffset;
         auto m4  = ( *( mask_ptr + 4 ) ) >> BitPositionOffset;
         auto m5  = ( *( mask_ptr + 5 ) ) >> BitPositionOffset;
         auto m6  = ( *( mask_ptr + 6 ) ) >> BitPositionOffset;
         auto m7  = ( *( mask_ptr + 7 ) ) >> BitPositionOffset;
         auto m8  = ( *( mask_ptr + 8 ) ) >> BitPositionOffset;
         auto m9  = ( *( mask_ptr + 9 ) ) >> BitPositionOffset;
         auto m10 = ( *( mask_ptr + 10 ) ) >> BitPositionOffset;
         auto m11 = ( *( mask_ptr + 11 ) ) >> BitPositionOffset;
         auto m12 = ( *( mask_ptr + 12 ) ) >> BitPositionOffset;
         auto m13 = ( *( mask_ptr + 13 ) ) >> BitPositionOffset;
         auto m14 = ( *( mask_ptr + 14 ) ) >> BitPositionOffset;
         auto m15 = ( *( mask_ptr + 15 ) ) >> BitPositionOffset;
         auto m16 = ( *( mask_ptr + 16 ) ) >> BitPositionOffset;
         auto m17 = ( *( mask_ptr + 17 ) ) >> BitPositionOffset;
         auto m18 = ( *( mask_ptr + 18 ) ) >> BitPositionOffset;
         auto m19 = ( *( mask_ptr + 19 ) ) >> BitPositionOffset;
         auto m20 = ( *( mask_ptr + 20 ) ) >> BitPositionOffset;
         auto m21 = ( *( mask_ptr + 21 ) ) >> BitPositionOffset;
         auto m22 = ( *( mask_ptr + 22 ) ) >> BitPositionOffset;
         auto m23 = ( *( mask_ptr + 23 ) ) >> BitPositionOffset;
         auto m24 = ( *( mask_ptr + 24 ) ) >> BitPositionOffset;
         auto m25 = ( *( mask_ptr + 25 ) ) >> BitPositionOffset;
         auto m26 = ( *( mask_ptr + 26 ) ) >> BitPositionOffset;
         auto m27 = ( *( mask_ptr + 27 ) ) >> BitPositionOffset;
         auto m28 = ( *( mask_ptr + 28 ) ) >> BitPositionOffset;
         auto m29 = ( *( mask_ptr + 29 ) ) >> BitPositionOffset;
         auto m30 = ( *( mask_ptr + 30 ) ) >> BitPositionOffset;
         auto m31 = ( *( mask_ptr + 31 ) ) >> BitPositionOffset;
         auto m32 = ( *( mask_ptr + 32 ) ) >> BitPositionOffset;
         auto m33 = ( *( mask_ptr + 33 ) ) >> BitPositionOffset;
         auto m34 = ( *( mask_ptr + 34 ) ) >> BitPositionOffset;
         auto m35 = ( *( mask_ptr + 35 ) ) >> BitPositionOffset;
         auto m36 = ( *( mask_ptr + 36 ) ) >> BitPositionOffset;
         auto m37 = ( *( mask_ptr + 37 ) ) >> BitPositionOffset;
         auto m38 = ( *( mask_ptr + 38 ) ) >> BitPositionOffset;
         auto m39 = ( *( mask_ptr + 39 ) ) >> BitPositionOffset;
         auto m40 = ( *( mask_ptr + 40 ) ) >> BitPositionOffset;
         auto m41 = ( *( mask_ptr + 41 ) ) >> BitPositionOffset;
         auto m42 = ( *( mask_ptr + 42 ) ) >> BitPositionOffset;
         auto m43 = ( *( mask_ptr + 43 ) ) >> BitPositionOffset;
         auto m44 = ( *( mask_ptr + 44 ) ) >> BitPositionOffset;
         auto m45 = ( *( mask_ptr + 45 ) ) >> BitPositionOffset;
         auto m46 = ( *( mask_ptr + 46 ) ) >> BitPositionOffset;
         auto m47 = ( *( mask_ptr + 47 ) ) >> BitPositionOffset;
         auto m48 = ( *( mask_ptr + 48 ) ) >> BitPositionOffset;
         auto m49 = ( *( mask_ptr + 49 ) ) >> BitPositionOffset;
         auto m50 = ( *( mask_ptr + 50 ) ) >> BitPositionOffset;
         auto m51 = ( *( mask_ptr + 51 ) ) >> BitPositionOffset;
         auto m52 = ( *( mask_ptr + 52 ) ) >> BitPositionOffset;
         auto m53 = ( *( mask_ptr + 53 ) ) >> BitPositionOffset;
         auto m54 = ( *( mask_ptr + 54 ) ) >> BitPositionOffset;
         auto m55 = ( *( mask_ptr + 55 ) ) >> BitPositionOffset;
         auto m56 = ( *( mask_ptr + 56 ) ) >> BitPositionOffset;
         auto m57 = ( *( mask_ptr + 57 ) ) >> BitPositionOffset;
         auto m58 = ( *( mask_ptr + 58 ) ) >> BitPositionOffset;
         auto m59 = ( *( mask_ptr + 59 ) ) >> BitPositionOffset;
         auto m60 = ( *( mask_ptr + 60 ) ) >> BitPositionOffset;
         auto m61 = ( *( mask_ptr + 61 ) ) >> BitPositionOffset;
         auto m62 = ( *( mask_ptr + 62 ) ) >> BitPositionOffset;
         auto m63 = ( *( mask_ptr + 63 ) ) >> BitPositionOffset;
         
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple(
               (
                  interleave_with_63_zeroes( m0 ) |
                  ( interleave_with_63_zeroes( m1 ) << 1 ) |
                  ( interleave_with_63_zeroes( m2 ) << 2 ) |
                  ( interleave_with_63_zeroes( m3 ) << 3 ) |
                  ( interleave_with_63_zeroes( m4 ) << 4 ) |
                  ( interleave_with_63_zeroes( m5 ) << 5 ) |
                  ( interleave_with_63_zeroes( m6 ) << 6 ) |
                  ( interleave_with_63_zeroes( m7 ) << 7 ) |
                  ( interleave_with_63_zeroes( m8 ) << 8 ) |
                  ( interleave_with_63_zeroes( m9 ) << 9 ) |
                  ( interleave_with_63_zeroes( m10 ) << 10 ) |
                  ( interleave_with_63_zeroes( m11 ) << 11 ) |
                  ( interleave_with_63_zeroes( m12 ) << 12 ) |
                  ( interleave_with_63_zeroes( m13 ) << 13 ) |
                  ( interleave_with_63_zeroes( m14 ) << 14 ) |
                  ( interleave_with_63_zeroes( m15 ) << 15 ) |
                  ( interleave_with_63_zeroes( m16 ) << 16 ) |
                  ( interleave_with_63_zeroes( m17 ) << 17 ) |
                  ( interleave_with_63_zeroes( m18 ) << 18 ) |
                  ( interleave_with_63_zeroes( m19 ) << 19 ) |
                  ( interleave_with_63_zeroes( m20 ) << 20 ) |
                  ( interleave_with_63_zeroes( m21 ) << 21 ) |
                  ( interleave_with_63_zeroes( m22 ) << 22 ) |
                  ( interleave_with_63_zeroes( m23 ) << 23 ) |
                  ( interleave_with_63_zeroes( m24 ) << 24 ) |
                  ( interleave_with_63_zeroes( m25 ) << 25 ) |
                  ( interleave_with_63_zeroes( m26 ) << 26 ) |
                  ( interleave_with_63_zeroes( m27 ) << 27 ) |
                  ( interleave_with_63_zeroes( m28 ) << 28 ) |
                  ( interleave_with_63_zeroes( m29 ) << 29 ) |
                  ( interleave_with_63_zeroes( m30 ) << 30 ) |
                  ( interleave_with_63_zeroes( m31 ) << 31 ) |
                  ( interleave_with_63_zeroes( m32 ) << 32 ) |
                  ( interleave_with_63_zeroes( m33 ) << 33 ) |
                  ( interleave_with_63_zeroes( m34 ) << 34 ) |
                  ( interleave_with_63_zeroes( m35 ) << 35 ) |
                  ( interleave_with_63_zeroes( m36 ) << 36 ) |
                  ( interleave_with_63_zeroes( m37 ) << 37 ) |
                  ( interleave_with_63_zeroes( m38 ) << 38 ) |
                  ( interleave_with_63_zeroes( m39 ) << 39 ) |
                  ( interleave_with_63_zeroes( m40 ) << 40 ) |
                  ( interleave_with_63_zeroes( m41 ) << 41 ) |
                  ( interleave_with_63_zeroes( m42 ) << 42 ) |
                  ( interleave_with_63_zeroes( m43 ) << 43 ) |
                  ( interleave_with_63_zeroes( m44 ) << 44 ) |
                  ( interleave_with_63_zeroes( m45 ) << 45 ) |
                  ( interleave_with_63_zeroes( m46 ) << 46 ) |
                  ( interleave_with_63_zeroes( m47 ) << 47 ) |
                  ( interleave_with_63_zeroes( m48 ) << 48 ) |
                  ( interleave_with_63_zeroes( m49 ) << 49 ) |
                  ( interleave_with_63_zeroes( m50 ) << 50 ) |
                  ( interleave_with_63_zeroes( m51 ) << 51 ) |
                  ( interleave_with_63_zeroes( m52 ) << 52 ) |
                  ( interleave_with_63_zeroes( m53 ) << 53 ) |
                  ( interleave_with_63_zeroes( m54 ) << 54 ) |
                  ( interleave_with_63_zeroes( m55 ) << 55 ) |
                  ( interleave_with_63_zeroes( m56 ) << 56 ) |
                  ( interleave_with_63_zeroes( m57 ) << 57 ) |
                  ( interleave_with_63_zeroes( m58 ) << 58 ) |
                  ( interleave_with_63_zeroes( m59 ) << 59 ) |
                  ( interleave_with_63_zeroes( m60 ) << 60 ) |
                  ( interleave_with_63_zeroes( m61 ) << 61 ) |
                  ( interleave_with_63_zeroes( m62 ) << 62 ) |
                  ( interleave_with_63_zeroes( m63 ) << 63 )
               ),
               mask_ptr + 64
            );
         }
      }
      
   };
}
#endif //TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_BITMASK_COMPLEX_BITMASK_H
