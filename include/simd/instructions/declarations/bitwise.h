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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_BITWISE_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_BITWISE_H

#include <simd/types/simd.h>

namespace tuddbs {

   template< typename T, class VectorExtension >
   struct bitwise_xor_t;

   template< class VectorExtension >
   NO_DISCARD FORCE_INLINE
   typename VectorExtension::vector_t
   bitwise_xor(
      typename VectorExtension::vector_t const a,
      typename VectorExtension::vector_t const b
   ) {
      return bitwise_xor_t< typename VectorExtension::base_t, VectorExtension >::apply( a, b );
   }

   template< typename T, class VectorExtension >
   struct bitwise_or_t;

   template< class VectorExtension >
   NO_DISCARD FORCE_INLINE
   typename VectorExtension::vector_t
   bitwise_or(
      typename VectorExtension::vector_t const a,
      typename VectorExtension::vector_t const b
   ) {
      return bitwise_or_t< typename VectorExtension::base_t, VectorExtension >::apply( a, b );
   }

   template< typename T, class VectorExtension >
   struct bitwise_and_t;

   template< class VectorExtension >
   NO_DISCARD FORCE_INLINE
   typename VectorExtension::vector_t
   bitwise_and(
      typename VectorExtension::vector_t const a,
      typename VectorExtension::vector_t const b
   ) {
      return bitwise_and_t< typename VectorExtension::base_t, VectorExtension >::apply( a, b );
   }
   
   template< typename T, class VectorExtension >
   struct bitwise_and_not_t;
   
   template< class VectorExtension >
   NO_DISCARD FORCE_INLINE
   typename VectorExtension::vector_t
   bitwise_and_not(
      typename VectorExtension::vector_t const a,
      typename VectorExtension::vector_t const b
   ) {
      return bitwise_and_not_t< typename VectorExtension::base_t, VectorExtension >::apply( a, b );
   }
   

   template< class VectorExtension, int I >
   struct bitshift_left_t;

   template< class VectorExtension, int I >
   NO_DISCARD FORCE_INLINE
   typename VectorExtension::vector_t
   bitshift_left( typename VectorExtension::vector_t const a ) {
      return bitshift_left_t< VectorExtension, I >::apply( a );
   }

   template< class VectorExtension, int I >
   struct bitshift_right_t;

   template< class VectorExtension, int I >
   NO_DISCARD FORCE_INLINE
   typename VectorExtension::vector_t
   bitshift_right( typename VectorExtension::vector_t const a ) {
      return bitshift_right_t< VectorExtension, I >::apply( a );
   }
   
   
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_BITWISE_H
