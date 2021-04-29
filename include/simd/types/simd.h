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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_SIMD_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_SIMD_H

#include <utils/preprocessor.h>

#include <cstddef>
#include <type_traits>
#include <array>

namespace tuddbs {
   
   template< typename T, std::size_t N, std::size_t Alignment >
   struct alignas(Alignment)
   aligned_array : public std::array <T, N> {
};

template< class VectorExtension >
struct vector_constants_t {
   using vector_size_byte_t =
   std::integral_constant< std::size_t, sizeof( typename VectorExtension::vector_t ) >;
   
   using vector_size_bit_t =
   std::integral_constant< std::size_t, vector_size_byte_t::value * 8 >;
   
   using vector_element_count_t =
   std::integral_constant< std::size_t, vector_size_byte_t::value / sizeof( typename VectorExtension::base_t ) >;
   
   using vector_alignment_byte_t =
   std::integral_constant< std::size_t, vector_size_byte_t::value >;
   
   using number_of_vectors_per_mask_t =
   std::integral_constant<
      std::size_t,
      ( sizeof( typename VectorExtension::mask_t ) * 8 ) / vector_element_count_t::value
   >;
   
   using shift_per_mask_t =
   std::integral_constant< std::size_t, vector_element_count_t::value >;
   
   using array_t =
   aligned_array< typename VectorExtension::base_t, vector_element_count_t::value, vector_alignment_byte_t::value >;
};

}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_TYPES_SIMD_H
