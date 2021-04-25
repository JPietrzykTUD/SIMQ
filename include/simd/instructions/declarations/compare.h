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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_COMPARE_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_COMPARE_H

#include <simd/types/simd.h>

namespace tuddbs {

   template< class VectorExtension >
   typename VectorExtension::mask_t
   cmp_lt(
      typename VectorExtension::vector_t const,
      typename VectorExtension::vector_t const
   );

   template< class VectorExtension >
   typename VectorExtension::mask_t
   cmp_neq(
      typename VectorExtension::vector_t const,
      typename VectorExtension::vector_t const
   );
   
   template< class VectorExtension >
   typename VectorExtension::vector_t
   min(
      typename VectorExtension::vector_t const,
      typename VectorExtension::vector_t const
   );
   
   template< class VectorExtension >
   typename VectorExtension::vector_t
   mask_min(
      typename VectorExtension::vector_t const,
      typename VectorExtension::vector_t const,
      typename VectorExtension::mask_t const
   );
   
   template< class VectorExtension >
   typename VectorExtension::vector_t
   max(
      typename VectorExtension::vector_t const,
      typename VectorExtension::vector_t const
   );
   
   template< class VectorExtension >
   typename VectorExtension::vector_t
   mask_max(
      typename VectorExtension::vector_t const,
      typename VectorExtension::vector_t const,
      typename VectorExtension::mask_t const
   );
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_COMPARE_H
