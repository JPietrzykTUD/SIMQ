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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_MATH_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_MATH_H

#include <simd/types/simd.h>
#include <utils/preprocessor.h>

#include <simd/utils/print.h>

namespace tuddbs {
   
   template< class VectorExtension >
   typename VectorExtension::vector_t
   add(
      typename VectorExtension::vector_t const,
      typename VectorExtension::vector_t const
   );
   
   template< class VectorExtension >
   typename VectorExtension::vector_t
   sub(
      typename VectorExtension::vector_t const,
      typename VectorExtension::vector_t const
   );
   
   template< class VectorExtension >
   typename VectorExtension::vector_t
   mask_add(
      typename VectorExtension::vector_t const,
      typename VectorExtension::vector_t const,
      typename VectorExtension::mask_t const
   );
   
   template< class VectorExtension, int NumberOfLanesPerTuple >
   NO_DISCARD FORCE_INLINE
   
   typename VectorExtension::vector_t
   reduce_add(
      typename VectorExtension::vector_t const values
   ) {
//      print< VectorExtension >( std::cerr, values, "Values" );
      typename vector_constants_t< VectorExtension >::array_t buff;
      [[maybe_unused]]typename VectorExtension::base_t * tmp          =
                                                          store< VectorExtension >( buff.data( ), values );
      typename vector_constants_t< VectorExtension >::array_t result_buff{ 0 };
      std::size_t                                             res_pos = 0;
      for(
         std::size_t                                          i       = 0;
         i < vector_constants_t< VectorExtension >::vector_element_count_t::value;
         i += NumberOfLanesPerTuple
         ) {
         typename VectorExtension::base_t result = 0;
         for(
            std::size_t                   j      = 0; j < NumberOfLanesPerTuple; ++j
            ) {
            result += buff[ i + j ];
         }
         result_buff[ res_pos ] = result;
         res_pos += NumberOfLanesPerTuple;
      }
//      print< VectorExtension >( std::cerr,  load< VectorExtension >( result_buff.data() ), "Reduced" );
      return load< VectorExtension >( result_buff.data( ) );
   }
   
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_DECLARATIONS_MATH_H
