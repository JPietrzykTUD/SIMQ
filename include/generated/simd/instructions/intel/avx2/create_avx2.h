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

#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_INTEL_AVX2_CREATE_AVX2_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_INTEL_AVX2_CREATE_AVX2_H
#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx2.h>
#include <simd/instructions/declarations/create.h>
#include <cstdint>
namespace tuddbs {
   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename avx2< uint8_t >::vector_t
   set< avx2< uint8_t > > (
      typename avx2< uint8_t >::base_t const val31,
      typename avx2< uint8_t >::base_t const val30,
      typename avx2< uint8_t >::base_t const val29,
      typename avx2< uint8_t >::base_t const val28,
      typename avx2< uint8_t >::base_t const val27,
      typename avx2< uint8_t >::base_t const val26,
      typename avx2< uint8_t >::base_t const val25,
      typename avx2< uint8_t >::base_t const val24,
      typename avx2< uint8_t >::base_t const val23,
      typename avx2< uint8_t >::base_t const val22,
      typename avx2< uint8_t >::base_t const val21,
      typename avx2< uint8_t >::base_t const val20,
      typename avx2< uint8_t >::base_t const val19,
      typename avx2< uint8_t >::base_t const val18,
      typename avx2< uint8_t >::base_t const val17,
      typename avx2< uint8_t >::base_t const val16,
      typename avx2< uint8_t >::base_t const val15,
      typename avx2< uint8_t >::base_t const val14,
      typename avx2< uint8_t >::base_t const val13,
      typename avx2< uint8_t >::base_t const val12,
      typename avx2< uint8_t >::base_t const val11,
      typename avx2< uint8_t >::base_t const val10,
      typename avx2< uint8_t >::base_t const val9,
      typename avx2< uint8_t >::base_t const val8,
      typename avx2< uint8_t >::base_t const val7,
      typename avx2< uint8_t >::base_t const val6,
      typename avx2< uint8_t >::base_t const val5,
      typename avx2< uint8_t >::base_t const val4,
      typename avx2< uint8_t >::base_t const val3,
      typename avx2< uint8_t >::base_t const val2,
      typename avx2< uint8_t >::base_t const val1,
      typename avx2< uint8_t >::base_t const val0
   ) {
      return _mm256_set_epi8(val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0);
   }
                   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename avx2< uint16_t >::vector_t
   set< avx2< uint16_t > > (
      typename avx2< uint16_t >::base_t const val15,
      typename avx2< uint16_t >::base_t const val14,
      typename avx2< uint16_t >::base_t const val13,
      typename avx2< uint16_t >::base_t const val12,
      typename avx2< uint16_t >::base_t const val11,
      typename avx2< uint16_t >::base_t const val10,
      typename avx2< uint16_t >::base_t const val9,
      typename avx2< uint16_t >::base_t const val8,
      typename avx2< uint16_t >::base_t const val7,
      typename avx2< uint16_t >::base_t const val6,
      typename avx2< uint16_t >::base_t const val5,
      typename avx2< uint16_t >::base_t const val4,
      typename avx2< uint16_t >::base_t const val3,
      typename avx2< uint16_t >::base_t const val2,
      typename avx2< uint16_t >::base_t const val1,
      typename avx2< uint16_t >::base_t const val0
   ) {
      return _mm256_set_epi16(val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0);
   }
                   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename avx2< uint32_t >::vector_t
   set< avx2< uint32_t > > (
      typename avx2< uint32_t >::base_t const val7,
      typename avx2< uint32_t >::base_t const val6,
      typename avx2< uint32_t >::base_t const val5,
      typename avx2< uint32_t >::base_t const val4,
      typename avx2< uint32_t >::base_t const val3,
      typename avx2< uint32_t >::base_t const val2,
      typename avx2< uint32_t >::base_t const val1,
      typename avx2< uint32_t >::base_t const val0
   ) {
      return _mm256_set_epi32(val7, val6, val5, val4, val3, val2, val1, val0);
   }
                   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename avx2< uint64_t >::vector_t
   set< avx2< uint64_t > > (
      typename avx2< uint64_t >::base_t const val3,
      typename avx2< uint64_t >::base_t const val2,
      typename avx2< uint64_t >::base_t const val1,
      typename avx2< uint64_t >::base_t const val0
   ) {
      return _mm256_set_epi64x(val3, val2, val1, val0);
   }
                   
}
#endif
                    