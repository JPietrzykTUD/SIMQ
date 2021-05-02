/*
 * This file is part of the LaneLord Project (https://github.com/JPietrzykTUD/LaneLord).
 * Copyright (c) 2021 Johannes Pietrzyk.
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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_ARM_NEON_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_ARM_NEON_H

#include <type_traits>
#include <cstddef>
#include <cstdint>

#include <simd/types/simd.h>



namespace tuddbs {
   
   template< typename T >
   struct neon {
      static_assert( std::is_arithmetic< T >::value, "Basetype has to be an arithmetic type." );
      
      template< typename U >
      using cast_t = neon< U >;
      
      using base_t = T;
      using vector_t =
         typename std::conditional_t<
            std::is_integral_v< T >,
            //todo: check for signed or unsigned!!!
            std::conditional_t <
               sizeof( T ) == 1,
               uint8x16_t,
               std::conditional_t <
                  sizeof( T ) == 2,
                  uint16x8_t,
                  std::conditional_t <
                     sizeof( T ) == 4,
                     uint32x4_t,
                     uint64x2_t
                  >
               >
            >,
            float32x4_t //todo: check for float and double
      >;


      using mask_t =
      typename std::conditional<
         sizeof( T ) == 1,
         uint16_t,
         uint8_t
      >::type;
   };
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_ARM_NEON_H
