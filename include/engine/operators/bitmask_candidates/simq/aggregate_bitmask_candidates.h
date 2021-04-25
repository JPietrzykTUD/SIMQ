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
 * @brief This file contains the SIMQ aggregate operator.
 */
#ifndef TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_BITMASK_CANDIDATES_SIMQ_AGGREGATE_BITMASK_CANDIDATES_H
#define TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_BITMASK_CANDIDATES_SIMQ_AGGREGATE_BITMASK_CANDIDATES_H

#include <cstddef>
#include <stdexcept>

#include <simd/intrin.h>
#include <utils/preprocessor.h>
#include <data/column.h>

#include <simq/control/bitmask/complex_bitmask.h>

namespace tuddbs {

   /**
    * @brief Helper class for reading a mask.
    *
    * Vector registers may contain less than 8 elements (sse with 32-bit (and 64-bit) vluase, avx2 with 64-bit values.
    * A mask has to be at least 8-bit wide to be directly addressable (cf. filter_bitmask_candidates.h).
    * Consequently, when reading a mask it is possible that one mask represents the results from multiple vector registers.
    * The purpose of this helper class is to unroll the de-referencing and shifting of given masks and forward a proper
    * mask along the input to the aggregator.
    * The aggregator should perform some "running" calculation like COUNT or SUM.
    * @tparam VectorExtension_t Used vector extension (e.g. sse< uint32_t >, avx< uint64_t >, ... ).
    * @tparam VectorBuilder_t Vector Builder Struct (to get values from a SIMQ context).
    * @tparam Aggregator_t Struct representing a specific aggregator.
    */
   template<
      class VectorExtension_t,
      class VectorBuilder_t,
      template< class > class Aggregator_t
   >
   struct aggregate_mask_helper {
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
       * @brief Loads a single vector register which should to be aggregated and applies the specified aggregator with a given mask and returns the result.
       *
       * This method is intended to be used for the remaining part of an input column.
       * The given reference to the input builder is internally incremented.
       * @tparam Args Types of variadic arguments predicates.
       * @param input_vector_builder Reference to the vector builder, managing the data which should be processed.
       * @param old_values_vec Result from a previous call.
       * @param active_lanes_mask Mask representing valid elements.
       * @return A vector register containing the new results from the aggregator.
       */
      FORCE_INLINE
      static
      typename VectorExtension_t::vector_t
      apply_single(
         VectorBuilder_t & input_vector_builder,
         typename VectorExtension_t::vector_t const old_values_vec,
         typename VectorExtension_t::mask_t const active_lanes_mask
      ) {
         return
            Aggregator_t< VectorExtension_t >::apply(
               input_vector_builder.get_and_increment(),
               old_values_vec,
               active_lanes_mask
            );
      }

      /**
       * @brief Specialization when 1 vector register form a complete mask.
       *
       * The given reference to the input builder is internally incremented.
       * @tparam VpCM values_per_complete_mask_t.
       * @param input_vector_builder Reference to the vector builder, managing the data which should be processed.
       * @param old_values_vec Result from a previous call.
       * @param active_lanes_mask Mask representing valid elements.
       * @return A vector register containing the new results from the aggregator.
       */
      template<
         std::size_t VpCM = values_per_complete_mask_t::value,
         typename std::enable_if< VpCM == 1, std::nullptr_t >::type = nullptr
      >
      FORCE_INLINE
      static
      typename VectorExtension_t::vector_t
      apply(
         VectorBuilder_t & input_vector_builder,
         typename VectorExtension_t::vector_t const old_values_vec,
         typename VectorExtension_t::mask_t const active_lanes_mask
      ) {
         return
            Aggregator_t< VectorExtension_t >::apply(
               input_vector_builder.get_and_increment(),
               old_values_vec,
               active_lanes_mask
            );
      }

      /**
       * @brief Specialization when 2 vector register form a complete mask.
       *
       * The given reference to the input builder is internally incremented.
       * The result is calculated from two vector registers using the aggregator and the mask.
       * @code{.cpp}
       *    typename VectorExtension_t::vector_t first = input_vector_builder.get_and_increment();
       *    typename VectorExtension_t::vector_t second = input_vector_builder.get_and_increment();
       *    old_values_vec = Aggregator_t< VectorExtension_t >::apply( first, old_values_vec, active_lanes_mask );
       *    return Aggregator_t< VectorExtension_t >::apply( second, old_values_vec, ( active_lanes_mask >> 4 ) );
       * @endcode
       * @tparam VpCM values_per_complete_mask_t.
       *  @param input_vector_builder Reference to the vector builder, managing the data which should be processed.
       * @param old_values_vec Result from a previous call.
       * @param active_lanes_mask Mask representing valid elements.
       * @return A vector register containing the new results from the aggregator.
       */
      template<
         std::size_t VpCM = values_per_complete_mask_t::value,
         typename std::enable_if< VpCM == 2, std::nullptr_t >::type = nullptr
      >
      FORCE_INLINE
      static
      typename VectorExtension_t::vector_t
      apply(
         VectorBuilder_t & input_vector_builder,
         typename VectorExtension_t::vector_t const old_values_vec,
         typename VectorExtension_t::mask_t const active_lanes_mask
      ) {
         typename VectorExtension_t::vector_t first = input_vector_builder.get_and_increment();
         typename VectorExtension_t::vector_t second = input_vector_builder.get_and_increment();
         return
            Aggregator_t< VectorExtension_t >::apply(
               second,
               Aggregator_t< VectorExtension_t >::apply(
                  first,
                  old_values_vec,
                  active_lanes_mask
               ),
              ( active_lanes_mask >> vector_constants_t< VectorExtension_t >::shift_per_mask_t::value )
            );
      }

      /**
       * @brief Specialization when 4 vector register form a complete mask.
       *
       * The given reference to the input builder is internally incremented.
       * The result is calculated from two vector registers using the aggregator and the mask.
       * @code{.cpp}
       *    typename VectorExtension_t::vector_t first = input_vector_builder.get_and_increment();
       *    typename VectorExtension_t::vector_t second = input_vector_builder.get_and_increment();
       *    typename VectorExtension_t::vector_t third = input_vector_builder.get_and_increment();
       *    typename VectorExtension_t::vector_t fourth = input_vector_builder.get_and_increment();
       *    old_values_vec = Aggregator_t< VectorExtension_t >::apply( first, old_values_vec, active_lanes_mask );
       *    old_values_vec = Aggregator_t< VectorExtension_t >::apply( second, old_values_vec, ( active_lanes_mask >> 2 ) );
       *    old_values_vec = Aggregator_t< VectorExtension_t >::apply( third, old_values_vec, ( active_lanes_mask >> 4 ) );
       *    return Aggregator_t< VectorExtension_t >::apply( fourth, old_values_vec, ( active_lanes_mask >> 6 ) );
       * @endcode
       * @tparam VpCM values_per_complete_mask_t.
       *  @param input_vector_builder Reference to the vector builder, managing the data which should be processed.
       * @param old_values_vec Result from a previous call.
       * @param active_lanes_mask Mask representing valid elements.
       * @return A vector register containing the new results from the aggregator.
       */
      template<
         std::size_t VpCM = values_per_complete_mask_t::value,
         typename std::enable_if< VpCM == 4, std::nullptr_t >::type = nullptr
      >
      FORCE_INLINE
      static
      typename VectorExtension_t::vector_t
      apply(
         VectorBuilder_t & input_vector_builder,
         typename VectorExtension_t::vector_t const old_values_vec,
         typename VectorExtension_t::mask_t const active_lanes_mask
      ) {
         typename VectorExtension_t::vector_t first = input_vector_builder.get_and_increment();
         typename VectorExtension_t::vector_t second = input_vector_builder.get_and_increment();
         typename VectorExtension_t::vector_t third = input_vector_builder.get_and_increment();
         typename VectorExtension_t::vector_t fourth = input_vector_builder.get_and_increment();
         return
            Aggregator_t< VectorExtension_t >::apply(
               fourth,
               Aggregator_t< VectorExtension_t >::apply(
                  third,
                  Aggregator_t< VectorExtension_t >::apply(
                     second,
                     Aggregator_t< VectorExtension_t >::apply(
                        first,
                        old_values_vec,
                        active_lanes_mask
                     ),
                     ( active_lanes_mask >> vector_constants_t< VectorExtension_t >::shift_per_mask_t::value )
                  ),
                  ( active_lanes_mask >> ( vector_constants_t< VectorExtension_t >::shift_per_mask_t::value * 2 ) )
               ),
               ( active_lanes_mask >> ( vector_constants_t< VectorExtension_t >::shift_per_mask_t::value * 3 ) )
            );
      }
   };

   /**
    * @brief Class for executing a SIMQ-compliant aggregate.
    * @tparam VectorExtension_t Struct representing used vector extension (e.g. sse< uint32_t >, avx< uint64_t >, ... ).
    * @tparam VectorBuilder_t Vector Builder Struct (to get values from a SIMQ context).
    * @tparam Aggregator_t Struct which is used to aggregate.
    */
   template<
      class VectorExtension_t,
      class VectorBuilder_t,
      template< class > class Aggregator_t,
      std::size_t NumberOfBits = 0,
      std::size_t BitPositionOffset = 0
   >
   struct aggregate_impl {
      /**
       * @brief Base type which was specified along the vector extension.
       */
      using T = typename VectorExtension_t::base_t;
      /**
       * @brief Number of elements which fit into the specified vector extension (VectorExtension_t).
       */
      using incrementor_t = std::integral_constant< std::size_t, VectorBuilder_t::get_incrementor() >;
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
      static_assert( ( ( step_width_t::value & ( step_width_t::value - 1 ) ) == 0 ), "Stepwidth should be 2^x." );

      /**
       * @brief SIMQ-compliant aggregate operator which operates on a whole column.
       *
       * Iterates over the given input column, derefences the current mask, and forwards the mask and the data pointer
       * to the specified aggregator. The result is transferred to the given result column. The result column is returned.
       * @param result_column Pointer to a column which will be used for the materialization of the result.
       * @param input_vector_builder Reference to the vector builder, managing the data which should be processed.
       * @param input_bitmask_column Pointer to a column which holds the corresponding bitmask, where a 1-bit denotes a valid entry.
       * @return Pointer to the result column.
       */
      static
      column< T > *
      apply(
         column< T > * const result_column,
         VectorBuilder_t & input_vector_builder,
         column< T > * const input_bitmask_column
      ) {
         std::size_t const element_count = input_vector_builder.svw.element_count;

         typename VectorExtension_t::mask_t * input_bitmask_buffer_ptr =
            ( typename VectorExtension_t::mask_t * ) input_bitmask_column->data_ptr;
         typename VectorExtension_t::vector_t result_vec = Aggregator_t< VectorExtension_t >::init();
         std::size_t const fully_vectorized_count = element_count / step_width_t::value;
         std::size_t const remainder_count = element_count & ( step_width_t::value - 1 );
         typename VectorExtension_t::mask_t mask = 0;
         for( std::size_t pos = 0; pos < fully_vectorized_count; ++pos ) {
            if constexpr( NumberOfBits != 0 ) {
               std::tie( mask, input_bitmask_buffer_ptr ) =
                  complex_bitmask_helper_t< VectorExtension_t, NumberOfBits, BitPositionOffset >::read_mask_and_increment( input_bitmask_buffer_ptr );
            } else {
               mask = *( input_bitmask_buffer_ptr++ );
            }
            result_vec =
               aggregate_mask_helper<
                  VectorExtension_t,
                  VectorBuilder_t,
                  Aggregator_t
               >::apply(
                  input_vector_builder,
                  result_vec,
                  mask
               );
         }

         if( remainder_count != 0 ) {
            throw std::runtime_error("Remainder!!!");
            std::size_t current_shift = 0;
            typename VectorExtension_t::mask_t remainder_mask = *( input_bitmask_buffer_ptr++ );
            for( std::size_t i = 0; i < remainder_count; i += incrementor_t::value ) {
               result_vec =
                  aggregate_mask_helper<
                     VectorExtension_t,
                     VectorBuilder_t,
                     Aggregator_t
                  >::apply_single(
                     input_vector_builder,
                     result_vec,
                     remainder_mask >> ( vector_constants_t< VectorExtension_t >::shift_per_mask_t::value * current_shift )
                  );
               ++current_shift;
               if( current_shift == values_per_complete_mask_t::value ) {
                  current_shift = 0;
                  remainder_mask = *( input_bitmask_buffer_ptr++ );
               }
            }
         }

         typename VectorExtension_t::vector_t reduced_result_vec =
            Aggregator_t< VectorExtension_t >::template inner_finalize< VectorBuilder_t::lanes_per_query_t::value >(
               result_vec
            );
//         typename VectorExtension_t::vector_t reduced_result_vec =
//            reduce_add< VectorExtension_t, VectorBuilder_t::lanes_per_query_t::value >( result_vec );
         [[maybe_unused]]typename VectorExtension_t::base_t * tmp = store< VectorExtension_t >( result_column->data_ptr, reduced_result_vec );
         return result_column;
      }


      /**
       * @brief SIMQ-compliant aggregate operator which operates on a pointer.
       *
       * Iterates over the given input data buffer, derefences the current mask, and forwards the mask and the data pointer
       * to the specified aggregator. The result is transferred to the given result column. The result column is returned.
       * @param result_column Pointer to a buffer which will be used for the materialization of the result (this column may contain the results from a previous call).
       * @param input_vector_builder Reference to the vector builder, managing the data which should be processed.
       * @param input_bitmask_column Pointer to a buffer which holds the corresponding bitmask, where a 1-bit denotes a valid entry.
       * @return Pointer to the result column.
       */
      static
      T *
      apply(
         T * const result_column,
         VectorBuilder_t & input_vector_builder,
         std::size_t const element_count,
         typename VectorExtension_t::mask_t * const input_bitmask_column_ptr
      ) {

         typename VectorExtension_t::mask_t * input_bitmask_buffer_ptr = input_bitmask_column_ptr;
         typename VectorExtension_t::vector_t result_vec = load< VectorExtension_t >( result_column );
         std::size_t const fully_vectorized_count = element_count / step_width_t::value;
         std::size_t const remainder_count = element_count & ( step_width_t::value - 1 );
         typename VectorExtension_t::mask_t mask = 0;
         for( std::size_t pos = 0; pos < fully_vectorized_count; ++pos ) {
            if constexpr( NumberOfBits != 0 ) {
               std::tie( mask, input_bitmask_buffer_ptr ) =
                  complex_bitmask_helper_t< VectorExtension_t, NumberOfBits, BitPositionOffset >::read_mask_and_increment( input_bitmask_buffer_ptr );
            } else {
               mask = *( input_bitmask_buffer_ptr++ );
            }
            result_vec =
               aggregate_mask_helper<
                  VectorExtension_t,
                  VectorBuilder_t,
                  Aggregator_t
               >::apply(
                  input_vector_builder,
                  result_vec,
                  mask
               );
         }

         if( remainder_count != 0 ) {
            throw std::runtime_error("Remainder!!!");
            std::size_t current_shift = 0;
            typename VectorExtension_t::mask_t remainder_mask = *( input_bitmask_buffer_ptr++ );
            for( std::size_t i = 0; i < remainder_count; i += incrementor_t::value ) {
               result_vec =
                  aggregate_mask_helper<
                     VectorExtension_t,
                     VectorBuilder_t,
                     Aggregator_t
                  >::apply_single(
                     input_vector_builder,
                     result_vec,
                     remainder_mask >> ( vector_constants_t< VectorExtension_t >::shift_per_mask_t::value * current_shift )
                  );
               ++current_shift;
               if( current_shift == values_per_complete_mask_t::value ) {
                  current_shift = 0;
                  remainder_mask = *( input_bitmask_buffer_ptr++ );
               }
            }
         }
         typename VectorExtension_t::vector_t reduced_result_vec =
            reduce_add< VectorExtension_t, VectorBuilder_t::lanes_per_query_t::value >( result_vec );
         [[maybe_unused]]typename VectorExtension_t::base_t * tmp = store< VectorExtension_t >( result_column, reduced_result_vec );
         return result_column;
      }
   };
}

#endif //TUDDBS_SIMQ_INCLUDE_ENGINE_OPERATORS_BITMASK_CANDIDATES_SIMQ_AGGREGATE_BITMASK_CANDIDATES_H
