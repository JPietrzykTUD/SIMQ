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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_COMPARE_SSE_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_COMPARE_SSE_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/sse.h>
#include <simd/instructions/declarations/compare.h>

#include <cstdint>

namespace tuddbs {

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint8_t >::mask_t
   cmp_lt< sse< uint8_t > >(
      typename sse< uint8_t >::vector_t const a,
      typename sse< uint8_t >::vector_t const b
   ) {
      return _mm_cmplt_epu8_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint8_t >::mask_t
   cmp_neq< sse< uint8_t > >(
      typename sse< uint8_t >::vector_t const a,
      typename sse< uint8_t >::vector_t const b
   ) {
      return _mm_cmpneq_epu8_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint16_t >::mask_t
   cmp_lt< sse< uint16_t > >(
      typename sse< uint16_t >::vector_t const a,
      typename sse< uint16_t >::vector_t const b
   ) {
      return _mm_cmplt_epu16_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint16_t >::mask_t
   cmp_neq< sse< uint16_t > >(
      typename sse< uint16_t >::vector_t const a,
      typename sse< uint16_t >::vector_t const b
   ) {
      return _mm_cmpneq_epu16_mask( a, b );
   }
#endif
   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint32_t >::mask_t
   cmp_lt< sse< uint32_t > >(
      typename sse< uint32_t >::vector_t const a,
      typename sse< uint32_t >::vector_t const b
   ) {
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
      return _mm_cmplt_epu32_mask( a, b );
#else
      return _mm_movemask_ps( _mm_castsi128_ps( _mm_cmplt_epi32( a, b ) ) );
#endif
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint32_t >::mask_t
   cmp_neq< sse< uint32_t > >(
      typename sse< uint32_t >::vector_t const a,
      typename sse< uint32_t >::vector_t const b
   ) {
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
      return _mm_cmpneq_epu32_mask( a, b );
#else
      return _mm_movemask_ps( _mm_cmpneq_ps(_mm_castsi128_ps( a ), _mm_castsi128_ps( b ) ) );
#endif
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint64_t >::mask_t
   cmp_lt< sse< uint64_t > >(
      typename sse< uint64_t >::vector_t const a,
      typename sse< uint64_t >::vector_t const b
   ) {
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
      return _mm_cmplt_epu64_mask( a, b );
#else
      return _mm_movemask_pd( _mm_cmplt_pd(_mm_castsi128_pd( a ), _mm_castsi128_pd( b ) ) );
#endif
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint64_t >::mask_t
   cmp_neq< sse< uint64_t > >(
      typename sse< uint64_t >::vector_t const a,
      typename sse< uint64_t >::vector_t const b
   ) {
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
      return _mm_cmpneq_epu64_mask( a, b );
#else
      return _mm_movemask_pd( _mm_cmpneq_pd(_mm_castsi128_pd( a ), _mm_castsi128_pd( b ) ) );
#endif
   }
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_COMPARE_SSE_H
