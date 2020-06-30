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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_CREATE_AVX2_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_CREATE_AVX2_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx2.h>
#include <simd/instructions/declarations/create.h>

#include <cstdint>
namespace tuddbs {

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   broadcast< avx2< uint8_t > >(
      typename avx2< uint8_t >::base_t const a
   ) {
      return _mm256_set1_epi8( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   broadcast< avx2< uint16_t > >(
      typename avx2< uint16_t >::base_t const a
   ) {
      return _mm256_set1_epi16( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   broadcast< avx2< uint32_t > >(
      typename avx2< uint32_t >::base_t const a
   ) {
      return _mm256_set1_epi32( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   broadcast< avx2< uint64_t > >(
      typename avx2< uint64_t >::base_t const a
   ) {
      return _mm256_set1_epi64x( a );
   }

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   mask_broadcast< avx2< uint8_t > >(
      typename avx2< uint8_t >::base_t const value,
      typename avx2< uint8_t >::mask_t const mask,
      typename avx2< uint8_t >::vector_t const src
   ) {
      return _mm256_mask_set1_epi8( src, mask, value );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   mask_broadcast< avx2< uint16_t > >(
      typename avx2< uint16_t >::base_t const value,
      typename avx2< uint16_t >::mask_t const mask,
      typename avx2< uint16_t >::vector_t const src
   ) {
      return _mm256_mask_set1_epi16( src, mask, value );
   }
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   mask_broadcast< avx2< uint32_t > >(
      typename avx2< uint32_t >::base_t const value,
      typename avx2< uint32_t >::mask_t const mask,
      typename avx2< uint32_t >::vector_t const src
   ) {
      return _mm256_mask_set1_epi32( src, mask, value );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   mask_broadcast< avx2< uint64_t > >(
      typename avx2< uint64_t >::base_t const value,
      typename avx2< uint64_t >::mask_t const mask,
      typename avx2< uint64_t >::vector_t const src
   ) {
      return _mm256_mask_set1_epi64( src, mask, value );
   }
#endif
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   set_zero< avx2< uint8_t > >( void ) {
      return _mm256_setzero_si256( );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   set_zero< avx2< uint16_t > >( void ) {
      return _mm256_setzero_si256( );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   set_zero< avx2< uint32_t > >( void ) {
      return _mm256_setzero_si256( );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   set_zero< avx2< uint64_t > >( void ) {
      return _mm256_setzero_si256( );
   }
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   maskz_move< avx2< uint8_t > >(
      typename avx2< uint8_t >::mask_t const m,
      typename avx2< uint8_t >::vector_t const a
   ) {
      return _mm256_maskz_mov_epi8( m, a );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   maskz_move< avx2< uint16_t > >(
      typename avx2< uint16_t >::mask_t const m,
      typename avx2< uint16_t >::vector_t const a
   ) {
      return _mm256_maskz_mov_epi16( m, a );
   }
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   maskz_move< avx2< uint32_t > >(
      typename avx2< uint32_t >::mask_t const m,
      typename avx2< uint32_t >::vector_t const a
   ) {
      return _mm256_maskz_mov_epi32( m, a );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   maskz_move< avx2< uint64_t > >(
      typename avx2< uint64_t >::mask_t const m,
      typename avx2< uint64_t >::vector_t const a
   ) {
      return _mm256_maskz_mov_epi64( m, a );
   }
#else
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   maskz_move< avx2< uint32_t > >(
      typename avx2< uint32_t >::mask_t const m,
      typename avx2< uint32_t >::vector_t const a
   ) {
      return
         _mm256_and_si256(
            a,
         _mm256_set_epi32(
            ( ( m & 0x80 ) == 0x80 ) ? 0xffffffff : 0,
            ( ( m & 0x40 ) == 0x40 ) ? 0xffffffff : 0,
            ( ( m & 0x20 ) == 0x20 ) ? 0xffffffff : 0,
            ( ( m & 0x10 ) == 0x10 ) ? 0xffffffff : 0,
            ( ( m & 0x8 ) == 0x8 ) ? 0xffffffff : 0,
            ( ( m & 0x4 ) == 0x4 ) ? 0xffffffff : 0,
            ( ( m & 0x2 ) == 0x2 ) ? 0xffffffff : 0,
            ( ( m & 0x1 ) == 0x1 ) ? 0xffffffff : 0
            )
         );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   maskz_move< avx2< uint64_t > >(
      typename avx2< uint64_t >::mask_t const m,
      typename avx2< uint64_t >::vector_t const a
   ) {
      return
         _mm256_and_si256(
            a,
         _mm256_set_epi64x(
            ( ( m & 0x8 ) == 0x8 ) ? 0xffffffffffffffff : 0,
            ( ( m & 0x4 ) == 0x4 ) ? 0xffffffffffffffff : 0,
            ( ( m & 0x2 ) == 0x2 ) ? 0xffffffffffffffff : 0,
            ( ( m & 0x1 ) == 0x1 ) ? 0xffffffffffffffff : 0
            )
         );
   }
#endif

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::mask_t
   move_mask< avx2< uint8_t > >( typename avx2< uint8_t >::vector_t const a ) {
      return _mm256_movepi8_mask( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::mask_t
   move_mask< avx2< uint16_t > >( typename avx2< uint16_t >::vector_t const a ) {
      return _mm256_movepi16_mask( a );
   }
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_DQ)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::mask_t
   move_mask< avx2< uint32_t > >( typename avx2< uint32_t >::vector_t const a ) {
      return _mm256_movepi32_mask( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::mask_t
   move_mask< avx2< uint64_t > >( typename avx2< uint64_t >::vector_t const a ) {
      return _mm256_movepi64_mask( a );
   }
#endif
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_CREATE_AVX2_H

