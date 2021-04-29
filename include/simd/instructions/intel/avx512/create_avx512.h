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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_CREATE_AVX512_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_CREATE_AVX512_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx512.h>
#include <simd/instructions/declarations/create.h>

#include <cstdint>

namespace tuddbs {
   
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint8_t >::vector_t
              broadcast< avx512 < uint8_t >
   >(
   typename avx512< uint8_t >::base_t const a
   ) {
   return
   _mm512_set1_epi8( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::vector_t
           broadcast< avx512 < uint16_t >
>(
typename avx512< uint16_t >::base_t const a
) {
return
_mm512_set1_epi16( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           broadcast< avx512 < uint32_t >
>(
typename avx512< uint32_t >::base_t const a
) {
return
_mm512_set1_epi32( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           broadcast< avx512 < uint64_t >
>(
typename avx512< uint64_t >::base_t const a
) {
return
_mm512_set1_epi64( a );
}

#if defined(INTEL_INTRINSICS_AVX512_BW)
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint8_t >::vector_t
mask_broadcast< avx512< uint8_t > >(
   typename avx512< uint8_t >::base_t const value,
   typename avx512< uint8_t >::mask_t const mask,
   typename avx512< uint8_t >::vector_t const src
) {
   return _mm512_mask_set1_epi8( src, mask, value );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::vector_t
mask_broadcast< avx512< uint16_t > >(
   typename avx512< uint16_t >::base_t const value,
   typename avx512< uint16_t >::mask_t const mask,
   typename avx512< uint16_t >::vector_t const src
) {
   return _mm512_mask_set1_epi16( src, mask, value );
}
#endif
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           mask_broadcast< avx512 < uint32_t >
>(
typename avx512< uint32_t >::base_t const   value,
typename avx512< uint32_t >::mask_t const   mask,
typename avx512< uint32_t >::vector_t const src
) {
return
_mm512_mask_set1_epi32( src, mask, value
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           mask_broadcast< avx512 < uint64_t >
>(
typename avx512< uint64_t >::base_t const   value,
typename avx512< uint64_t >::mask_t const   mask,
typename avx512< uint64_t >::vector_t const src
) {
return
_mm512_mask_set1_epi64( src, mask, value
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint8_t >::vector_t
           set_zero< avx512 < uint8_t >
>( void ) {
return

_mm512_setzero_si512( );

}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::vector_t
           set_zero< avx512 < uint16_t >
>( void ) {
return

_mm512_setzero_si512( );

}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           set_zero< avx512 < uint32_t >
>( void ) {
return

_mm512_setzero_si512( );

}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           set_zero< avx512 < uint64_t >
>( void ) {
return

_mm512_setzero_si512( );

}

#ifdef INTEL_INTRINSICS_AVX512_BW
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint8_t >::vector_t
maskz_move< avx512< uint8_t > >(
   typename avx512< uint8_t >::mask_t const m,
   typename avx512< uint8_t >::vector_t const a
) {
   return _mm512_maskz_mov_epi8( m, a );
}
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::vector_t
maskz_move< avx512< uint16_t > >(
   typename avx512< uint16_t >::mask_t const m,
   typename avx512< uint16_t >::vector_t const a
) {
   return _mm512_maskz_mov_epi16( m, a );
}
#endif
#ifdef INTEL_INTRINSICS_AVX512_F
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
maskz_move< avx512< uint32_t > >(
   typename avx512< uint32_t >::mask_t const m,
   typename avx512< uint32_t >::vector_t const a
) {
   return _mm512_maskz_mov_epi32( m, a );
}
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
maskz_move< avx512< uint64_t > >(
   typename avx512< uint64_t >::mask_t const m,
   typename avx512< uint64_t >::vector_t const a
) {
   return _mm512_maskz_mov_epi64( m, a );
}
#endif

#ifdef INTEL_INTRINSICS_AVX512_BW
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint8_t >::mask_t
move_mask< avx512< uint8_t > >( typename avx512< uint8_t >::vector_t const a ) {
   return _mm512_movepi8_mask( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::mask_t
move_mask< avx512< uint16_t > >( typename avx512< uint16_t >::vector_t const a ) {
   return _mm512_movepi16_mask( a );
}
#endif
#ifdef INTEL_INTRINSICS_AVX512_DQ
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::mask_t
move_mask< avx512< uint32_t > >( typename avx512< uint32_t >::vector_t const a ) {
   return _mm512_movepi32_mask( a );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::mask_t
move_mask< avx512< uint64_t > >( typename avx512< uint64_t >::vector_t const a ) {
   return _mm512_movepi64_mask( a );
}
#endif
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_CREATE_AVX512_H
