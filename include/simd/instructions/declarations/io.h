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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_IO_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_IO_H

#include <simd/types/simd.h>

namespace tuddbs {
   
   template< class VectorExtension >
   typename VectorExtension::vector_t
   load(
      typename VectorExtension::base_t * const
   );
   
   template< class VectorExtension >
   typename VectorExtension::base_t *
   store(
      typename VectorExtension::base_t * const,
      typename VectorExtension::vector_t const
   );
   
   /*
   template< class VectorExtension >
   struct store_impl;

   template< class VectorExtension >
   NO_DISCARD FORCE_INLINE
   typename VectorExtension::base_t *
   store(
      typename VectorExtension::base_t * const a,
      typename VectorExtension::vector_t const b
   ) {
      return store_impl< VectorExtension >::apply( a, b );
   }
*/
   template< class VectorExtension >
   struct stream_store_impl;
   
   template< class VectorExtension >
   NO_DISCARD FORCE_INLINE
   
   typename VectorExtension::base_t *
   stream_store(
      typename VectorExtension::base_t * const a,
      typename VectorExtension::vector_t const b
   ) {
      return stream_store_impl< VectorExtension >::apply( a, b );
   }
   
   template< class VectorExtension, std::size_t Scale >
   struct gather_impl;
   
   template< class VectorExtension, std::size_t Scale = sizeof( typename VectorExtension::base_t ) >
   NO_DISCARD FORCE_INLINE
   
   typename VectorExtension::vector_t
   gather(
      typename VectorExtension::vector_t const vidx,
      typename VectorExtension::base_t * const min
   ) {
      return gather_impl< VectorExtension, Scale >::apply( vidx, min );
   }
   
   template< class VectorExtension >
   typename VectorExtension::mask_t
   load_mask(
      typename VectorExtension::mask_t * const
   );
   
   template< class VectorExtension >
   void
   store_mask(
      typename VectorExtension::mask_t * const,
      typename VectorExtension::mask_t const
   );
   
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_IO_H
