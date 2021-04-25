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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_COMPARE_AVX2_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_COMPARE_AVX2_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx2.h>
#include <simd/instructions/declarations/compare.h>

#include <cstdint>

namespace tuddbs {

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::mask_t
   cmp_lt< avx2< uint8_t > >(
      typename avx2< uint8_t >::vector_t const a,
      typename avx2< uint8_t >::vector_t const b
   ) {
      return _mm256_cmplt_epu8_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::mask_t
   cmp_neq< avx2< uint8_t > >(
      typename avx2< uint8_t >::vector_t const a,
      typename avx2< uint8_t >::vector_t const b
   ) {
      return _mm256_cmpneq_epu8_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::mask_t
   cmp_lt< avx2< uint16_t > >(
      typename avx2< uint16_t >::vector_t const a,
      typename avx2< uint16_t >::vector_t const b
   ) {
      return _mm256_cmplt_epu16_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::mask_t
   cmp_neq< avx2< uint16_t > >(
      typename avx2< uint16_t >::vector_t const a,
      typename avx2< uint16_t >::vector_t const b
   ) {
      return _mm256_cmpneq_epu16_mask( a, b );
   }
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::mask_t
   cmp_lt< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const a,
      typename avx2< uint32_t >::vector_t const b
   ) {
      return _mm256_cmplt_epu32_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::mask_t
   cmp_neq< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const a,
      typename avx2< uint32_t >::vector_t const b
   ) {
      return _mm256_cmpneq_epu32_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::mask_t
   cmp_lt< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b
   ) {
      return _mm256_cmplt_epu64_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::mask_t
   cmp_neq< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b
   ) {
      return _mm256_cmpneq_epu64_mask( a, b );
   }
#else
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::mask_t
   cmp_lt< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const a,
      typename avx2< uint32_t >::vector_t const b
   ) {
      // ( ~ ( a == b ) ) & ( ( ~ ( a > b ) ) & 0xffffffff )
      return _mm256_movemask_ps(
         _mm256_castsi256_ps(
            _mm256_andnot_si256(
               _mm256_cmpeq_epi32( a, b ),
               _mm256_andnot_si256(
                     _mm256_cmpgt_epi32( a, b ),
                  _mm256_set1_epi32( 0xffffffff )
               )
            )
         )
      );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::mask_t
   cmp_lt< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b
   ) {
      // ( ~ ( a == b ) ) & ( ( ~ ( a > b ) ) & 0xffffffff )
      return _mm256_movemask_pd(
         _mm256_castsi256_pd(
            _mm256_andnot_si256(
                  _mm256_cmpeq_epi64( a, b ),
               _mm256_andnot_si256(
                     _mm256_cmpgt_epi64( a, b ),
                  _mm256_set1_epi64x( 0xffffffffffffffff )
               )
            )
         )
      );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::mask_t
   cmp_neq< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const a,
      typename avx2< uint32_t >::vector_t const b
   ) {
      return _mm256_movemask_ps(
         _mm256_castsi256_ps(
            _mm256_andnot_si256(
               _mm256_cmpeq_epi32( a, b ),
               _mm256_set1_epi32( 0xffffffff )
            )
         )
      );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::mask_t
   cmp_neq< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b
   ) {
      return _mm256_movemask_pd(
         _mm256_castsi256_pd(
            _mm256_andnot_si256(
                  _mm256_cmpeq_epi64( a, b ),
               _mm256_set1_epi64x( 0xffffffffffffffff )
            )
         )
      );
   }
#endif

   template<>
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   min< avx2< uint8_t > >(
      typename avx2< uint8_t >::vector_t const a,
      typename avx2< uint8_t >::vector_t const b
   ) {
      return _mm256_min_epu8( a, b );
   }
   
   template<>
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   min< avx2< uint16_t > >(
      typename avx2< uint16_t >::vector_t const a,
      typename avx2< uint16_t >::vector_t const b
   ) {
      return _mm256_min_epu16( a, b );
   }
   
   template<>
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   min< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const a,
      typename avx2< uint32_t >::vector_t const b
   ) {
      return _mm256_min_epu32( a, b );
   }
   
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
   template<>
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   min< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b
   ) {
      return _mm256_min_epu64( a, b );
   }
#endif

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW) && defined(INTEL_INTRINSICS_AVX512_F)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   mask_min< avx2< uint8_t > >(
      typename avx2< uint8_t >::vector_t const a,
      typename avx2< uint8_t >::vector_t const b,
      typename avx2< uint8_t >::mask_t const mask
   ) {
      return _mm256_mask_min_epu8( b, mask, a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   mask_min< avx2< uint16_t > >(
      typename avx2< uint16_t >::vector_t const a,
      typename avx2< uint16_t >::vector_t const b,
      typename avx2< uint16_t >::mask_t const mask
   ) {
      return _mm256_mask_min_epu16( b, mask, a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   mask_min< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const a,
      typename avx2< uint32_t >::vector_t const b,
      typename avx2< uint32_t >::mask_t const mask
   ) {
      return _mm256_mask_min_epu32( b, mask, a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   mask_min< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b,
      typename avx2< uint64_t >::mask_t const mask
   ) {
      return _mm256_mask_min_epu64( b, mask, a, b );
   }
#endif
template<>
NO_DISCARD FORCE_INLINE
typename avx2< uint8_t >::vector_t
   max< avx2< uint8_t > >(
typename avx2< uint8_t >::vector_t const a,
typename avx2< uint8_t >::vector_t const b
) {
return _mm256_max_epu8( a, b );
}

template<>
NO_DISCARD FORCE_INLINE
typename avx2< uint16_t >::vector_t
   max< avx2< uint16_t > >(
typename avx2< uint16_t >::vector_t const a,
typename avx2< uint16_t >::vector_t const b
) {
return _mm256_max_epu16( a, b );
}

template<>
NO_DISCARD FORCE_INLINE
typename avx2< uint32_t >::vector_t
   max< avx2< uint32_t > >(
typename avx2< uint32_t >::vector_t const a,
typename avx2< uint32_t >::vector_t const b
) {
return _mm256_max_epu32( a, b );
}

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
template<>
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   max< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b
   ) {
      return _mm256_max_epu64( a, b );
   }
#endif

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW) && defined(INTEL_INTRINSICS_AVX512_F)
template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   mask_max< avx2< uint8_t > >(
      typename avx2< uint8_t >::vector_t const a,
      typename avx2< uint8_t >::vector_t const b,
      typename avx2< uint8_t >::mask_t const mask
   ) {
      return _mm256_mask_max_epu8( b, mask, a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   mask_max< avx2< uint16_t > >(
      typename avx2< uint16_t >::vector_t const a,
      typename avx2< uint16_t >::vector_t const b,
      typename avx2< uint16_t >::mask_t const mask
   ) {
      return _mm256_mask_max_epu16( b, mask, a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   mask_max< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const a,
      typename avx2< uint32_t >::vector_t const b,
      typename avx2< uint32_t >::mask_t const mask
   ) {
      return _mm256_mask_max_epu32( b, mask, a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   mask_max< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const a,
      typename avx2< uint64_t >::vector_t const b,
      typename avx2< uint64_t >::mask_t const mask
   ) {
      return _mm256_mask_max_epu64( b, mask, a, b );
   }
#endif
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_COMPARE_AVX2_H
