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
#ifndef TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_CORE_AGGREGATE_AGGREGATE_SUM_CORE_H
#define TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_CORE_AGGREGATE_AGGREGATE_SUM_CORE_H

#include <simd/intrin.h>
#include <utils/preprocessor.h>

namespace tuddbs {

   template< class VectorExtension >
   struct aggregate_mask_add {
      NO_DISCARD FORCE_INLINE
      static
      typename VectorExtension::vector_t
      apply(
         typename VectorExtension::vector_t const next_values,
         typename VectorExtension::vector_t const old_values,
         typename VectorExtension::mask_t const mask
      ) {
         return mask_add< VectorExtension >( next_values, old_values, mask );
      }

      NO_DISCARD FORCE_INLINE
      static
      typename VectorExtension::vector_t
      apply(
         typename VectorExtension::vector_t const next_values,
         typename VectorExtension::vector_t const old_values,
         typename VectorExtension::vector_t const mask_vec
      ) {
         return add< VectorExtension >( old_values, bitwise_and< VectorExtension >( next_values, mask_vec ) );
      }

      template< int NumberOfActiveLanes >
      NO_DISCARD FORCE_INLINE
      static
      typename VectorExtension::vector_t
      finalize(
         typename VectorExtension::vector_t const values
      ) {
         typename vector_constants_t< VectorExtension >::array_t buff;
         [[maybe_unused]]typename VectorExtension::base_t * tmp = store< VectorExtension >( buff.data(), values );
         typename vector_constants_t< VectorExtension >::array_t result_buff{0};
         std::size_t res_pos = 0;
         for( std::size_t i = 0; i < vector_constants_t< VectorExtension >::vector_element_count_t::value; i += NumberOfActiveLanes ) {
            typename VectorExtension::base_t result = 0;
            for( std::size_t j = 0; j < NumberOfActiveLanes; ++j ) {
               result += buff[ i + j ];
            }
            result_buff[ res_pos++ ] = result;
         }
         return load< VectorExtension >( result_buff.data() );
      }
   };

}


#endif //TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_CORE_AGGREGATE_AGGREGATE_SUM_CORE_H
