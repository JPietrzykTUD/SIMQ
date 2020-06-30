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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_SET_H
#define TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_SET_H

namespace tuddbs {
   template<
      class ColumnContainer,
      std::size_t NumberOfQueries,
      typename DepT,
      class VectorExtension
   >
   struct simq_vector_builder_set_t;
}


#ifdef INTEL_SIMDI
#include <generated/simq/control/vector_builder/build_variants/set/set_sse.h>
#include <generated/simq/control/vector_builder/build_variants/set/set_avx2.h>
#include <generated/simq/control/vector_builder/build_variants/set/set_avx512.h>
#endif

#endif //TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_SET_H
