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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_INTEL_AVX2_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_INTEL_AVX2_H

#include <type_traits>
#include <cstddef>
#include <cstdint>

#include <simd/types/simd.h>

#include "immintrin.h"

namespace tuddbs {
   
   template< typename T >
   struct avx2 {
      static_assert( std::is_arithmetic< T >::value, "Basetype has to be an arithmetic type." );
      
      template< typename U >
      using cast_t = avx2< U >;
      
      using base_t = T;
      using vector_t =
      typename std::conditional<
         std::is_integral< T >::value,
         __m256i,
         typename std::conditional<
            ( std::is_floating_point< T >::value && sizeof( T ) == sizeof( float ) ),
            __m256,
            __m256d
         >::type
      >::type;
#if defined(INTEL_INTRINSICS_AVX512_VL) && defined(INTEL_INTRINSICS_AVX512_BW)
      using mask_t =
         typename std::conditional<
            sizeof( T ) == 1,
            __mmask32,
            typename std::conditional<
               sizeof( T ) == 2,
               __mmask16,
               __mmask8
            >::type
         >::type;
#else
      using mask_t =
      typename std::conditional<
         sizeof( T ) == 1,
         uint32_t,
         typename std::conditional<
            sizeof( T ) == 2,
            uint16_t,
            uint8_t
         >::type
      >::type;
#endif
   };
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_INTEL_AVX2_H
