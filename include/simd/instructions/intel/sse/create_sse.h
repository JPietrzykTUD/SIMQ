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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_CREATE_SSE_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_CREATE_SSE_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/sse.h>
#include <simd/instructions/declarations/create.h>

#include <cstdint>

namespace tuddbs {
   
   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint8_t >::vector_t
              broadcast< sse < uint8_t >
   >(
   typename sse< uint8_t >::base_t const a
   ) {
   return
   _mm_set1_epi8( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint16_t >::vector_t
           broadcast< sse < uint16_t >
>(
typename sse< uint16_t >::base_t const a
) {
return
_mm_set1_epi16( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
           broadcast< sse < uint32_t >
>(
typename sse< uint32_t >::base_t const a
) {
return
_mm_set1_epi32( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::vector_t
           broadcast< sse < uint64_t >
>(
typename sse< uint64_t >::base_t const a
) {
return
_mm_set1_epi64x( a );
}

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint8_t >::vector_t
mask_broadcast< sse< uint8_t > >(
   typename sse< uint8_t >::base_t const value,
   typename sse< uint8_t >::mask_t const mask,
   typename sse< uint8_t >::vector_t const src
) {
   return _mm_mask_set1_epi8( src, mask, value );
}
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint16_t >::vector_t
mask_broadcast< sse< uint16_t > >(
   typename sse< uint16_t >::base_t const value,
   typename sse< uint16_t >::mask_t const mask,
   typename sse< uint16_t >::vector_t const src
) {
   return _mm_mask_set1_epi16( src, mask, value );
}
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
mask_broadcast< sse< uint32_t > >(
   typename sse< uint32_t >::base_t const value,
   typename sse< uint32_t >::mask_t const mask,
   typename sse< uint32_t >::vector_t const src
) {
   return _mm_mask_set1_epi32( src, mask, value );
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::vector_t
mask_broadcast< sse< uint64_t > >(
   typename sse< uint64_t >::base_t const value,
   typename sse< uint64_t >::mask_t const mask,
   typename sse< uint64_t >::vector_t const src
) {
   return _mm_mask_set1_epi64( src, mask, value );
}
#endif
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint8_t >::vector_t
           set_zero< sse < uint8_t >
>( void ) {
return

_mm_setzero_si128( );

}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint16_t >::vector_t
           set_zero< sse < uint16_t >
>( void ) {
return

_mm_setzero_si128( );

}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
           set_zero< sse < uint32_t >
>( void ) {
return

_mm_setzero_si128( );

}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::vector_t
           set_zero< sse < uint64_t >
>( void ) {
return

_mm_setzero_si128( );

}
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint8_t >::vector_t
maskz_move< sse< uint8_t > >(
   typename sse< uint8_t >::mask_t const m,
   typename sse< uint8_t >::vector_t const a
) {
   return _mm_maskz_mov_epi8( m, a );
}
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint16_t >::vector_t
maskz_move< sse< uint16_t > >(
   typename sse< uint16_t >::mask_t const m,
   typename sse< uint16_t >::vector_t const a
) {
   return _mm_maskz_mov_epi16( m, a );
}
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
maskz_move< sse< uint32_t > >(
   typename sse< uint32_t >::mask_t const m,
   typename sse< uint32_t >::vector_t const a
) {
   return _mm_maskz_mov_epi32( m, a );
}
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::vector_t
maskz_move< sse< uint64_t > >(
   typename sse< uint64_t >::mask_t const m,
   typename sse< uint64_t >::vector_t const a
) {
   return _mm_maskz_mov_epi64( m, a );
}
#else
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
           maskz_move< sse < uint32_t >
>(
typename sse< uint32_t >::mask_t const   m,
typename sse< uint32_t >::vector_t const a
) {
return
_mm_and_si128(
                a,
   _mm_set_epi32(
   ( ( m & 0x8 ) == 0x8 ) ? 0xffffffff : 0,
   ( ( m & 0x4 ) == 0x4 ) ? 0xffffffff : 0,
   ( ( m & 0x2 ) == 0x2 ) ? 0xffffffff : 0,
   ( ( m & 0x1 ) == 0x1 ) ? 0xffffffff : 0
)
);
}
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::vector_t
           maskz_move< sse < uint64_t >
>(
typename sse< uint64_t >::mask_t const   m,
typename sse< uint64_t >::vector_t const a
) {
return
_mm_and_si128(
                a,
   _mm_set_epi64x(
   ( ( m & 0x2 ) == 0x2 ) ? 0xffffffffffffffff : 0,
   ( ( m & 0x1 ) == 0x1 ) ? 0xffffffffffffffff : 0
)
);
}
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint8_t >::mask_t
move_mask< sse< uint8_t > >( typename sse< uint8_t >::vector_t const a ) {
   return _mm_movepi8_mask( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint16_t >::mask_t
move_mask< sse< uint16_t > >( typename sse< uint16_t >::vector_t const a ) {
   return _mm_movepi16_mask( a );
}
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_DQ)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::mask_t
move_mask< sse< uint32_t > >( typename sse< uint32_t >::vector_t const a ) {
   return _mm_movepi32_mask( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::mask_t
move_mask< sse< uint64_t > >( typename sse< uint64_t >::vector_t const a ) {
   return _mm_movepi64_mask( a );
}
#endif
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_CREATE_SSE_H