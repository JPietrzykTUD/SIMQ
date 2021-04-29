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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_VIEW_H
#define TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_VIEW_H

#include <simd/intrin.h>
#include <data/column.h>
#include <data/container/column_array.h>

#include <simq/control/vector_builder/vector_view_impl.h>

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <cassert>
#include <limits>

namespace tuddbs {
   
   template<
      class ColumnContainer,
      std::size_t NumberOfQueries
   >
   struct simq_column_vector_view_t {
      static_assert( ColumnContainer::number_or_columns_t::value
      <= NumberOfQueries,
      "To few columns specified.");
      static_assert( ( NumberOfQueries
      & ( NumberOfQueries - 1 ) ) == 0, "Number of queries has to be an exponent of two.");
      using VectorExtension = typename ColumnContainer::vector_extension_t;
      using T = typename VectorExtension::base_t;
      using vector_lanes_per_column_t =
      std::integral_constant<
         std::size_t,
         vector_constants_t< VectorExtension >::vector_element_count_t::value
         / ColumnContainer::number_or_columns_t::value
      >;
      using step_per_query_t =
      std::integral_constant<
         std::size_t,
         vector_constants_t< VectorExtension >::vector_element_count_t::value / NumberOfQueries
      >;
      T * min_address;
      T * const min_orig_address;
      alignas( vector_constants_t< VectorExtension >::vector_alignment_byte_t::value )
      T * column_data_ptr[vector_constants_t< VectorExtension >::vector_element_count_t::value]      = { nullptr };
      T * column_data_orig_ptr[vector_constants_t< VectorExtension >::vector_element_count_t::value] = { nullptr };
#ifdef INTRIN
      typename VectorExtension::vector_t column_data_ptr_vec;
#endif
      std::size_t element_count;
      T * const column_data_end_ptr;
      T * const min_address_end_ptr;
      
      FORCE_INLINE
      static constexpr
      
      std::size_t get_incrementor( void ) {
         return simq_column_vector_view_impl_t<
            ColumnContainer,
            NumberOfQueries,
            T,
            VectorExtension
         >::get_incrementor( );
      }
      
      simq_column_vector_view_t( ColumnContainer const & p_container ) :
         min_address{ p_container.get_min_address( ) },
         min_orig_address{ min_address },
         column_data_ptr{ },
         column_data_orig_ptr{ },
         element_count{ p_container.columns[ 0 ]->data_count },
         column_data_end_ptr{ p_container.columns[ 0 ]->data_ptr + element_count },
         min_address_end_ptr{ min_address + element_count } {
         simq_column_vector_view_impl_t< ColumnContainer, NumberOfQueries, T, VectorExtension >::init(
            p_container, column_data_ptr
         );
         for(
            std::size_t i = 0; i < vector_constants_t< VectorExtension >::vector_element_count_t::value; ++i
            ) {
            T * tmp = column_data_ptr[ i ];
            column_data_orig_ptr[ i ] = tmp;
#ifdef INTEL_SIMDI
            _mm_prefetch(((char *)(tmp)),_MM_HINT_NTA);
#endif
         }
#ifdef INTRIN
         alignas( vector_constants_t< VectorExtension >::vector_alignment_byte_t::value )
         T column_offset[ vector_constants_t< VectorExtension >::vector_element_count_t::value ];
         for( std::size_t i = 0; i < vector_constants_t< VectorExtension >::vector_element_count_t::value; ++i ) {
            std::size_t offset = column_data_ptr[ i ] - min_address;
//            assert( offset <= std::numeric_limits< T >::max() );
            column_offset[ i ] = ( T ) offset;
         }
         column_data_ptr_vec = load< VectorExtension >( column_offset );
#endif
      }
      
      void reset( ) {
         for(
            std::size_t i = 0; i < vector_constants_t< VectorExtension >::vector_element_count_t::value; ++i
            ) {
            column_data_ptr[ i ] = column_data_orig_ptr[ i ];
            min_address = min_orig_address;
         }
      }
      
      typename VectorExtension::vector_t get_offset_vector_in_byte( void ) const {
         typename vector_constants_t< VectorExtension >::array_t tmp;
         uint64_t const                                          umin_address = ( uint64_t ) min_address;
         T * data = tmp.data( );
         for(
            std::size_t i = 0; i < vector_constants_t< VectorExtension >::vector_element_count_t::value; ++i
            ) {
            data[ i ] = ( uint64_t )( column_data_ptr[ i ] ) - umin_address;
         }
         return load< VectorExtension >( data );
      }
      
      typename VectorExtension::vector_t get_offset_vector( void ) const {
         typename vector_constants_t< VectorExtension >::array_t tmp;
         T * data = tmp.data( );
         for(
            std::size_t i = 0; i < vector_constants_t< VectorExtension >::vector_element_count_t::value; ++i
            ) {
            data[ i ] = ( column_data_ptr[ i ]->data_ptr ) - min_address;
         }
         return load< VectorExtension >( data );
      }
   };
   
   template<
      class ValueContainer,
      std::size_t NumberOfColumns
   >
   struct simq_value_vector_view_t {
      static_assert( NumberOfColumns <= ValueContainer::number_or_queries_t::value,
      "To few columns specified.");
      using VectorExtension = typename ValueContainer::vector_extension_t;
      using T = typename VectorExtension::base_t;
      using vector_lanes_per_query_t =
      std::integral_constant<
         std::size_t,
         vector_constants_t< VectorExtension >::vector_element_count_t::value
         / ValueContainer::number_or_queries_t::value
      >;
      [[nodiscard]] FORCE_INLINE
      static
      typename VectorExtension::vector_t
      apply( ValueContainer const & p_container) {
         alignas( vector_constants_t< VectorExtension >::vector_alignment_byte_t::value )
         T              column_data_ptr[vector_constants_t< VectorExtension >::vector_element_count_t::value];
         //@todo: this can be done better...
         std::size_t    current_column_idx = 0;
         for(
            std::size_t column_idx         = 0;
            column_idx < vector_constants_t< VectorExtension >::vector_element_count_t::value;
            column_idx += vector_lanes_per_query_t::value
            ) {
            std::size_t    query_idx             = 0;
            for(
               std::size_t column_repetition_idx = 0;
               column_repetition_idx < vector_lanes_per_query_t::value;
               ++column_repetition_idx
               ) {
               column_data_ptr[ column_idx + column_repetition_idx ] =
                  p_container.values[ current_column_idx ];
               ++query_idx;
            }
            ++current_column_idx;
         }
         return load< VectorExtension >( column_data_ptr );
      }
      
   };
   
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_VIEW_H
