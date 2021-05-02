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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_MISC_NEON_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_MISC_NEON_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/arm/neon.h>
#include <simd/instructions/declarations/misc.h>

#include <cstdint>


namespace tuddbs {
   
   template< >
   char const * vector_extension_to_str< neon < uint8_t > >( void ) {
      return "NEON;u8";
   }
   template< >
   char const * vector_extension_to_str< neon < uint16_t > >( void ) {
      return "NEON;u16";
   }
   template< >
   char const * vector_extension_to_str< neon < uint32_t > >( void ) {
      return "NEON;u32";
   }
   template< >
   char const * vector_extension_to_str< neon < uint64_t > >( void ) {
      return "NEON;u64";
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   blend< neon< uint8_t > >(
      typename neon< uint8_t >::vector_t const value,
      typename neon< uint8_t >::mask_t const mask,
      typename neon< uint8_t >::vector_t const src
   ) {
      uint8x16_t cmp = { 
         1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128 
      };

      typename neon< uint8_t >::vector_t mask_vec =
         vceqq_u8(
            vandq_u8(
               vcombine_u8(
                  vdup_n_u8( (uint8_t) mask ),
                  vdup_n_u8( (uint8_t) ( mask >> 8 ) ) 
               ),  
               cmp 
            ),  
            cmp 
         );
      return vorrq_u8( vandq_u8( value, mask_vec ), vbicq_u8( src, mask_vec ) );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   blend< neon< uint16_t > >(
      typename neon< uint16_t >::vector_t const value,
      typename neon< uint16_t >::mask_t const mask,
      typename neon< uint16_t >::vector_t const src
   ) {
      uint16x8_t cmp = { 
         1, 2, 4, 8, 16, 32, 64, 128
      };

      typename neon< uint16_t >::vector_t mask_vec =
         vceqq_u16(
            vandq_u16(
               vdupq_n_u16( ( uint16_t ) mask ),  
               cmp 
            ),  
            cmp 
         );
      return vorrq_u16( vandq_u16( value, mask_vec ), vbicq_u16( src, mask_vec ) );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   blend< neon< uint32_t > >(
      typename neon< uint32_t >::vector_t const value,
      typename neon< uint32_t >::mask_t const mask,
      typename neon< uint32_t >::vector_t const src
   ) {
      uint32x4_t cmp = { 
         1, 2, 4, 8
      };
      typename neon< uint32_t >::vector_t mask_vec =
         vceqq_u32(
            vandq_u32(
               vdupq_n_u32( ( uint32_t ) mask ),  
               cmp 
            ),  
            cmp 
         );
      return vorrq_u32( vandq_u32( value, mask_vec ), vbicq_u32( src, mask_vec ) );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   blend< neon< uint64_t > >(
      typename neon< uint64_t >::vector_t const value,
      typename neon< uint64_t >::mask_t const mask,
      typename neon< uint64_t >::vector_t const src
   ) {
      uint64x2_t cmp = { 
         1, 2
      };

      typename neon< uint64_t >::vector_t mask_vec =
         vceqq_u64(
            vandq_u64(
               vdupq_n_u64( ( uint64_t ) mask ),  
               cmp 
            ),  
            cmp 
         );
      return vorrq_u64( vandq_u64( value, mask_vec ), vbicq_u64( src, mask_vec ) );
   }
}


#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_MISC_NEON_H