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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_BITWISE_NEON_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_BITWISE_NEON_H
#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/sse.h>
#include <simd/instructions/declarations/bitwise.h>

#include <cstdint>

namespace tuddbs {
   template< typename T >
   struct bitwise_xor_t< T, sse< T > > {
      NO_DISCARD FORCE_INLINE
      static
      typename sse< T >::vector_t
      apply(
         typename sse< T >::vector_t const a,
         typename sse< T >::vector_t const b
      ) {
         return _mm_xor_si128( a, b );
      }
   };
   template< typename T >
   struct bitwise_or_t< T, sse< T > > {
      NO_DISCARD FORCE_INLINE
      static
      typename sse< T >::vector_t
      apply(
         typename sse< T >::vector_t const a,
         typename sse< T >::vector_t const b
      ) {
         return _mm_or_si128( a, b );
      }
   };
   template< typename T >
   struct bitwise_and_t< T, sse< T > > {
      NO_DISCARD FORCE_INLINE
      static
      typename sse< T >::vector_t
      apply(
         typename sse< T >::vector_t const a,
         typename sse< T >::vector_t const b
      ) {
         return _mm_and_si128( a, b );
      }
   };

   template< typename T >
   struct bitwise_and_not_t< T, sse< T > > {
      NO_DISCARD FORCE_INLINE
      static
      typename sse< T >::vector_t
      apply(
         typename sse< T >::vector_t const a,
         typename sse< T >::vector_t const b
      ) {
         return _mm_andnot_si128( a, b );
      }
   };
   


//use this with care!
   template< typename T, int I >
   struct bitshift_left_t< sse< T >, I > {
      NO_DISCARD FORCE_INLINE
      static
      typename sse< T >::vector_t
      apply(
         typename sse< T >::vector_t const a
      ) {
         return _mm_slli_epi64( a, I );
      }
   };

   //use this with care!
   template< typename T, int I >
   struct bitshift_right_t< sse< T >, I > {
      NO_DISCARD FORCE_INLINE
      static
      typename sse< T >::vector_t
      apply(
         typename sse< T >::vector_t const a
      ) {
         return _mm_srli_epi64( a, I );
      }
   };
}


#endif