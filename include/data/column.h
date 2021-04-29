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
 * @brief This file contains structs for organizing data in columns.
 */
#ifndef TUDDBS_SIMQ_INCLUDE_DATA_COLUMN_H
#define TUDDBS_SIMQ_INCLUDE_DATA_COLUMN_H

#include <cstdint>
#include <cstddef>
#include <utility>

#include <simd/intrin.h>
#include <memory/memory.h>
#include <utils/md_preprocessor.h>

namespace tuddbs {
   
   template< typename T >
   /**
    * @brief Helper function to calculate the number of data elements needed to hold one bit for every data element (from data_count).
    * @tparam T Base type.
    * @param data_count Number of data elements of type T.
    * @return Number of data elements which are required for a bitmask.
    */
   constexpr std::size_t
   calculate_datacount_needed_for_bitmask( std::size_t
   data_count ) {
   return ( ( data_count / ( sizeof( T ) * 8 ) ) + ( ( data_count & ( ( sizeof( T ) * 8 ) - 1 ) ) == 0 ? 0 : 1 ) );
}

template< typename T >
/**
 * @brief Fixed sized container class for holding data in a columnar layout.
 * @tparam T Base type for column.
 */
struct __attribute__((packed)) column {
   std::size_t data_count;
   T * data_ptr;
   bool owns_memory;
   using base_t = T;
#ifdef HAS_MCD
   bool use_mcd;
#endif
   
   template< class... Args >
   /**
    * @brief Constructor for column.
    * @tparam Args Types for decorators.
    * @param dc Number of elements which should fit in the container.
    * @param args Arguments for decorators.
    */
   column(
      std::size_t dc,
#ifdef HAS_MCD
      bool _use_mcd,
#endif
      Args... args
   ):
      data_count{ dc },
#ifdef HAS_MCD
      data_ptr{ ( T* ) acquire(dc*sizeof( T ),
         _use_mcd,
         args... ) },
#else
      data_ptr{
         ( T * ) acquire(
            dc * sizeof( T ),
            args...
         )
      },
#endif
      owns_memory{ true }
#ifdef HAS_MCD
   , use_mcd{ _use_mcd }
#endif
   { }
   
   column( T * p_data_ptr, std::size_t dc ) :
      data_count{ dc },
      data_ptr{ p_data_ptr },
      owns_memory{ false } { }
   
   /**
    * @brief Destructor.
    */
   ~column( ) {
      if( owns_memory )
#ifdef HAS_MCD
         release_ptr( data_ptr, use_mcd );
#else
      {
         release_ptr( data_ptr );
      }
#endif
   }
   
   /**
    * @brief Initialize the column with a sequence.
    * @param base Start value for the sequence.
    */
   void init_seq( T base ) {
      for(
         std::size_t i = 0; i < data_count; ++i
         ) {
         data_ptr[ i ] = base + i;
      }
   }
   
   /**
    * @brief Initialize the column with a specific value.
    * @param base Value which should be used for initialization.
    */
   void init( T base ) {
      for(
         std::size_t i = 0; i < data_count; ++i
         ) {
         data_ptr[ i ] = base;
      }
   }
   
   /**
    * @brief Compares the pointers of the underlying arrays from two column.
    * @param l First column.
    * @param r Second column.
    * @return True, if pointer of l is smaller than pointer of r.
    */
   friend inline bool operator<( const column & l, const column & r ) {
      return ( l.data_ptr ) < ( r.data_ptr );
   }
   
   friend inline bool operator>( const column & l, const column & r ) {
      return r < l;
   }
   
   friend inline bool operator<=( const column & l, const column & r ) {
      return !( l > r );
   }
   
   friend inline bool operator>=( const column & l, const column & r ) {
      return !( l < r );
   }
};

}
#ifdef SIMQ_DEBUG
#  ifdef HAS_MCD
#     define create_column(type, datacount, use_mcd) new tuddbs::column< type >( datacount, use_mcd, 64, __FILE__, __LINE__)
#     define create_bitmask(type, datacount, use_mcd) new tuddbs::column< type >( tuddbs::calculate_datacount_needed_for_bitmask< type >( datacount ), use_mcd, 64, __FILE__, __LINE__)
#     define destroy_column(columnptr) delete columnptr;
#  else
#     define create_column(type, datacount) new tuddbs::column< type >( datacount, 64, __FILE__, __LINE__)/*;std::cout << "Create called: " << __FILE__ << ":" << __LINE__ << "\n"*/
#     define create_bitmask(type, datacount) new tuddbs::column< type >( tuddbs::calculate_datacount_needed_for_bitmask< type >( datacount ), 64, __FILE__, __LINE__)/*;std::cout << "Create called: " << __FILE__ << ":" << __LINE__ << "\n"*/
#     define destroy_column(columnptr) /*std::cout << "Delete called: " << __FILE__ << ":" << __LINE__ << "\n";*/delete columnptr
#  endif
#else
#  ifdef HAS_MCD
#     define create_column(type, datacount, use_mcd) new tuddbs::column< type >( datacount, use_mcd, 64 )
#     define create_bitmask(type, datacount, use_mcd) new tuddbs::column< type >( tuddbs::calculate_datacount_needed_for_bitmask< type >( datacount ), use_mcd, 64 )
#     define destroy_column(columnptr) delete columnptr;
#  else
#     define create_column( type, datacount ) new tuddbs::column< type >( datacount, 64 )
#     define create_bitmask( type, datacount ) new tuddbs::column< type >( tuddbs::calculate_datacount_needed_for_bitmask< type >( datacount ), 64 )
#     define destroy_column( columnptr ) delete columnptr;
#  endif
#endif

#endif //TUDDBS_SIMQ_INCLUDE_DATA_COLUMN_H
