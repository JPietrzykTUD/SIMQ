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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_COMPARE_AVX512_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_COMPARE_AVX512_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx512.h>
#include <simd/instructions/declarations/compare.h>

#include <cstdint>

namespace tuddbs {

#if defined(INTEL_INTRINSICS_AVX512_BW)
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint8_t >::mask_t
   cmp_lt< avx512< uint8_t > >(
      typename avx512< uint8_t >::vector_t const a,
      typename avx512< uint8_t >::vector_t const b
   ) {
      return _mm512_cmplt_epu8_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint8_t >::mask_t
   cmp_neq< avx512< uint8_t > >(
      typename avx512< uint8_t >::vector_t const a,
      typename avx512< uint8_t >::vector_t const b
   ) {
      return _mm512_cmpneq_epu8_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint16_t >::mask_t
   cmp_lt< avx512< uint16_t > >(
      typename avx512< uint16_t >::vector_t const a,
      typename avx512< uint16_t >::vector_t const b
   ) {
      return _mm512_cmplt_epu16_mask( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint16_t >::mask_t
   cmp_neq< avx512< uint16_t > >(
      typename avx512< uint16_t >::vector_t const a,
      typename avx512< uint16_t >::vector_t const b
   ) {
      return _mm512_cmpneq_epu16_mask( a, b );
   }
#endif
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint32_t >::mask_t
              cmp_lt< avx512 < uint32_t >
   >(
   typename avx512< uint32_t >::vector_t const a,
   typename avx512< uint32_t >::vector_t const b
   ) {
   return
   _mm512_cmplt_epu32_mask( a, b
   );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::mask_t
           cmp_neq< avx512 < uint32_t >
>(
typename avx512< uint32_t >::vector_t const a,
typename avx512< uint32_t >::vector_t const b
) {
return
_mm512_cmpneq_epu32_mask( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::mask_t
           cmp_lt< avx512 < uint64_t >
>(
typename avx512< uint64_t >::vector_t const a,
typename avx512< uint64_t >::vector_t const b
) {
return
_mm512_cmplt_epu64_mask( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::mask_t
           cmp_neq< avx512 < uint64_t >
>(
typename avx512< uint64_t >::vector_t const a,
typename avx512< uint64_t >::vector_t const b
) {
return
_mm512_cmpneq_epu64_mask( a, b
);
}

#if defined(INTEL_INTRINSICS_AVX512_BW)
template<>
NO_DISCARD FORCE_INLINE
typename avx512< uint8_t >::vector_t
min< avx512< uint8_t > >(
   typename avx512< uint8_t >::vector_t const a,
   typename avx512< uint8_t >::vector_t const b
) {
   return _mm512_min_epu8( a, b );
}

template<>
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::vector_t
min< avx512< uint16_t > >(
   typename avx512< uint16_t >::vector_t const a,
   typename avx512< uint16_t >::vector_t const b
) {
   return _mm512_min_epu16( a, b );
}
#endif
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           min< avx512 < uint32_t >
>(
typename avx512< uint32_t >::vector_t const a,
typename avx512< uint32_t >::vector_t const b
) {
return
_mm512_min_epu32( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           min< avx512 < uint64_t >
>(
typename avx512< uint64_t >::vector_t const a,
typename avx512< uint64_t >::vector_t const b
) {
return
_mm512_min_epu64( a, b
);
}

#if defined(INTEL_INTRINSICS_AVX512_BW)
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint8_t >::vector_t
mask_min< avx512< uint8_t > >(
   typename avx512< uint8_t >::vector_t const a,
   typename avx512< uint8_t >::vector_t const b,
   typename avx512< uint8_t >::mask_t const mask
) {
   return _mm512_mask_min_epu8( b, mask, a, b );
}
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::vector_t
mask_min< avx512< uint16_t > >(
   typename avx512< uint16_t >::vector_t const a,
   typename avx512< uint16_t >::vector_t const b,
   typename avx512< uint16_t >::mask_t const mask
) {
   return _mm512_mask_min_epu16( b, mask, a, b );
}
#endif
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           mask_min< avx512 < uint32_t >
>(
typename avx512< uint32_t >::vector_t const a,
typename avx512< uint32_t >::vector_t const b,
typename avx512< uint32_t >::mask_t const   mask
) {
return
_mm512_mask_min_epu32( b, mask, a, b
);
}
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           mask_min< avx512 < uint64_t >
>(
typename avx512< uint64_t >::vector_t const a,
typename avx512< uint64_t >::vector_t const b,
typename avx512< uint64_t >::mask_t const   mask
) {
return
_mm512_mask_min_epu64( b, mask, a, b
);
}
#if defined(INTEL_INTRINSICS_AVX512_BW)
template<>
   NO_DISCARD FORCE_INLINE
   typename avx512< uint8_t >::vector_t
   max< avx512< uint8_t > >(
      typename avx512< uint8_t >::vector_t const a,
      typename avx512< uint8_t >::vector_t const b
   ) {
      return _mm512_max_epu8( a, b );
   }
   
   template<>
   NO_DISCARD FORCE_INLINE
   typename avx512< uint16_t >::vector_t
   max< avx512< uint16_t > >(
      typename avx512< uint16_t >::vector_t const a,
      typename avx512< uint16_t >::vector_t const b
   ) {
      return _mm512_max_epu16( a, b );
   }
#endif
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           max< avx512 < uint32_t >
>(
typename avx512< uint32_t >::vector_t const a,
typename avx512< uint32_t >::vector_t const b
) {
return
_mm512_max_epu32( a, b
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           max< avx512 < uint64_t >
>(
typename avx512< uint64_t >::vector_t const a,
typename avx512< uint64_t >::vector_t const b
) {
return
_mm512_max_epu64( a, b
);
}

#if defined(INTEL_INTRINSICS_AVX512_BW)
template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint8_t >::vector_t
   mask_max< avx512< uint8_t > >(
      typename avx512< uint8_t >::vector_t const a,
      typename avx512< uint8_t >::vector_t const b,
      typename avx512< uint8_t >::mask_t const mask
   ) {
      return _mm512_mask_max_epu8( b, mask, a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint16_t >::vector_t
   mask_max< avx512< uint16_t > >(
      typename avx512< uint16_t >::vector_t const a,
      typename avx512< uint16_t >::vector_t const b,
      typename avx512< uint16_t >::mask_t const mask
   ) {
      return _mm512_mask_max_epu16( b, mask, a, b );
   }
#endif
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           mask_max< avx512 < uint32_t >
>(
typename avx512< uint32_t >::vector_t const a,
typename avx512< uint32_t >::vector_t const b,
typename avx512< uint32_t >::mask_t const   mask
) {
return
_mm512_mask_max_epu32( b, mask, a, b
);
}
template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           mask_max< avx512 < uint64_t >
>(
typename avx512< uint64_t >::vector_t const a,
typename avx512< uint64_t >::vector_t const b,
typename avx512< uint64_t >::mask_t const   mask
) {
return
_mm512_mask_max_epu64( b, mask, a, b
);
}
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_COMPARE_AVX512_H
