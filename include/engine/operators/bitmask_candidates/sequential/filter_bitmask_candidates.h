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
/**
 * @brief This file contains the SISQ filter operator which materializes bitmasks along needed helper structs.
 */
#ifndef TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_BITMASK_CANDIDATES_SEQUENTIAL_FILTER_BITMASK_CANDIDATES_H
#define TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_BITMASK_CANDIDATES_SEQUENTIAL_FILTER_BITMASK_CANDIDATES_H

#include <cstddef>

#include <simd/intrin.h>
#include <utils/preprocessor.h>
#include <data/column.h>

namespace tuddbs {

   template<
      class VectorExtension_t,
      template< class > class Comparator_t
   >
   /**
    * @brief Helper Class for generating a mask.
    *
    * Vector registers may contain less than 8 elements (sse with 32-bit (and 64-bit) values, avx2 with 64-bit values.
    * A mask has to be at least 8-bit wide to be directly addressable.
    * When executing a vector instruction which produces a mask (e.g. vector compare), this can be result in a mask
    * where only the 2 or 4 lowest bit are set.
    * E.g.:
    * @code{.cpp}
    *   // Comparator_t is cmplt
    *   __mmask8 m1 = _mm256_cmplt_epi64_mask( a, b );
    *   __mmask8 m2 = _mm256_cmplt_epi64_mask( c, d );
    *   *( result++ ) = m1; *( result++ ) = m2;
    *   // result[-2] = 0b0000 1101
    *   // result[-1] = 0b0000 0101
    * @endcode
    * While it is possible to materialize the resulting mask, this should be avoided to reduce the the overall store-ops.
    * One way to to this is by merging to resulting masks into just one.
    * E.g.:
    * @code{.cpp}
    *   __mmask8 m = ( _mm256_cmplt_epi64_mask( a, b ) | ( _mm256_cmplt_epi64_mask( c, d ) << 4 ) );
    *   *( result ++ ) = m;
    *   // result[-1] = 0b0101 1101
    * @endcode
    * @tparam VectorExtension_t Struct representing used vector extension (e.g. sse< uint32_t >, avx< uint64_t >, ... ).
    * @tparam Comparator_t Struct representing specific comparator.
    */
   struct sequential_filter_mask_helper {
      /**
       * @brief Base type which was specified along the vector extension.
       */
      using T = typename VectorExtension_t::base_t;
      /**
       * @brief Number of masks resulting from the comparator which have to be merged merged.
       * @verbatim
       * |====================|===========|=================|==========|=============================|
       * |--vector extension--|--base_t---|--element count--|--mask_t--|--values per complete mask-- |
       * |--------------------|-----------|-----------------|----------|-----------------------------|
       * |         sse        |  uint8_t  |        16       | _mmask16 |             1               |
       * |         sse        |  uint16_t |        8        | _mmask8  |             1               |
       * |         sse        |  uint32_t |        4        | _mmask8  |             2               |
       * |         sse        |  uint64_t |        2        | _mmask8  |             4               |
       * |        avx2        |  uint8_t  |        32       | _mmask32 |             1               |
       * |        avx2        |  uint16_t |        16       | _mmask16 |             1               |
       * |        avx2        |  uint32_t |        8        | _mmask8  |             1               |
       * |        avx2        |  uint64_t |        4        | _mmask8  |             2               |
       * |       avx512       |  uint8_t  |        64       | _mmask64 |             1               |
       * |       avx512       |  uint16_t |        32       | _mmask32 |             1               |
       * |       avx512       |  uint32_t |        16       | _mmask16 |             1               |
       * |       avx512       |  uint64_t |        8        | _mmask8  |             1               |
       * |====================|===========|=================|==========|=============================|
       * @endverbatim
       * @code{.cpp}
       *    values_per_complete_mask_t = ( sizeof( typename VectorExtension::mask_t ) * 8 ) / vector_element_count_t::value;
       * @endcode
       */
      using values_per_complete_mask_t = typename vector_constants_t< VectorExtension_t >::number_of_vectors_per_mask_t;

      /**
       * @brief Loads a single vector register, applies the specified comparator with all arguments and return the result.
       * This function is intended to be used for the remaining part of an input column.
       * The given input_ptr is incremented by the number of elements which fit into a vector register.
       * @tparam Args Types of variadic arguments predicates.
       * @param input_ptr Reference of pointer to the data which should be processed.
       * @param predicates Variadic arguments which should be used by the comparator.
       * @return A mask containing the result from the comparator.
       */
      template< typename... Args >
      FORCE_INLINE
      static
      typename VectorExtension_t::mask_t
      apply_single(
         T *& input_ptr,
         Args&&... predicates
      ) {
         typename VectorExtension_t::vector_t tmp = load< VectorExtension_t >( input_ptr );
         input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
         return Comparator_t< VectorExtension_t >::apply( tmp, std::forward< Args >( predicates )... );
      }

      /**
       * @brief Specialization when 1 vector register form a complete mask.
       * The given input_ptr is incremented by the number of elements which fit into a vector register.
       * @tparam VpCM values_per_complete_mask_t.
       * @tparam Args Types of variadic arguments predicates.
       * @param input_ptr Reference of pointer to the data which should be processed.
       * @param predicates Variadic arguments which should be used by the comparator.
       * @return A mask containing the result from the comparator.
       */
      template<
         std::size_t VpCM = values_per_complete_mask_t::value,
         typename std::enable_if< VpCM == 1, std::nullptr_t >::type = nullptr,
         typename... Args
      >
      FORCE_INLINE
      static
      typename VectorExtension_t::mask_t
      apply(
         T *& input_ptr,
         Args&&... predicates
      ) {
         typename VectorExtension_t::vector_t tmp = load< VectorExtension_t >( input_ptr );
         input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
         return Comparator_t< VectorExtension_t >::apply( tmp, std::forward< Args >( predicates )... );
      }

      /**
       * @brief Specialization when 2 vector register form a complete mask.
       * The given input_ptr is incremented by two times the number of elements which fit into a vector register.
       * The result is calculated from two vector compares which are merged together.
       * @code{.cpp}
       *    typename VectorExtension_t::vector_t first = load< VectorExtension_t >( input_ptr );
       *    input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
       *    typename VectorExtension_t::vector_t second = load< VectorExtension_t >( input_ptr );
       *    input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
       *    typename VectorExtension_t::mask_t m1 =
       *        Comparator_t< VectorExtension_t >::apply( first, std::forward< Args >( predicates )... );
       *    typename VectorExtension_t::mask_t m2 =
       *        Comparator_t< VectorExtension_t >::apply( second, std::forward< Args >( predicates )... );
       *    return ( m1 | ( m2 << 4 ) );
       * @endcode
       * @tparam VpCM values_per_complete_mask_t.
       * @tparam Args Types of variadic arguments predicates.
       * @param input_ptr Reference of pointer to the data which should be processed.
       * @param predicates Variadic arguments which should be used by the comparator.
       * @return A mask containing the result from the comparator.
       */
      template<
         std::size_t VpCM = values_per_complete_mask_t::value,
         typename std::enable_if< VpCM == 2, std::nullptr_t >::type = nullptr,
         typename... Args
      >
      FORCE_INLINE
      static
      typename VectorExtension_t::mask_t
      apply(
         T *& input_ptr,
         Args&&... predicates
      ) {
         typename VectorExtension_t::vector_t first = load< VectorExtension_t >( input_ptr );
         input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
         typename VectorExtension_t::vector_t second = load< VectorExtension_t >( input_ptr );
         input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
         return
            (
               Comparator_t< VectorExtension_t >::apply( first, std::forward< Args >( predicates )... )
               |
                  (
                     Comparator_t< VectorExtension_t >::apply( second, std::forward< Args >( predicates )... ) <<
                     vector_constants_t< VectorExtension_t >::shift_per_mask_t::value
                  )
            );
      }

      /**
       * @brief Specialization when 4 vector register form a complete mask.
       * The given input_ptr is incremented by four times the number of elements which fit into a vector register.
       * The result is calculated from two vector compares which are merged together.
       * @code{.cpp}
       *    typename VectorExtension_t::vector_t first = load< VectorExtension_t >( input_ptr );
       *    input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
       *    typename VectorExtension_t::vector_t second = load< VectorExtension_t >( input_ptr );
       *    input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
       *    typename VectorExtension_t::vector_t third = load< VectorExtension_t >( input_ptr );
       *    input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
       *    typename VectorExtension_t::vector_t fourth = load< VectorExtension_t >( input_ptr );
       *    input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
       *    typename VectorExtension_t::mask_t m1 =
       *        Comparator_t< VectorExtension_t >::apply( first, std::forward< Args >( predicates )... );
       *    typename VectorExtension_t::mask_t m2 =
       *        Comparator_t< VectorExtension_t >::apply( second, std::forward< Args >( predicates )... );
       *    typename VectorExtension_t::mask_t m3 =
       *        Comparator_t< VectorExtension_t >::apply( third, std::forward< Args >( predicates )... );
       *    typename VectorExtension_t::mask_t m4 =
       *        Comparator_t< VectorExtension_t >::apply( fourth, std::forward< Args >( predicates )... );
       *    return ( m1 | ( m2 << 2 ) | ( m3 << 4 ) | ( m4 << 6 ) );
       * @endcode
       * @tparam VpCM values_per_complete_mask_t.
       * @tparam Args Types of variadic arguments predicates.
       * @param input_ptr Reference of pointer to the data which should be processed.
       * @param predicates Variadic arguments which should be used by the comparator.
       * @return A mask containing the result from the comparator.
       */
      template<
         std::size_t VpCM = values_per_complete_mask_t::value,
         typename std::enable_if< VpCM == 4, std::nullptr_t >::type = nullptr,
         typename... Args
      >
      FORCE_INLINE
      static
      typename VectorExtension_t::mask_t
      apply(
         T *& input_ptr,
         Args&&... predicates
      ) {
         typename VectorExtension_t::vector_t first = load< VectorExtension_t >( input_ptr );
         input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
         typename VectorExtension_t::vector_t second = load< VectorExtension_t >( input_ptr );
         input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
         typename VectorExtension_t::vector_t third = load< VectorExtension_t >( input_ptr );
         input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
         typename VectorExtension_t::vector_t fourth = load< VectorExtension_t >( input_ptr );
         input_ptr += vector_constants_t< VectorExtension_t >::vector_element_count_t::value;
         return
            (
               Comparator_t< VectorExtension_t >::apply( first, std::forward< Args >( predicates )... )
               |
                  (
                     Comparator_t< VectorExtension_t >::apply( second, std::forward< Args >( predicates )... ) <<
                     vector_constants_t< VectorExtension_t >::shift_per_mask_t::value
                  )
               |
                  (
                     Comparator_t< VectorExtension_t >::apply( third, std::forward< Args >( predicates )... ) <<
                     ( vector_constants_t< VectorExtension_t >::shift_per_mask_t::value * 2 )
                  )
               |
                  (
                     Comparator_t< VectorExtension_t >::apply( fourth, std::forward< Args >( predicates )... ) <<
                     ( vector_constants_t< VectorExtension_t >::shift_per_mask_t::value * 3 )
                  )
            );
      }
   };

   /**
    * @brief Class for executing a sequential (SISQ) filter.
    * @tparam VectorExtension_t Struct representing used vector extension (e.g. sse< uint32_t >, avx< uint64_t >, ... ).
    * @tparam Comparator_t Struct representing specific comparator.
    */
   template<
      class VectorExtension_t,
      template< class > class Comparator_t
   >
   struct sequential_filter_impl {
      /**
       * @brief Base type which was specified along the vector extension.
       */
      using T = typename VectorExtension_t::base_t;
      /**
       * @brief Number of elements which fit into the specified vector extension (VectorExtension_t).
       */
      using incrementor_t = typename vector_constants_t< VectorExtension_t >::vector_element_count_t;
      /**
       * @brief Number of masks resulting from the comparator which have to be merged merged.
       * @verbatim
       * |====================|===========|=================|==========|=============================|
       * |--vector extension--|--base_t---|--element count--|--mask_t--|--values per complete mask-- |
       * |--------------------|-----------|-----------------|----------|-----------------------------|
       * |         sse        |  uint8_t  |        16       | _mmask16 |             1               |
       * |         sse        |  uint16_t |        8        | _mmask8  |             1               |
       * |         sse        |  uint32_t |        4        | _mmask8  |             2               |
       * |         sse        |  uint64_t |        2        | _mmask8  |             4               |
       * |        avx2        |  uint8_t  |        32       | _mmask32 |             1               |
       * |        avx2        |  uint16_t |        16       | _mmask16 |             1               |
       * |        avx2        |  uint32_t |        8        | _mmask8  |             1               |
       * |        avx2        |  uint64_t |        4        | _mmask8  |             2               |
       * |       avx512       |  uint8_t  |        64       | _mmask64 |             1               |
       * |       avx512       |  uint16_t |        32       | _mmask32 |             1               |
       * |       avx512       |  uint32_t |        16       | _mmask16 |             1               |
       * |       avx512       |  uint64_t |        8        | _mmask8  |             1               |
       * |====================|===========|=================|==========|=============================|
       * @endverbatim
       * @code{.cpp}
       *    values_per_complete_mask_t = ( sizeof( typename VectorExtension::mask_t ) * 8 ) / vector_element_count_t::value;
       * @endcode
       */
      using values_per_complete_mask_t = typename vector_constants_t< VectorExtension_t >::number_of_vectors_per_mask_t;
      /**
       * @brief Number of elements which are processed to form a complete mask (values_per_complete_mask_t::value * incrementor_t::value).
       */
      using step_width_t =
         std::integral_constant< std::size_t, values_per_complete_mask_t::value * incrementor_t::value >;

      /**
       * @brief Sequential (SISQ) filter operator which operates on a whole column.
       *
       * Iterates over the given input column, transfers the values into a vector register (using the helper struct)
       * and applies the specified comparator. The resulting bitmask is stored in the result column.
       * A 1-bit in the bitmask indicates, that the corresponding element satisfied the predicate.
       * E.g.:
       * @code{.cpp}
       *    auto tmp = result_bitmask_column->data_ptr[ 0 ];
       *    if( ( ( tmp >> 2 ) & ( 0b1 ) ) == 1 ) ) {
       *        // input_column->data_ptr[ 2 ] satisfied the predicate
       *    }
       * @endcode
       * @tparam Args Types of variadic arguments of predicates.
       * @param result_bitmask_column Pointer to a column which will be used for the materialization of the result.
       * @param input_column Pointer to a column which should be processed with a FILTER.
       * @param predicates Variadic arguments which should be used by the comparator.
       * @return Pointer to the result column.
       */
      template< typename... Args >
      static
      column< T > *
      apply(
         column< T > * const result_bitmask_column,
         column< T > * const input_column,
         Args&& ... predicates
      ) {
         std::size_t const element_count = input_column->data_count;

         typename VectorExtension_t::mask_t * result_mask_buffer =
            ( typename VectorExtension_t::mask_t * ) result_bitmask_column->data_ptr;
         T * input_ptr = input_column->data_ptr;
         std::size_t const fully_vectorized_count = element_count / step_width_t::value;
         std::size_t const remainder_count = element_count & ( step_width_t::value - 1 );
         for( std::size_t pos = 0; pos < fully_vectorized_count; ++pos ) {
            *( result_mask_buffer++ ) =
               sequential_filter_mask_helper<
                  VectorExtension_t,
                  Comparator_t
               >::apply(
                  input_ptr,
                  std::forward< Args >( predicates )...
               );
         }

         if( remainder_count != 0 ) {
            std::size_t current_shift = 0;
            typename VectorExtension_t::mask_t result_mask = 0;
            for( std::size_t i = 0; i < remainder_count; i += incrementor_t::value ) {
               result_mask |=
                  (
                     sequential_filter_mask_helper<
                        VectorExtension_t,
                        Comparator_t
                     >::apply_single( input_ptr, std::forward< Args >( predicates )... ) <<
                     ( vector_constants_t< VectorExtension_t >::shift_per_mask_t::value * current_shift )
                  );
               ++current_shift;
               if( current_shift == values_per_complete_mask_t::value ) {
                  current_shift = 0;
                  *( result_mask_buffer++ ) = result_mask;
                  result_mask = 0;
               }
            }
         }
         return result_bitmask_column;
      }

      /**
       * @brief Sequential (SISQ) filter operator which operates on a pointer.
       *
       * Iterates over the given input data, transfers the values into a vector register (using the helper struct)
       * and applies the specified comparator. The resulting bitmask is stored in the result pointer.
       * A 1-bit in the bitmask indicates, that the corresponding element satisfied the predicate.
       * E.g.:
       * @code{.cpp}
       *    auto tmp = input_column[ 0 ];
       *    if( ( ( tmp >> 2 ) & ( 0b1 ) ) == 1 ) ) {
       *        // input_column[ 2 ] satisfied the predicate
       *    }
       * @endcode
       * @tparam Args Types of variadic arguments of predicates.
       * @param result_bitmask_column_ptr Pointer to a buffer which will be used for the materialization of the result.
       * @param input_column Pointer to a buffer which should be processed with a FILTER.
       * @param element_count Number of elements which should be processed.
       * @param predicates Variadic arguments which should be used by the comparator.
       * @return Pointer to the end of the result buffer.
       */
      template< typename... Args >
      static
      typename VectorExtension_t::mask_t *
      apply(
         typename VectorExtension_t::mask_t * const result_bitmask_column_ptr,
         T *& input_column,
         std::size_t const element_count,
         Args&& ... predicates
      ) {

         typename VectorExtension_t::mask_t * result_mask_buffer = result_bitmask_column_ptr;
         std::size_t const fully_vectorized_count = element_count / step_width_t::value;
         std::size_t const remainder_count = element_count & ( step_width_t::value - 1 );
         for( std::size_t pos = 0; pos < fully_vectorized_count; ++pos ) {
            *( result_mask_buffer++ ) =
               sequential_filter_mask_helper<
                  VectorExtension_t,
                  Comparator_t
               >::apply(
                  input_column,
                  std::forward< Args >( predicates )...
               );
         }

         if( remainder_count != 0 ) {
            std::size_t current_shift = 0;
            typename VectorExtension_t::mask_t result_mask = 0;
            for( std::size_t i = 0; i < remainder_count; i += incrementor_t::value ) {
               result_mask |=
                  (
                     sequential_filter_mask_helper<
                        VectorExtension_t,
                        Comparator_t
                     >::apply_single( input_column, std::forward< Args >( predicates )... ) <<
                                      ( vector_constants_t< VectorExtension_t >::shift_per_mask_t::value * current_shift )
                  );
               ++current_shift;
               if( current_shift == values_per_complete_mask_t::value ) {
                  current_shift = 0;
                  *( result_mask_buffer++ ) = result_mask;
                  result_mask = 0;
               }
            }
         }
         return result_mask_buffer;
      }
   };
}

#endif //TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_BITMASK_CANDIDATES_SEQUENTIAL_FILTER_BITMASK_CANDIDATES_H
