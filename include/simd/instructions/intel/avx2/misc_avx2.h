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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_MISC_AVX2_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_MISC_AVX2_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx2.h>
#include <simd/instructions/declarations/misc.h>

#include <cstdint>

namespace tuddbs {
   template< >
   char const * vector_extension_to_str< avx2< uint8_t > >( void ) {
      return "AVX2;u8";
   }
   template< >
   char const * vector_extension_to_str< avx2< uint16_t > >( void ) {
      return "AVX2;u16";
   }
   template< >
   char const * vector_extension_to_str< avx2< uint32_t > >( void ) {
      return "AVX2;u32";
   }
   template< >
   char const * vector_extension_to_str< avx2< uint64_t > >( void ) {
      return "AVX2;u64";
   }

#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   blend< avx2< uint8_t > >(
      typename avx2< uint8_t >::vector_t const value,
      typename avx2< uint8_t >::mask_t const mask,
      typename avx2< uint8_t >::vector_t const src
   ) {
      return _mm256_mask_blend_epi8( mask, src, value );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   blend< avx2< uint16_t > >(
      typename avx2< uint16_t >::vector_t const value,
      typename avx2< uint16_t >::mask_t const mask,
      typename avx2< uint16_t >::vector_t const src
   ) {
      return _mm256_mask_blend_epi16( mask, src, value );
   }
#endif
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_F)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   blend< avx2< uint32_t > >(
      typename avx2< uint32_t >::vector_t const value,
      typename avx2< uint32_t >::mask_t const mask,
      typename avx2< uint32_t >::vector_t const src
   ) {
      return _mm256_mask_blend_epi32( mask, src, value );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   blend< avx2< uint64_t > >(
      typename avx2< uint64_t >::vector_t const value,
      typename avx2< uint64_t >::mask_t const mask,
      typename avx2< uint64_t >::vector_t const src
   ) {
      return _mm256_mask_blend_epi64( mask, src, value );
   }
#endif

}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_MISC_AVX2_H
