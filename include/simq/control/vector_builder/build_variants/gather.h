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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_GATHER_H
#define TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_GATHER_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace tuddbs {
   template<
      class ColumnContainer,
      std::size_t NumberOfQueries,
      typename DepT,
      class VectorExtension
   >
   struct simq_vector_builder_gather_t {
      using T = typename VectorExtension::base_t;
      
      static constexpr char const * get_name( void ) { return "GATHER"; }
      
      FORCE_INLINE
      static
      typename VectorExtension::vector_t
      get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries >
      & svw ) {
         typename VectorExtension::vector_t
            result = gather< VectorExtension >( svw.column_data_ptr_vec, svw.min_address );
         svw.min_address += simq_column_vector_view_t < ColumnContainer, NumberOfQueries > ::get_incrementor( );
         return result;
      }
   };
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_GATHER_H
