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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_MISC_SSE_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_MISC_SSE_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/sse.h>
#include <simd/instructions/declarations/misc.h>

#include <cstdint>

namespace tuddbs {
   template< >
   char const * vector_extension_to_str< sse < uint8_t >
   >( void ) {
   return "SSE;u8";
}
template< >
char const * vector_extension_to_str< sse < uint16_t >
>( void ) {
return "SSE;u16";
}
template< >
char const * vector_extension_to_str< sse < uint32_t >
>( void ) {
return "SSE;u32";
}
template< >
char const * vector_extension_to_str< sse < uint64_t >
>( void ) {
return "SSE;u64";
}
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint8_t >::vector_t
blend< sse< uint8_t > >(
   typename sse< uint8_t >::vector_t const value,
   typename sse< uint8_t >::mask_t const mask,
   typename sse< uint8_t >::vector_t const src
) {
   return _mm_mask_blend_epi8( mask, src, value );
}
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint16_t >::vector_t
blend< sse< uint16_t > >(
   typename sse< uint16_t >::vector_t const value,
   typename sse< uint16_t >::mask_t const mask,
   typename sse< uint16_t >::vector_t const src
) {
   return _mm_mask_blend_epi16( mask, src, value );
}
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint32_t >::vector_t
blend< sse< uint32_t > >(
   typename sse< uint32_t >::vector_t const value,
   typename sse< uint32_t >::mask_t const mask,
   typename sse< uint32_t >::vector_t const src
) {
   return _mm_mask_blend_epi32( mask, src, value );
}
template< >
NO_DISCARD FORCE_INLINE
typename sse< uint64_t >::vector_t
blend< sse< uint64_t > >(
   typename sse< uint64_t >::vector_t const value,
   typename sse< uint64_t >::mask_t const mask,
   typename sse< uint64_t >::vector_t const src
) {
   return _mm_mask_blend_epi64( mask, src, value );
}
#endif
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_SSE_MISC_SSE_H
