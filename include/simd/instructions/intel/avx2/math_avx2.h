/* 
 * This file is part of the LaneLord Project (https://github.com/JPietrzykTUD/LaneLord).
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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_MATH_AVX2_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_MATH_AVX2_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx2.h>
#include <simd/instructions/declarations/math.h>

#include <cstdint>
#include <tuple>

namespace tuddbs {

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   add< avx2< uint8_t > >(
      typename avx2< uint8_t >::vector_t const a,
      typename avx2< uint8_t >::vector_t const b
   ) {
      return _mm256_add_epi8( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   add< avx2< uint16_t > >(
      typename avx2< uint16_t >::vector_t const a,
      typename avx2< uint16_t >::vector_t const b
   ) {
      return _mm256_add_epi16( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   add< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const a,
      typename avx2< uint32_t >::vector_t const b
   ) {
      return _mm256_add_epi32( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   add< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b
   ) {
      return _mm256_add_epi64( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   sub< avx2< uint8_t > >(
      typename avx2< uint8_t >::vector_t const a,
      typename avx2< uint8_t >::vector_t const b
   ) {
      return _mm256_sub_epi8( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   sub< avx2< uint16_t > >(
      typename avx2< uint16_t >::vector_t const a,
      typename avx2< uint16_t >::vector_t const b
   ) {
      return _mm256_sub_epi16( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   sub< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const a,
      typename avx2< uint32_t >::vector_t const b
   ) {
      return _mm256_sub_epi32( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   sub< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b
   ) {
      return _mm256_sub_epi64( a, b );
   }

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   mask_add< avx2< uint8_t > >(
      typename avx2< uint8_t >::vector_t const incrementor,
      typename avx2< uint8_t >::vector_t const result,
      typename avx2< uint8_t >::mask_t const mask
   ) {
      return _mm256_mask_add_epi8( result, mask, incrementor, result );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   mask_add< avx2< uint16_t > >(
      typename avx2< uint16_t >::vector_t const incrementor,
      typename avx2< uint16_t >::vector_t const result,
      typename avx2< uint16_t >::mask_t const mask
   ) {
      return _mm256_mask_add_epi16( result, mask, incrementor, result );
   }
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   mask_add< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const incrementor,
      typename avx2< uint32_t >::vector_t const result,
      typename avx2< uint32_t >::mask_t const mask
   ) {
      return _mm256_mask_add_epi32( result, mask, incrementor, result );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   mask_add< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const incrementor,
      typename avx2< uint64_t >::vector_t const result,
      typename avx2< uint64_t >::mask_t const mask
   ) {
      return _mm256_mask_add_epi64( result, mask, incrementor, result );
   }
#else
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   mask_add< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const incrementor,
      typename avx2< uint32_t >::vector_t const result,
      typename avx2< uint32_t >::mask_t const mask
   ) {
      return _mm256_add_epi32(
         result,
         _mm256_and_si256(
            _mm256_set_epi32(
               ( ( mask & 0x80 ) == 0x80 ) ? 0xffffffff : 0,
               ( ( mask & 0x40 ) == 0x40 ) ? 0xffffffff : 0,
               ( ( mask & 0x20 ) == 0x20 ) ? 0xffffffff : 0,
               ( ( mask & 0x10 ) == 0x10 ) ? 0xffffffff : 0,
               ( ( mask & 0x8 ) == 0x8 ) ? 0xffffffff : 0,
               ( ( mask & 0x4 ) == 0x4 ) ? 0xffffffff : 0,
               ( ( mask & 0x2 ) == 0x2 ) ? 0xffffffff : 0,
               ( ( mask & 0x1 ) == 0x1 ) ? 0xffffffff : 0
            ),
            incrementor
         )
      );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   mask_add< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const incrementor,
      typename avx2< uint64_t >::vector_t const result,
      typename avx2< uint64_t >::mask_t const mask
   ) {
      return _mm256_add_epi64(
         result,
         _mm256_and_si256(
            _mm256_set_epi64x(
               ( ( mask & 0x8 ) == 0x8 ) ? 0xffffffffffffffff : 0,
               ( ( mask & 0x4 ) == 0x4 ) ? 0xffffffffffffffff : 0,
               ( ( mask & 0x2 ) == 0x2 ) ? 0xffffffffffffffff : 0,
               ( ( mask & 0x1 ) == 0x1 ) ? 0xffffffffffffffff : 0
            ),
            incrementor
         )
      );
   }
#endif

}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_MATH_AVX2_H
