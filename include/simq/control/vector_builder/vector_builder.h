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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_BUILDER_H
#define TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_BUILDER_H

#include <simd/intrin.h>
#include <utils/preprocessor.h>

#include <simq/control/vector_builder/build_variants/gather.h>

namespace tuddbs {
   
   template<
      template< class, std::size_t, typename, class > class Strategy,
                                                      class ColumnContainer,
      std::size_t NumberOfQueries
   >
   struct simq_vector_builder_t {
      using VectorExtension = typename ColumnContainer::vector_extension_t;
      using T = typename VectorExtension::base_t;
      using NoQ_t = std::integral_constant< std::size_t, NumberOfQueries >;
      using lanes_per_query_t =
      std::integral_constant<
         std::size_t,
         vector_constants_t< VectorExtension >::vector_element_count_t::value / NumberOfQueries
      >;
      
      simq_column_vector_view_t <ColumnContainer, NumberOfQueries> svw;
      
      simq_vector_builder_t( ColumnContainer & column_container ) :
         svw{ column_container } { }
      
      FORCE_INLINE
      static constexpr
      
      std::size_t get_incrementor( void ) {
         return simq_column_vector_view_t< ColumnContainer, NumberOfQueries >::get_incrementor( );
      }
      
      FORCE_INLINE
      typename VectorExtension::vector_t
      
      get_and_increment( void ) {
         return Strategy< ColumnContainer, NumberOfQueries, T, VectorExtension >::get_and_increment( svw );
      }
      
      FORCE_INLINE
      bool
      has_next( void ) {
         return ( svw.column_data_ptr[ 0 ] < svw.column_data_end_ptr );
      }
      
      void reset( void ) {
         svw.reset( );
      }
   };
   
   template<
      class ColumnContainer,
      std::size_t NumberOfQueries
   >
   struct simq_vector_builder_t< simq_vector_builder_gather_t, ColumnContainer, NumberOfQueries > {
      using VectorExtension = typename ColumnContainer::vector_extension_t;
      using T = typename VectorExtension::base_t;
      using NoQ_t = std::integral_constant< std::size_t, NumberOfQueries >;
      using lanes_per_query_t =
      std::integral_constant<
         std::size_t,
         vector_constants_t< VectorExtension >::vector_element_count_t::value / NumberOfQueries
      >;
      
      simq_column_vector_view_t <ColumnContainer, NumberOfQueries> svw;
      
      simq_vector_builder_t( ColumnContainer & column_container ) :
         svw{ column_container } { }
      
      FORCE_INLINE
      static constexpr
      
      std::size_t get_incrementor( void ) {
         return simq_column_vector_view_t< ColumnContainer, NumberOfQueries >::get_incrementor( );
      }
      
      FORCE_INLINE
      typename VectorExtension::vector_t
      
      get_and_increment( void ) {
         return simq_vector_builder_gather_t< ColumnContainer, NumberOfQueries, T, VectorExtension >::get_and_increment(
            svw
         );
      }
      
      FORCE_INLINE
      bool
      has_next( void ) {
         return ( svw.min_address < svw.min_address_end_ptr );
      }
      
      void reset( void ) {
         svw.reset( );
      }
   };
   
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_BUILDER_H
