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
 * @brief This file contains structs for organizing multiple columns in a fixed sized array.
 */
#ifndef TUDDBS_SIMQ_INCLUDE_DATA_CONTAINER_COLUMN_ARRAY_H
#define TUDDBS_SIMQ_INCLUDE_DATA_CONTAINER_COLUMN_ARRAY_H

#include <data/column.h>
#include <simd/intrin.h>

#include <utility>
#include <algorithm>
#include <type_traits>
#include <cstddef>

namespace tuddbs {
   
   template< class VectorExtension, std::size_t NumberOfColumns >
   /**
    * @brief Container class for organizing multiple columns.
    *
    * For SIMQ, multiple columns have to be managed as a workload input.
    * The column_array holds all associated columns in a fixed sized array.
    * The columns are not ordered in any way. The maximum number of columns is determined by the number of
    * elements which fit into the specified vector extension.
    * Furthermore, the number of columns must be equal to 2^x.
    * @tparam VectorExtension Used vector extension (e.g. sse< uint8_t >, avx2< uint16_t >, avx512< uint32_t >).
    * @tparam NumberOfColumns Number of columns.
    */
   struct column_array {
      using T = typename VectorExtension::base_t;
      using number_or_columns_t = std::integral_constant< std::size_t, NumberOfColumns >;
      using vector_extension_t = VectorExtension;
      static_assert( NumberOfColumns
      <= vector_constants_t< VectorExtension >::vector_element_count_t::value,
      "To many columns specified.");
      column <T> * columns[NumberOfColumns];
      
      template< class... Args >
      column_array( Args && ... args ):
         columns{ std::forward< Args >( args )... } { }
      
      void assign(
         std::initializer_list< column < typename VectorExtension::base_t > *
      
      > list ) {
         std::copy( list.begin( ), list.end( ), columns );
      }
      
      void set( std::size_t idx, void * a ) {
         columns[ idx ] = ( column <T> * ) a;
      }
      
      T * get_min_address( void ) const {
         return ( *( std::min_element( columns, &columns[ NumberOfColumns ] ) ) )->data_ptr;
      }
      
      T * get_max_address( void ) const {
         return ( *( std::max_element( columns, &columns[ NumberOfColumns ] ) ) )->data_ptr;
      }
      
      T * get_max_end_address( void ) const {
         column <T> * max = ( *( std::max_element( columns, &columns[ NumberOfColumns ] ) ) );
         return ( max->data_ptr + max->data_count );
      }
      
      void delete_columns( void ) {
         for(
            std::size_t i = 0; i < NumberOfColumns; ++i
            ) {
            delete columns[ i ];
         }
      }
      
   };
   
   template< class VectorExtension, std::size_t NumberOfQueries >
   /**
    * @brief Container class for organizing multiple values.
    *
    * For SIMQ, multiple values can be required for a specific workload (e.g. predicates for different SELECT operators).
    * @tparam VectorExtension Used vector extension (e.g. sse< uint8_t >, avx2< uint16_t >, avx512< uint32_t >).
    * @tparam NumberOfQueries Number of columns.
    */
   struct value_array {
      using T = typename VectorExtension::base_t;
      using number_or_queries_t = std::integral_constant< std::size_t, NumberOfQueries >;
      using vector_extension_t = VectorExtension;
      static_assert( NumberOfQueries
      <= vector_constants_t< VectorExtension >::vector_element_count_t::value,
      "To many queries specified.");
      static_assert( ( NumberOfQueries
      & ( NumberOfQueries - 1 ) ) == 0, "Number of queries has to be an exponent of two.");
      T values[NumberOfQueries];
      
      template< class... Args >
      constexpr value_array( Args && ... args ):
         values{ static_cast< T >( std::forward< Args >( args ) )... } { }
      
      void assign( std::initializer_list <T> list ) {
         std::copy( list.begin( ), list.end( ), values );
      }
      
      void set( std::size_t idx, T a ) {
         values[ idx ] = a;
      }
   };
   
}

#endif //TUDDBS_SIMQ_INCLUDE_DATA_CONTAINER_COLUMN_ARRAY_H
