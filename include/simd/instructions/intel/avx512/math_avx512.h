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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_MATH_AVX512_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_MATH_AVX512_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx512.h>
#include <simd/instructions/declarations/math.h>

#include <cstdint>
#include <tuple>

namespace tuddbs {

#if defined(INTEL_INTRINSICS_AVX512_BW)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint8_t >::vector_t
   add< avx512< uint8_t > >(
      typename avx512< uint8_t >::vector_t const a,
      typename avx512< uint8_t >::vector_t const b
   ) {
      return _mm512_add_epi8( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint16_t >::vector_t
   add< avx512< uint16_t > >(
      typename avx512< uint16_t >::vector_t const a,
      typename avx512< uint16_t >::vector_t const b
   ) {
      return _mm512_add_epi16( a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint8_t >::vector_t
   sub< avx512< uint8_t > >(
      typename avx512< uint8_t >::vector_t const a,
      typename avx512< uint8_t >::vector_t const b
   ) {
      return _mm512_sub_epi8( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint16_t >::vector_t
   sub< avx512< uint16_t > >(
      typename avx512< uint16_t >::vector_t const a,
      typename avx512< uint16_t >::vector_t const b
   ) {
      return _mm512_sub_epi16( a, b );
   }
#endif
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint32_t >::vector_t
              add< avx512 < uint32_t >
   >(
   typename avx512< uint32_t >::vector_t const a,
   typename avx512< uint32_t >::vector_t const b
   ) {
   return
   _mm512_add_epi32( a, b
   );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           add< avx512 < uint64_t >
>(
typename avx512< uint64_t >::vector_t const a,
typename avx512< uint64_t >::vector_t const b
) {
return
_mm512_add_epi64( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           sub< avx512 < uint32_t >
>(
typename avx512< uint32_t >::vector_t const a,
typename avx512< uint32_t >::vector_t const b
) {
return
_mm512_sub_epi32( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           sub< avx512 < uint64_t >
>(
typename avx512< uint64_t >::vector_t const a,
typename avx512< uint64_t >::vector_t const b
) {
return
_mm512_sub_epi64( a, b
);
}

#if defined(INTEL_INTRINSICS_AVX512_BW)
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint8_t >::vector_t
mask_add< avx512< uint8_t > >(
   typename avx512< uint8_t >::vector_t const incrementor,
   typename avx512< uint8_t >::vector_t const result,
   typename avx512< uint8_t >::mask_t const mask
) {
   return _mm512_mask_add_epi8( result, mask, incrementor, result );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::vector_t
mask_add< avx512< uint16_t > >(
   typename avx512< uint16_t >::vector_t const incrementor,
   typename avx512< uint16_t >::vector_t const result,
   typename avx512< uint16_t >::mask_t const mask
) {
   return _mm512_mask_add_epi16( result, mask, incrementor, result );
}
#endif
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           mask_add< avx512 < uint32_t >
>(
typename avx512< uint32_t >::vector_t const incrementor,
typename avx512< uint32_t >::vector_t const result,
typename avx512< uint32_t >::mask_t const   mask
) {
return
_mm512_mask_add_epi32( result, mask, incrementor, result
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           mask_add< avx512 < uint64_t >
>(
typename avx512< uint64_t >::vector_t const incrementor,
typename avx512< uint64_t >::vector_t const result,
typename avx512< uint64_t >::mask_t const   mask
) {
return
_mm512_mask_add_epi64( result, mask, incrementor, result
);
}

}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_MATH_AVX512_H
