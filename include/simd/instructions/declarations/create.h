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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_CREATE_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_CREATE_H

#include <simd/types/simd.h>

namespace tuddbs {

   template< class VectorExtension >
   typename VectorExtension::vector_t
   broadcast(
      typename VectorExtension::base_t const
   );

   template< class VectorExtension >
   typename VectorExtension::vector_t
   mask_broadcast(
      typename VectorExtension::base_t const,
      typename VectorExtension::mask_t const,
      typename VectorExtension::vector_t const
   );

   template< class VectorExtension >
   typename VectorExtension::vector_t
   set_zero( void );

   template< class VectorExtension >
   typename VectorExtension::vector_t
   maskz_move(
      typename VectorExtension::mask_t const,
      typename VectorExtension::vector_t const
   );

   template< class VectorExtension >
   typename VectorExtension::mask_t
   move_mask( typename VectorExtension::vector_t const );

}
#ifdef INTEL_SIMDI
#  include <generated/simd/instructions/declarations/create.h>
#endif

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_CREATE_H
