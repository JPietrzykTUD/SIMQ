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

#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_INTEL_AVX512_CREATE_AVX512_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_INTEL_AVX512_CREATE_AVX512_H
#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx512.h>
#include <simd/instructions/declarations/create.h>
#include <cstdint>
namespace tuddbs {
   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename avx512< uint8_t >::vector_t
   set< avx512< uint8_t > > (
      typename avx512< uint8_t >::base_t const val63,
      typename avx512< uint8_t >::base_t const val62,
      typename avx512< uint8_t >::base_t const val61,
      typename avx512< uint8_t >::base_t const val60,
      typename avx512< uint8_t >::base_t const val59,
      typename avx512< uint8_t >::base_t const val58,
      typename avx512< uint8_t >::base_t const val57,
      typename avx512< uint8_t >::base_t const val56,
      typename avx512< uint8_t >::base_t const val55,
      typename avx512< uint8_t >::base_t const val54,
      typename avx512< uint8_t >::base_t const val53,
      typename avx512< uint8_t >::base_t const val52,
      typename avx512< uint8_t >::base_t const val51,
      typename avx512< uint8_t >::base_t const val50,
      typename avx512< uint8_t >::base_t const val49,
      typename avx512< uint8_t >::base_t const val48,
      typename avx512< uint8_t >::base_t const val47,
      typename avx512< uint8_t >::base_t const val46,
      typename avx512< uint8_t >::base_t const val45,
      typename avx512< uint8_t >::base_t const val44,
      typename avx512< uint8_t >::base_t const val43,
      typename avx512< uint8_t >::base_t const val42,
      typename avx512< uint8_t >::base_t const val41,
      typename avx512< uint8_t >::base_t const val40,
      typename avx512< uint8_t >::base_t const val39,
      typename avx512< uint8_t >::base_t const val38,
      typename avx512< uint8_t >::base_t const val37,
      typename avx512< uint8_t >::base_t const val36,
      typename avx512< uint8_t >::base_t const val35,
      typename avx512< uint8_t >::base_t const val34,
      typename avx512< uint8_t >::base_t const val33,
      typename avx512< uint8_t >::base_t const val32,
      typename avx512< uint8_t >::base_t const val31,
      typename avx512< uint8_t >::base_t const val30,
      typename avx512< uint8_t >::base_t const val29,
      typename avx512< uint8_t >::base_t const val28,
      typename avx512< uint8_t >::base_t const val27,
      typename avx512< uint8_t >::base_t const val26,
      typename avx512< uint8_t >::base_t const val25,
      typename avx512< uint8_t >::base_t const val24,
      typename avx512< uint8_t >::base_t const val23,
      typename avx512< uint8_t >::base_t const val22,
      typename avx512< uint8_t >::base_t const val21,
      typename avx512< uint8_t >::base_t const val20,
      typename avx512< uint8_t >::base_t const val19,
      typename avx512< uint8_t >::base_t const val18,
      typename avx512< uint8_t >::base_t const val17,
      typename avx512< uint8_t >::base_t const val16,
      typename avx512< uint8_t >::base_t const val15,
      typename avx512< uint8_t >::base_t const val14,
      typename avx512< uint8_t >::base_t const val13,
      typename avx512< uint8_t >::base_t const val12,
      typename avx512< uint8_t >::base_t const val11,
      typename avx512< uint8_t >::base_t const val10,
      typename avx512< uint8_t >::base_t const val9,
      typename avx512< uint8_t >::base_t const val8,
      typename avx512< uint8_t >::base_t const val7,
      typename avx512< uint8_t >::base_t const val6,
      typename avx512< uint8_t >::base_t const val5,
      typename avx512< uint8_t >::base_t const val4,
      typename avx512< uint8_t >::base_t const val3,
      typename avx512< uint8_t >::base_t const val2,
      typename avx512< uint8_t >::base_t const val1,
      typename avx512< uint8_t >::base_t const val0
   ) {
      return _mm512_set_epi8(val63, val62, val61, val60, val59, val58, val57, val56, val55, val54, val53, val52, val51, val50, val49, val48, val47, val46, val45, val44, val43, val42, val41, val40, val39, val38, val37, val36, val35, val34, val33, val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0);
   }
                   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename avx512< uint16_t >::vector_t
   set< avx512< uint16_t > > (
      typename avx512< uint16_t >::base_t const val31,
      typename avx512< uint16_t >::base_t const val30,
      typename avx512< uint16_t >::base_t const val29,
      typename avx512< uint16_t >::base_t const val28,
      typename avx512< uint16_t >::base_t const val27,
      typename avx512< uint16_t >::base_t const val26,
      typename avx512< uint16_t >::base_t const val25,
      typename avx512< uint16_t >::base_t const val24,
      typename avx512< uint16_t >::base_t const val23,
      typename avx512< uint16_t >::base_t const val22,
      typename avx512< uint16_t >::base_t const val21,
      typename avx512< uint16_t >::base_t const val20,
      typename avx512< uint16_t >::base_t const val19,
      typename avx512< uint16_t >::base_t const val18,
      typename avx512< uint16_t >::base_t const val17,
      typename avx512< uint16_t >::base_t const val16,
      typename avx512< uint16_t >::base_t const val15,
      typename avx512< uint16_t >::base_t const val14,
      typename avx512< uint16_t >::base_t const val13,
      typename avx512< uint16_t >::base_t const val12,
      typename avx512< uint16_t >::base_t const val11,
      typename avx512< uint16_t >::base_t const val10,
      typename avx512< uint16_t >::base_t const val9,
      typename avx512< uint16_t >::base_t const val8,
      typename avx512< uint16_t >::base_t const val7,
      typename avx512< uint16_t >::base_t const val6,
      typename avx512< uint16_t >::base_t const val5,
      typename avx512< uint16_t >::base_t const val4,
      typename avx512< uint16_t >::base_t const val3,
      typename avx512< uint16_t >::base_t const val2,
      typename avx512< uint16_t >::base_t const val1,
      typename avx512< uint16_t >::base_t const val0
   ) {
      return _mm512_set_epi16(val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0);
   }
                   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename avx512< uint32_t >::vector_t
   set< avx512< uint32_t > > (
      typename avx512< uint32_t >::base_t const val15,
      typename avx512< uint32_t >::base_t const val14,
      typename avx512< uint32_t >::base_t const val13,
      typename avx512< uint32_t >::base_t const val12,
      typename avx512< uint32_t >::base_t const val11,
      typename avx512< uint32_t >::base_t const val10,
      typename avx512< uint32_t >::base_t const val9,
      typename avx512< uint32_t >::base_t const val8,
      typename avx512< uint32_t >::base_t const val7,
      typename avx512< uint32_t >::base_t const val6,
      typename avx512< uint32_t >::base_t const val5,
      typename avx512< uint32_t >::base_t const val4,
      typename avx512< uint32_t >::base_t const val3,
      typename avx512< uint32_t >::base_t const val2,
      typename avx512< uint32_t >::base_t const val1,
      typename avx512< uint32_t >::base_t const val0
   ) {
      return _mm512_set_epi32(val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1, val0);
   }
                   
   template< >
   NO_DISCARD
   FORCE_INLINE
   typename avx512< uint64_t >::vector_t
   set< avx512< uint64_t > > (
      typename avx512< uint64_t >::base_t const val7,
      typename avx512< uint64_t >::base_t const val6,
      typename avx512< uint64_t >::base_t const val5,
      typename avx512< uint64_t >::base_t const val4,
      typename avx512< uint64_t >::base_t const val3,
      typename avx512< uint64_t >::base_t const val2,
      typename avx512< uint64_t >::base_t const val1,
      typename avx512< uint64_t >::base_t const val0
   ) {
      return _mm512_set_epi64(val7, val6, val5, val4, val3, val2, val1, val0);
   }
                   
}
#endif
                    