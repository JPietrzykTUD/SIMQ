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

#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_VIEW_IMPL_AVX2_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_VIEW_IMPL_AVX2_H

#include <simd/intrin.h>
#include <data/column.h>
#include <data/container/column_array.h>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace tuddbs {
   template<
      class ColumnContainer,
      std::size_t NumberOfQueries,
      typename DepT
   >
   struct simq_column_vector_view_impl_t< ColumnContainer, NumberOfQueries, DepT, avx2 < DepT > > {
   using VectorExtension = typename ColumnContainer::vector_extension_t;
   using T = typename VectorExtension::base_t;
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 1 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 8;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 9;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 10;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 11;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 12;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 13;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 14;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 15;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 16;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 17;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 18;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 19;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 20;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 21;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 22;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 23;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 24;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 25;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 26;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 27;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 28;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 29;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 30;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 31;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 1 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 32;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 8;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 9;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 10;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 11;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 12;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 13;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 14;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 15;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 8;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 9;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 10;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 11;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 12;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 13;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 14;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 15;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 16;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 8;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 9;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 10;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 11;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 12;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 13;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 14;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 15;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 4;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 5;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 6;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 7;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 8;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 9;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 10;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 11;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 12;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 13;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 14;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 15;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 16;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 8;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 4;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 5;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 6;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 7;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 4;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 5;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 6;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 7;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 8;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 4;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 5;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 6;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 7;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 2;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 3;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 4;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 5;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 6;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 7;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 2;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 3;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 4;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 5;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 6;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 7;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 8;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 2;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 3;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 2;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 3;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 2;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 3;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 2;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 2;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 3;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr + 2;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr + 3;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr + 1;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr + 2;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr + 3;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr + 2;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr + 3;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr + 1;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr + 2;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr + 1;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr + 1;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr + 1;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr + 1;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr + 1;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 16 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr + 1;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr + 1;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 8 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 8 ]->data_ptr + 1;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 9 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 9 ]->data_ptr + 1;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 10 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 10 ]->data_ptr + 1;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 11 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 11 ]->data_ptr + 1;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 12 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 12 ]->data_ptr + 1;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 13 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 13 ]->data_ptr + 1;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 14 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 14 ]->data_ptr + 1;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 15 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 15 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 16 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 16 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 8 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 8 ]->data_ptr;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 9 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 9 ]->data_ptr;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 10 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 10 ]->data_ptr;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 11 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 11 ]->data_ptr;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 12 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 12 ]->data_ptr;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 13 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 13 ]->data_ptr;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 14 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 14 ]->data_ptr;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 15 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 15 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 16 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 32 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint8_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint8_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint8_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint8_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint8_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint8_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint8_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint8_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint8_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint8_t * ) p_container.columns[ 8 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint8_t * ) p_container.columns[ 9 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint8_t * ) p_container.columns[ 10 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint8_t * ) p_container.columns[ 11 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint8_t * ) p_container.columns[ 12 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint8_t * ) p_container.columns[ 13 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint8_t * ) p_container.columns[ 14 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint8_t * ) p_container.columns[ 15 ]->data_ptr;
      column_data_ptr[ 16 ] = ( uint8_t * ) p_container.columns[ 16 ]->data_ptr;
      column_data_ptr[ 17 ] = ( uint8_t * ) p_container.columns[ 17 ]->data_ptr;
      column_data_ptr[ 18 ] = ( uint8_t * ) p_container.columns[ 18 ]->data_ptr;
      column_data_ptr[ 19 ] = ( uint8_t * ) p_container.columns[ 19 ]->data_ptr;
      column_data_ptr[ 20 ] = ( uint8_t * ) p_container.columns[ 20 ]->data_ptr;
      column_data_ptr[ 21 ] = ( uint8_t * ) p_container.columns[ 21 ]->data_ptr;
      column_data_ptr[ 22 ] = ( uint8_t * ) p_container.columns[ 22 ]->data_ptr;
      column_data_ptr[ 23 ] = ( uint8_t * ) p_container.columns[ 23 ]->data_ptr;
      column_data_ptr[ 24 ] = ( uint8_t * ) p_container.columns[ 24 ]->data_ptr;
      column_data_ptr[ 25 ] = ( uint8_t * ) p_container.columns[ 25 ]->data_ptr;
      column_data_ptr[ 26 ] = ( uint8_t * ) p_container.columns[ 26 ]->data_ptr;
      column_data_ptr[ 27 ] = ( uint8_t * ) p_container.columns[ 27 ]->data_ptr;
      column_data_ptr[ 28 ] = ( uint8_t * ) p_container.columns[ 28 ]->data_ptr;
      column_data_ptr[ 29 ] = ( uint8_t * ) p_container.columns[ 29 ]->data_ptr;
      column_data_ptr[ 30 ] = ( uint8_t * ) p_container.columns[ 30 ]->data_ptr;
      column_data_ptr[ 31 ] = ( uint8_t * ) p_container.columns[ 31 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 32 )
            && ( NoC == 32 )
            && ( std::is_same < VecExt, avx2 < uint8_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 1 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 8;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 9;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 10;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 11;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 12;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 13;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 14;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 15;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 1 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 16;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 8;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 4;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 5;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 6;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 7;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 8;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr + 2;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr + 3;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr + 2;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 4 ]->data_ptr + 1;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 5 ]->data_ptr + 1;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 6 ]->data_ptr + 1;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 7 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 7 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 16 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint16_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ]  = ( uint16_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ]  = ( uint16_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 2 ]  = ( uint16_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 3 ]  = ( uint16_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 4 ]  = ( uint16_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 5 ]  = ( uint16_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 6 ]  = ( uint16_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 7 ]  = ( uint16_t * ) p_container.columns[ 7 ]->data_ptr;
      column_data_ptr[ 8 ]  = ( uint16_t * ) p_container.columns[ 8 ]->data_ptr;
      column_data_ptr[ 9 ]  = ( uint16_t * ) p_container.columns[ 9 ]->data_ptr;
      column_data_ptr[ 10 ] = ( uint16_t * ) p_container.columns[ 10 ]->data_ptr;
      column_data_ptr[ 11 ] = ( uint16_t * ) p_container.columns[ 11 ]->data_ptr;
      column_data_ptr[ 12 ] = ( uint16_t * ) p_container.columns[ 12 ]->data_ptr;
      column_data_ptr[ 13 ] = ( uint16_t * ) p_container.columns[ 13 ]->data_ptr;
      column_data_ptr[ 14 ] = ( uint16_t * ) p_container.columns[ 14 ]->data_ptr;
      column_data_ptr[ 15 ] = ( uint16_t * ) p_container.columns[ 15 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 16 )
            && ( NoC == 16 )
            && ( std::is_same < VecExt, avx2 < uint16_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 1 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 4;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 5;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 6;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 7;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 1 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 8;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr + 2;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 2 ]->data_ptr + 1;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 3 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 3 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint32_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint32_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint32_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 2 ] = ( uint32_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint32_t * ) p_container.columns[ 3 ]->data_ptr;
      column_data_ptr[ 4 ] = ( uint32_t * ) p_container.columns[ 4 ]->data_ptr;
      column_data_ptr[ 5 ] = ( uint32_t * ) p_container.columns[ 5 ]->data_ptr;
      column_data_ptr[ 6 ] = ( uint32_t * ) p_container.columns[ 6 ]->data_ptr;
      column_data_ptr[ 7 ] = ( uint32_t * ) p_container.columns[ 7 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 8 )
            && ( NoC == 8 )
            && ( std::is_same < VecExt, avx2 < uint32_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 1 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint64_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr + 2;
      column_data_ptr[ 3 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr + 3;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 1 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 4;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint64_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint64_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr + 1;
      column_data_ptr[ 2 ] = ( uint64_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint64_t * ) p_container.columns[ 1 ]->data_ptr + 1;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 2 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 2;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint64_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 1 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint64_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 2 ] = ( uint64_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint64_t * ) p_container.columns[ 1 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 2 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static void init( ColumnContainer const & p_container, uint64_t ** const column_data_ptr ) {
      column_data_ptr[ 0 ] = ( uint64_t * ) p_container.columns[ 0 ]->data_ptr;
      column_data_ptr[ 1 ] = ( uint64_t * ) p_container.columns[ 1 ]->data_ptr;
      column_data_ptr[ 2 ] = ( uint64_t * ) p_container.columns[ 2 ]->data_ptr;
      column_data_ptr[ 3 ] = ( uint64_t * ) p_container.columns[ 3 ]->data_ptr;
      
   }
   
   template<
      std::size_t NoQ = NumberOfQueries,
      std::size_t NoC = ColumnContainer::number_or_columns_t::value,
      class VecExt = VectorExtension,
      typename std::enable_if<
         (
            ( NoQ == 4 )
            && ( NoC == 4 )
            && ( std::is_same < VecExt, avx2 < uint64_t > > ::value )
         ), std::nullptr_t
      >::type = nullptr
   >
   constexpr static std::size_t
   
   get_incrementor( void ) {
      return 1;
   }
   
};
}
#endif //TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_VIEW_H
      