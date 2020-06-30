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
#ifndef TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_CORE_FILTER_POINT_FILTER_COMPARATOR_CORE_H
#define TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_CORE_FILTER_POINT_FILTER_COMPARATOR_CORE_H

#include <simd/intrin.h>
#include <utils/preprocessor.h>

namespace tuddbs {

   template< class VectorExtension >
   struct point_filter_lt_core {
      NO_DISCARD FORCE_INLINE
      static
      typename VectorExtension::mask_t
      apply( typename VectorExtension::vector_t const a, typename VectorExtension::vector_t const b ) {
         return cmp_lt< VectorExtension >( a, b );
      }
   };

}

#endif //TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_CORE_FILTER_POINT_FILTER_COMPARATOR_CORE_H
