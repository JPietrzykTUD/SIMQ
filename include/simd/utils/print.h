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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_UTILS_PRINT_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_UTILS_PRINT_H

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <string>
#include <simd/intrin.h>

#define TUDDBS_SIMQ_MIN_PRINT_SIZE 5

namespace tuddbs {
   
   template< class VectorExtension >
   void
   print(
      std::ostream & os, typename VectorExtension::vector_t const & simd_register, std::string identifier = "",
      std::size_t max_size = 0
   ) {
      typename vector_constants_t< VectorExtension >::array_t tmp;
      [[maybe_unused]] auto
                                                              tmp2                    =
                                                                 store< VectorExtension >( tmp.data( ), simd_register );
      std::size_t                                             max_size_for_all_values =
//         ( max_size == 0 ) ? 32 - __builtin_clz( *( std::max_element( tmp.begin(), tmp.end() ) ) ) : max_size;
                                                                 ( max_size == 0 ) ? (
                                                                    std::to_string(
                                                                       *( std::max_element( tmp.begin( ), tmp.end( ) ) )
                                                                    )
                                                                 ).length( ) : max_size;
      max_size_for_all_values =
         ( max_size_for_all_values < TUDDBS_SIMQ_MIN_PRINT_SIZE ) ? TUDDBS_SIMQ_MIN_PRINT_SIZE
                                                                  : max_size_for_all_values;
      os
         << std::setw( 10 )
         << identifier
         << "( VEC "
         << std::setw( 10 )
         << vector_extension_to_str< VectorExtension >( )
         << ") :";
      os << "| ";
      for(
         auto it = tmp.rbegin( ); it != tmp.rend( ); it++
         ) {
         os << std::setw( max_size_for_all_values ) << *it + 0 << " | ";
      }
      os << "\n";
   }
   
   template< class VectorExtension >
   void
   print(
      std::ostream & os, typename VectorExtension::mask_t const & mask, std::string identifier = "",
      std::size_t max_size = 0
   ) {
      std::bitset< sizeof( typename VectorExtension::mask_t ) * 8 > bs{ mask };
      os
         << std::setw( 10 )
         << identifier
         << "(MASK "
         << std::setw( 10 )
         << vector_extension_to_str< VectorExtension >( )
         << ") :";
      os << "| ";
      std::size_t max_size_for_all_values =
                     ( max_size == 0 ) ? TUDDBS_SIMQ_MIN_PRINT_SIZE : max_size;
      for(
         int      i                       = ( sizeof( typename VectorExtension::mask_t ) * 8 ) - 1; i >= 0; i--
         ) {
         if( bs[ i ] == 0 ) {
            os << std::setw( max_size_for_all_values ) << "FALSE" << " | ";
         } else {
            os << std::setw( max_size_for_all_values ) << "TRUE" << " | ";
         }
      }
      os << "\n";
   }
   
   template< class VectorExtension >
   struct vec_ext_to_string_t;

#ifdef INTEL_SIMDI
   template< >
   struct vec_ext_to_string_t< sse< uint8_t > > {
      static std::string apply( void ) {
         return "SSE;8";
      }
   };
   template< >
   struct vec_ext_to_string_t< sse< uint16_t > > {
      static std::string apply( void ) {
         return "SSE;16";
      }
   };
   template< >
   struct vec_ext_to_string_t< sse< uint32_t > > {
      static std::string apply( void ) {
         return "SSE;32";
      }
   };
   template< >
   struct vec_ext_to_string_t< sse< uint64_t > > {
      static std::string apply( void ) {
         return "SSE;64";
      }
   };

   template< >
   struct vec_ext_to_string_t< avx2< uint8_t > > {
      static std::string apply( void ) {
         return "AVX2;8";
      }
   };
   template< >
   struct vec_ext_to_string_t< avx2< uint16_t > > {
      static std::string apply( void ) {
         return "AVX2;16";
      }
   };
   template< >
   struct vec_ext_to_string_t< avx2< uint32_t > > {
      static std::string apply( void ) {
         return "AVX2;32";
      }
   };
   template< >
   struct vec_ext_to_string_t< avx2< uint64_t > > {
      static std::string apply( void ) {
         return "AVX2;64";
      }
   };

   template< >
   struct vec_ext_to_string_t< avx512< uint8_t > > {
      static std::string apply( void ) {
         return "AVX512;8";
      }
   };
   template< >
   struct vec_ext_to_string_t< avx512< uint16_t > > {
      static std::string apply( void ) {
         return "AVX512;16";
      }
   };
   template< >
   struct vec_ext_to_string_t< avx512< uint32_t > > {
      static std::string apply( void ) {
         return "AVX512;32";
      }
   };
   template< >
   struct vec_ext_to_string_t< avx512< uint64_t > > {
      static std::string apply( void ) {
         return "AVX512;64";
      }
   };
#endif
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_UTILS_PRINT_H
