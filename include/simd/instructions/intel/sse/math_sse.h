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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_MATH_SSE_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_MATH_SSE_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/sse.h>
#include <simd/instructions/declarations/math.h>

#include <cstdint>
#include <tuple>

namespace tuddbs {
   
   template< >
   NO_DISCARD FORCE_INLINE
   typename sse< uint8_t >::vector_t
              add< sse < uint8_t >
   >(
   typename sse< uint8_t >::vector_t const a,
   typename sse< uint8_t >::vector_t const b
   ) {
   return
   _mm_add_epi8( a, b
   );
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint16_t >::vector_t
           add< sse < uint16_t >
>(
typename sse< uint16_t >::vector_t const a,
typename sse< uint16_t >::vector_t const b
) {
return
_mm_add_epi16( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
           add< sse < uint32_t >
>(
typename sse< uint32_t >::vector_t const a,
typename sse< uint32_t >::vector_t const b
) {
return
_mm_add_epi32( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::vector_t
           add< sse < uint64_t >
>(
typename sse< uint64_t >::vector_t const a,
typename sse< uint64_t >::vector_t const b
) {
return
_mm_add_epi64( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint8_t >::vector_t
           sub< sse < uint8_t >
>(
typename sse< uint8_t >::vector_t const a,
typename sse< uint8_t >::vector_t const b
) {
return
_mm_sub_epi8( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint16_t >::vector_t
           sub< sse < uint16_t >
>(
typename sse< uint16_t >::vector_t const a,
typename sse< uint16_t >::vector_t const b
) {
return
_mm_sub_epi16( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
           sub< sse < uint32_t >
>(
typename sse< uint32_t >::vector_t const a,
typename sse< uint32_t >::vector_t const b
) {
return
_mm_sub_epi32( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::vector_t
           sub< sse < uint64_t >
>(
typename sse< uint64_t >::vector_t const a,
typename sse< uint64_t >::vector_t const b
) {
return
_mm_sub_epi64( a, b
);
}

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint8_t >::vector_t
mask_add< sse< uint8_t > >(
   typename sse< uint8_t >::vector_t const incrementor,
   typename sse< uint8_t >::vector_t const result,
   typename sse< uint8_t >::mask_t const mask
) {
   return _mm_mask_add_epi8( result, mask, incrementor, result );
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint16_t >::vector_t
mask_add< sse< uint16_t > >(
   typename sse< uint16_t >::vector_t const incrementor,
   typename sse< uint16_t >::vector_t const result,
   typename sse< uint16_t >::mask_t const mask
) {
   return _mm_mask_add_epi16( result, mask, incrementor, result );
}
#endif

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
mask_add< sse< uint32_t > >(
   typename sse< uint32_t >::vector_t const incrementor,
   typename sse< uint32_t >::vector_t const result,
   typename sse< uint32_t >::mask_t const mask
) {
   return _mm_mask_add_epi32( result, mask, incrementor, result );
}

template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::vector_t
mask_add< sse< uint64_t > >(
   typename sse< uint64_t >::vector_t const incrementor,
   typename sse< uint64_t >::vector_t const result,
   typename sse< uint64_t >::mask_t const mask
) {
   return _mm_mask_add_epi64( result, mask, incrementor, result );
}
#else
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
           mask_add< sse < uint32_t >
>(
typename sse< uint32_t >::vector_t const incrementor,
typename sse< uint32_t >::vector_t const result,
typename sse< uint32_t >::mask_t const   mask
) {
return
_mm_add_epi32(
                result,
   _mm_and_si128(
   _mm_set_epi32(
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
typename sse< uint64_t >::vector_t
           mask_add< sse < uint64_t >
>(
typename sse< uint64_t >::vector_t const incrementor,
typename sse< uint64_t >::vector_t const result,
typename sse< uint64_t >::mask_t const   mask
) {
return
_mm_add_epi32(
                result,
   _mm_and_si128(
   _mm_set_epi64x(
      ( ( mask & 0x2 ) == 0x2 ) ? 0xffffffffffffffff : 0,
      ( ( mask & 0x1 ) == 0x1 ) ? 0xffffffffffffffff : 0
   ),
   incrementor
)
);
}
#endif
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_MATH_SSE_H
