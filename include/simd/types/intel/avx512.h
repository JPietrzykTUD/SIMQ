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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_INTEL_AVX512_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_INTEL_AVX512_H

#include <type_traits>
#include <cstddef>
#include <cstdint>

#include <simd/types/simd.h>

#include "immintrin.h"

namespace tuddbs {

   template< typename T >
   struct avx512 {
      static_assert( std::is_arithmetic< T >::value, "Basetype has to be an arithmetic type." );
      
      template< typename U >
      using cast_t = avx512< U >;
      
      using base_t = T;
      using vector_t =
      typename std::conditional<
         std::is_integral< T >::value,
         __m512i,
         typename std::conditional<
            (std::is_floating_point< T >::value && sizeof( T ) == sizeof( float ) ),
            __m512,
            __m512d
         >::type
      >::type;
      using mask_t =
         typename std::conditional<
            sizeof( T ) == 1,
#if defined(INTEL_INTRINSICS_AVX512_BW)
            __mmask64,
#else
            uint64_t,
#endif
            typename std::conditional<
               sizeof( T ) == 2,
#if defined(INTEL_INTRINSICS_AVX512_BW)
               __mmask32,
#else
               uint32_t,
#endif
               typename std::conditional<
                  sizeof( T ) == 4,
                  __mmask16,
                  __mmask8
               >::type
            >::type
         >::type;
   };
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_INTEL_AVX512_H
