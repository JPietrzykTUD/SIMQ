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

#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_INTEL_SSE_CREATE_SSE_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_INTEL_SSE_CREATE_SSE_H
#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/sse.h>
#include <simd/instructions/declarations/create.h>
#include <cstdint>
namespace tuddbs {
   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename sse< uint8_t >::vector_t
   set< sse< uint8_t > > (
      typename sse< uint8_t >::base_t const val15,
      typename sse< uint8_t >::base_t const val14,
      typename sse< uint8_t >::base_t const val13,
      typename sse< uint8_t >::base_t const val12,
      typename sse< uint8_t >::base_t const val11,
      typename sse< uint8_t >::base_t const val10,
      typename sse< uint8_t >::base_t const val9,
      typename sse< uint8_t >::base_t const val8,
      typename sse< uint8_t >::base_t const val7,
      typename sse< uint8_t >::base_t const val6,
      typename sse< uint8_t >::base_t const val5,
      typename sse< uint8_t >::base_t const val4,
      typename sse< uint8_t >::base_t const val3,
      typename sse< uint8_t >::base_t const val2,
      typename sse< uint8_t >::base_t const val1,
      typename sse< uint8_t >::base_t const val0
   ) {
      return _mm_set_epi8(val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0);
   }
                   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename sse< uint16_t >::vector_t
   set< sse< uint16_t > > (
      typename sse< uint16_t >::base_t const val7,
      typename sse< uint16_t >::base_t const val6,
      typename sse< uint16_t >::base_t const val5,
      typename sse< uint16_t >::base_t const val4,
      typename sse< uint16_t >::base_t const val3,
      typename sse< uint16_t >::base_t const val2,
      typename sse< uint16_t >::base_t const val1,
      typename sse< uint16_t >::base_t const val0
   ) {
      return _mm_set_epi16(val7, val6, val5, val4, val3, val2, val1, val0);
   }
                   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename sse< uint32_t >::vector_t
   set< sse< uint32_t > > (
      typename sse< uint32_t >::base_t const val3,
      typename sse< uint32_t >::base_t const val2,
      typename sse< uint32_t >::base_t const val1,
      typename sse< uint32_t >::base_t const val0
   ) {
      return _mm_set_epi32(val3, val2, val1, val0);
   }
                   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename sse< uint64_t >::vector_t
   set< sse< uint64_t > > (
      typename sse< uint64_t >::base_t const val1,
      typename sse< uint64_t >::base_t const val0
   ) {
      return _mm_set_epi64x(val1, val0);
   }
                   
}
#endif
                    