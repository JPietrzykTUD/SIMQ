/*
 * This file is part of the SIMQ Project (https://github.com/JPietrzykTUD/SIMQ).
 * Copyright (c) 2021 Johannes Pietrzyk.
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

#ifndef TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_BITMASK_COMPLEX_BITMASK_H
#define TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_BITMASK_COMPLEX_BITMASK_H

#include <cstdint>
#include <cstddef>

#include <cstddef>
#include <type_traits>
#include <typeinfo>

#ifndef _MSC_VER

#   include <cxxabi.h>

#endif

#include <memory>
#include <string>
#include <cstdlib>
#include <limits>

#include <utils/preprocessor.h>
#include <simd/intrin.h>

namespace tuddbs {
   
   template< class T >
   std::string type_name( ) {
      typedef typename std::remove_reference< T >::type TR;
      std::unique_ptr< char, void ( * )( void * ) >     own
                                                           (
#ifndef _MSC_VER
                                                           abi::__cxa_demangle(
                                                              typeid( TR ).name( ), nullptr,
                                                              nullptr, nullptr
                                                           ),
#else
                                                           nullptr,
#endif
                                                           std::free
                                                        );
      std::string                                       r = own != nullptr ? own.get( ) : typeid( TR ).name( );
      if( std::is_const< TR >::value ) {
         r += " const";
      }
      if( std::is_volatile< TR >::value ) {
         r += " volatile";
      }
      if( std::is_lvalue_reference< T >::value ) {
         r += "&";
      } else if( std::is_rvalue_reference< T >::value ) {
         r += "&&";
      }
      return r;
   }

#define TYPENAME( x ) type_name< decltype( x ) >( )
   
   template< typename T >
   struct next_bigger_type;
   
   template< >
   struct next_bigger_type< uint32_t > {
      using type = uint64_t;
   };
   template< >
   struct next_bigger_type< uint16_t > {
      using type = uint32_t;
   };
   template< >
   struct next_bigger_type< uint8_t > {
      using type = uint16_t;
   };
   
   template< typename T >
   using next_bigger_type_t = typename next_bigger_type< T >::type;
   
   /**
    * @brief Helper class for complex masks (where not all bits are relevant for the caller).
    * We assume, that relevant bits are clustered (not interrupted by irrelevant bits)
    * @tparam VectorExtension
    * @tparam NumberOfParticipants Allowed Values so far: 1, 2, 3 (Because we only have 3 successor-operators)
    * @tparam NumberOfBits
    */
   template<
      class VectorExtension,
      std::size_t NumberOfBits = 0,
      std::size_t BitPositionOffset = 0
   >
   struct complex_bitmask_helper_t {
      
      using mask_t = typename VectorExtension::mask_t;
      using bits_per_mask_t = std::integral_constant< std::size_t, sizeof( mask_t ) << 3 >;
      using vecs_per_mask_t = typename vector_constants_t< VectorExtension >::number_of_vectors_per_mask_t;
      using number_of_bits_per_mask =
      std::integral_constant<
         std::size_t, NumberOfBits * vecs_per_mask_t::value
      >;
      
      using incrementor_t =
      std::integral_constant<
         std::size_t, bits_per_mask_t::value / number_of_bits_per_mask::value
      >;
      /*using vectors_to_acces_per_mask_count_t =
         std::integral_constant<
            std::size_t,
            vector_constants_t< VectorExtension >::vector_element_count_t::value / NumberOfBits
            //assuming a vector register with 16 slots, if 4 bits per mask are valid, than 4 masks have to be loaded to get
            //all bits corresponding with the vector
         >;
      using incrementor_t =
         std::integral_constant<
            std::size_t,
            vectors_to_acces_per_mask_count_t::value / vector_constants_t< VectorExtension
            >::number_of_vectors_per_mask_t::value
         >;*/
//      using has_to_be_applied_t = std::integral_constant< bool, (incrementor_t::value != 1) >;
      
      
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 1, std::nullptr_t > = nullptr
      >
      FORCE_INLINE
      static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         if constexpr( vecs_per_mask_t::value == 1 )
         {
            return std::make_tuple( *mask_ptr, mask_ptr + 1 );
         } else if constexpr( vecs_per_mask_t::value == 2 )
         {
            //if 2 vecs per mask than the first bits are @ Bitpositionoffset, the second bits are @
            // 1/2*mask_size_in_bits + Bitpositionoffset
            using offset_t = std::integral_constant< std::size_t, bits_per_mask_t::value / vecs_per_mask_t::value >;
            auto tmp = *mask_ptr;
            return std::make_tuple(
               (
                  ( tmp >> BitPositionOffset ) |
                  ( ( ( tmp >> BitPositionOffset ) >> offset_t::value ) << ( NumberOfBits ) )
               ),
               mask_ptr + 1
            );
         } else if constexpr( vecs_per_mask_t::value == 4 )
         {
            using offset_t = std::integral_constant< std::size_t, bits_per_mask_t::value / vecs_per_mask_t::value >;
            auto tmp = *mask_ptr;
            return std::make_tuple(
               (
                  ( tmp >> BitPositionOffset ) |
                  ( ( ( tmp >> BitPositionOffset ) >> offset_t::value ) << ( NumberOfBits ) ) |
                  (
                     ( ( tmp >> BitPositionOffset ) >> ( offset_t::value + offset_t::value ) ) << (
                        NumberOfBits +
                        NumberOfBits
                     )
                  ) |
                  (
                     ( ( tmp >> BitPositionOffset ) >> ( offset_t::value + offset_t::value + offset_t::value ) ) << (
                        NumberOfBits + NumberOfBits + NumberOfBits
                     )
                  )
               ),
               mask_ptr + 1
            );
         }
      }
      
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 2, std::nullptr_t > = nullptr
      >
      FORCE_INLINE
      static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
//         if constexpr( vecs_per_mask_t::value == 1 ) {
         return std::make_tuple(
            // First Full Mask
            ( ( *mask_ptr ) >> BitPositionOffset ) |
            // Second Full Mask
            ( ( ( *( mask_ptr + 1 ) ) >> BitPositionOffset ) << NumberOfBits ),
            mask_ptr + 2
         );
//         }
      }
      
      template<
         std::size_t INC = incrementor_t::value,
         typename std::enable_if_t< INC == 4, std::nullptr_t > = nullptr
      >
      FORCE_INLINE
      static
         std::tuple< mask_t, mask_t * >
      read_mask_and_increment( mask_t * mask_ptr ) {
         return std::make_tuple(
            (
               // First Full Mask
               ( ( *mask_ptr ) >> BitPositionOffset ) |
               // Second Full Mask
               ( ( ( *( mask_ptr + 1 ) ) >> BitPositionOffset ) << NumberOfBits ) |
               // Third Full Mask
               ( ( ( *( mask_ptr + 2 ) ) >> BitPositionOffset ) << ( NumberOfBits + NumberOfBits ) ) |
               // Fourth Full Mask
               ( ( ( *( mask_ptr + 3 ) ) >> BitPositionOffset ) << ( NumberOfBits + NumberOfBits + NumberOfBits ) )
            ),
            mask_ptr + 4
         );
      }
   };
   
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMQ_CONTROL_BITMASK_COMPLEX_BITMASK_H
