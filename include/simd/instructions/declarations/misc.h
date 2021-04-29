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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_MISC_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_MISC_H

#include <simd/types/simd.h>
#include <simd/instructions/declarations/io.h>

namespace tuddbs {
   
   template< class VectorExtension >
   char const * vector_extension_to_str( void );
   
   template< class VectorExtension >
   typename VectorExtension::vector_t
   blend(
      typename VectorExtension::vector_t const,
      typename VectorExtension::mask_t const,
      typename VectorExtension::vector_t const
   );

//   template< class VectorExtension >
//   typename VectorExtension::vector_t
//   mask_expand(
//      typename VectorExtension::vector_t const,
//      typename VectorExtension::mask_t const,
//      typename VectorExtension::vector_t const
//   );

}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_MISC_H
