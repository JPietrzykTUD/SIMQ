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
      using bits_of_interest_t =
         std::conditional_t<
            NumberOfBits == ( sizeof( mask_t ) * 8 ),      std::integral_constant< mask_t, std::numeric_limits< mask_t >::max( ) >,
            std::integral_constant< mask_t, ( 1 << NumberOfBits ) - 1 >
         >;
      
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
            using offset_t = std::integral_constant< std::size_t, bits_per_mask_t::value / vecs_per_mask_t::value >;
            return std::make_tuple(
               (
                  ( ( ( ( tmp0 ) ) & bits_of_interest_t::value ) ) |
                  ( ( ( ( tmp0 ) >> ( offset_t::value ) ) & bits_of_interest_t::value ) << ( NumberOfBits ) )
               ),
               mask_ptr + 1
            );
         } else if constexpr( vecs_per_mask_t::value == 4 )
         {
            auto tmp0 = ( *mask_ptr ) >> BitPositionOffset;
            using offset_t = std::integral_constant< std::size_t, bits_per_mask_t::value / vecs_per_mask_t::value >;
            return std::make_tuple(
               (
                  ( ( ( ( tmp0 ) ) & bits_of_interest_t::value ) ) |
                  ( ( ( ( tmp0 ) >> ( offset_t::value ) ) & bits_of_interest_t::value ) << ( NumberOfBits ) ) |
                  ( ( ( ( tmp0 ) >> ( offset_t::value + offset_t::value ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp0 ) >> ( offset_t::value + offset_t::value + offset_t::value ) ) &
                      bits_of_interest_t::value ) << ( NumberOfBits + NumberOfBits + NumberOfBits ) )
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
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple(
               (
                  ( ( ( *mask_ptr ) >> BitPositionOffset ) & bits_of_interest_t::value ) |
                  ( ( ( ( *( mask_ptr + 1 ) ) >> BitPositionOffset ) & bits_of_interest_t::value ) << ( NumberOfBits ) )
               ),
               mask_ptr + 2
            );
         } else if constexpr( vecs_per_mask_t::value == 2 )
         {
            auto tmp0 = ( *mask_ptr ) >> BitPositionOffset;
            auto tmp1 = ( *( mask_ptr + 1 ) ) >> BitPositionOffset;
            using offset_t = std::integral_constant< std::size_t, bits_per_mask_t::value / vecs_per_mask_t::value >;
            return std::make_tuple(
               (
                  ( ( ( ( tmp0 ) ) & bits_of_interest_t::value ) ) |
                  ( ( ( ( tmp0 ) >> ( offset_t::value ) ) & bits_of_interest_t::value ) << ( NumberOfBits ) ) |
                  ( ( ( ( tmp1 ) ) & bits_of_interest_t::value ) << ( NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp1 ) >> ( offset_t::value ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits ) )
               ),
               mask_ptr + 2
            );
         } else if constexpr( vecs_per_mask_t::value == 4 )
         {
            auto tmp0 = ( *mask_ptr ) >> BitPositionOffset;
            auto tmp1 = ( *( mask_ptr + 1 ) ) >> BitPositionOffset;
            using offset_t = std::integral_constant< std::size_t, bits_per_mask_t::value / vecs_per_mask_t::value >;
            return std::make_tuple(
               (
                  ( ( ( ( tmp0 ) ) & bits_of_interest_t::value ) ) |
                  ( ( ( ( tmp0 ) >> ( offset_t::value ) ) & bits_of_interest_t::value ) << ( NumberOfBits ) ) |
                  ( ( ( ( tmp0 ) >> ( offset_t::value + offset_t::value ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp0 ) >> ( offset_t::value + offset_t::value + offset_t::value ) ) &
                      bits_of_interest_t::value ) << ( NumberOfBits + NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp1 ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp1 ) >> ( offset_t::value ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp1 ) >> ( offset_t::value + offset_t::value ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp1 ) >> ( offset_t::value + offset_t::value + offset_t::value ) ) &
                      bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                          NumberOfBits ) )
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
         std::cerr << "Old Bitmask : " << std::bitset< 64 >( *mask_ptr ) << "\n";
         std::cerr << "Old Bitmask : " << std::bitset< 64 >( *(mask_ptr+1) ) << "\n";
         std::cerr << "Old Bitmask : " << std::bitset< 64 >( *(mask_ptr+2) ) << "\n";
         std::cerr << "Old Bitmask : " << std::bitset< 64 >( *(mask_ptr+3) ) << "\n";
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple(
               (
                  ( ( ( *mask_ptr ) >> BitPositionOffset ) & bits_of_interest_t::value ) |
                  ( ( ( ( *( mask_ptr + 1 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                     << ( NumberOfBits ) ) |
                  ( ( ( ( *( mask_ptr + 2 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( *( mask_ptr + 3 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits ) )
               ),
               mask_ptr + 4
            );
         } else if constexpr( vecs_per_mask_t::value == 2 )
         {
            auto tmp0 = ( *mask_ptr ) >> BitPositionOffset;
            auto tmp1 = ( *( mask_ptr + 1 ) ) >> BitPositionOffset;
            auto tmp2 = ( *( mask_ptr + 2 ) ) >> BitPositionOffset;
            auto tmp3 = ( *( mask_ptr + 3 ) ) >> BitPositionOffset;
            using offset_t = std::integral_constant< std::size_t, bits_per_mask_t::value / vecs_per_mask_t::value >;
            return std::make_tuple(
               (
                  ( ( ( ( tmp0 ) ) & bits_of_interest_t::value ) ) |
                  ( ( ( ( tmp0 ) >> ( offset_t::value ) ) & bits_of_interest_t::value ) << ( NumberOfBits ) ) |
                  ( ( ( ( tmp1 ) ) & bits_of_interest_t::value ) << ( NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp1 ) >> ( offset_t::value ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp2 ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp2 ) >> ( offset_t::value ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp3 ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
                  ( ( ( ( tmp3 ) >> ( offset_t::value ) ) & bits_of_interest_t::value )
                     << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                          NumberOfBits ) )
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
         return std::make_tuple(
            (
               ( ( ( *mask_ptr ) >> BitPositionOffset ) & bits_of_interest_t::value ) |
               ( ( ( ( *( mask_ptr + 1 ) ) >> BitPositionOffset ) & bits_of_interest_t::value ) << ( NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 2 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 3 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 4 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 5 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 6 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 7 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) )
            ),
            mask_ptr + 8
         );
      }
   
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 16, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         return std::make_tuple(
            (
               ( ( ( *mask_ptr ) >> BitPositionOffset ) & bits_of_interest_t::value ) |
               ( ( ( ( *( mask_ptr + 1 ) ) >> BitPositionOffset ) & bits_of_interest_t::value ) << ( NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 2 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 3 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 4 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 5 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 6 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 7 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 8 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 9 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 10 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 11 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 12 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 13 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 14 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 15 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) )
            ),
            mask_ptr + 16
         );
      }
   
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 32, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         return std::make_tuple(
            (
               ( ( ( *mask_ptr ) >> BitPositionOffset ) & bits_of_interest_t::value ) |
               ( ( ( ( *( mask_ptr + 1 ) ) >> BitPositionOffset ) & bits_of_interest_t::value ) << ( NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 2 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 3 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 4 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 5 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 6 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 7 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 8 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 9 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 10 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 11 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 12 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 13 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 14 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 15 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 16 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 17 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 18 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 19 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 20 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 21 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 22 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 23 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 24 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 25 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 26 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 27 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 28 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 29 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 30 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 31 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) )
            ),
            mask_ptr + 32
         );
      }
   
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 64, std::nullptr_t > = nullptr
      >
      FORCE_INLINE static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         return std::make_tuple(
            (
               ( ( ( *mask_ptr ) >> BitPositionOffset ) & bits_of_interest_t::value ) |
               ( ( ( ( *( mask_ptr + 1 ) ) >> BitPositionOffset ) & bits_of_interest_t::value ) << ( NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 2 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 3 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 4 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 5 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 6 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 7 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 8 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 9 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 10 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 11 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 12 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 13 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 14 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 15 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 16 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 17 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 18 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 19 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 20 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 21 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 22 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 23 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 24 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 25 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 26 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 27 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 28 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 29 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 30 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 31 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 32 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 33 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 34 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 35 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 36 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 37 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 38 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 39 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 40 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 41 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 42 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 43 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 44 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 45 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 46 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 47 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 48 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 49 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 50 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 51 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 52 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 53 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 54 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 55 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 56 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 57 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 58 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 59 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 60 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 61 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 62 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits ) ) |
               ( ( ( ( *( mask_ptr + 63 ) ) >> BitPositionOffset ) & bits_of_interest_t::value )
                  << ( NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits + NumberOfBits +
                       NumberOfBits + NumberOfBits + NumberOfBits ) )
            ),
            mask_ptr + 64
         );
      }
   
   
   };
}
#endif //TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_BITMASK_COMPLEX_BITMASK_H
