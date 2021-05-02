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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_CREATE_NEON_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_CREATE_NEON_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/arm/neon.h>
#include <simd/instructions/declarations/create.h>

#include <cstdint>

namespace tuddbs {

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   broadcast< neon < uint8_t > >(
      typename neon< uint8_t >::base_t const a
   ) {
      return vdupq_n_u8( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   broadcast< neon < uint16_t > >(
      typename neon< uint16_t >::base_t const a
   ) {
      return vdupq_n_u16( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   broadcast< neon < uint32_t > >(
      typename neon< uint32_t >::base_t const a
   ) {
      return vdupq_n_u32( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   broadcast< neon < uint64_t > >(
      typename neon< uint64_t >::base_t const a
   ) {
      return vdupq_n_u64( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   mask_broadcast< neon< uint8_t > >(
      typename neon< uint8_t >::base_t const value,
      typename neon< uint8_t >::mask_t const mask,
      typename neon< uint8_t >::vector_t const src
   ) {
      uint8x16_t cmp = { 
         1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128 
      };

      uint8x16_t mask_vec = 
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
      return vorrq_u8(
         vandq_u8( vdupq_n_u8( value ), mask_vec ),
         vbicq_u8(src, mask_vec )
      );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   mask_broadcast< neon< uint16_t > >(
      typename neon< uint16_t >::base_t const value,
      typename neon< uint16_t >::mask_t const mask,
      typename neon< uint16_t >::vector_t const src
   ) {
      uint16x8_t cmp = { 
         1, 2, 4, 8, 16, 32, 64, 128
      };

      uint16x8_t mask_vec = 
         vceqq_u16(
            vandq_u16(
               vdupq_n_u16( ( uint16_t ) mask ),  
               cmp 
            ),  
            cmp 
         );
      return vorrq_u16(
         vandq_u16( vdupq_n_u16( value ), mask_vec ),
         vbicq_u16(src, mask_vec )
      );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   mask_broadcast< neon< uint32_t > >(
      typename neon< uint32_t >::base_t const value,
      typename neon< uint32_t >::mask_t const mask,
      typename neon< uint32_t >::vector_t const src
   ) {
      uint32x4_t cmp = { 
         1, 2, 4, 8
      };

      uint32x4_t mask_vec = 
         vceqq_u32(
            vandq_u32(
               vdupq_n_u32( ( uint32_t ) mask ),  
               cmp 
            ),  
            cmp 
         );
      return vorrq_u32(
         vandq_u32( vdupq_n_u32( value ), mask_vec ),
         vbicq_u32(src, mask_vec )
      );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   mask_broadcast< neon< uint64_t > >(
      typename neon< uint64_t >::base_t const value,
      typename neon< uint64_t >::mask_t const mask,
      typename neon< uint64_t >::vector_t const src
   ) {
      uint64x2_t cmp = { 
         1, 2
      };

      uint64x2_t mask_vec = 
         vceqq_u64(
            vandq_u64(
               vdupq_n_u64( ( uint16_t ) mask ),  
               cmp 
            ),  
            cmp 
         );
      return vorrq_u64(
         vandq_u64( vdupq_n_u64( value ), mask_vec ),
         vbicq_u64(src, mask_vec )
      );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   set_zero< neon < uint8_t > >( void ) {
      return vdupq_n_u8( 0 );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   set_zero< neon < uint16_t > >( void ) {
      return vdupq_n_u16( 0 );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   set_zero< neon < uint32_t > >( void ) {
      return vdupq_n_u32( 0 );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   set_zero< neon < uint64_t > >( void ) {
      return vdupq_n_u64( 0 );
   }


   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   maskz_move< neon< uint8_t > >(
      typename neon< uint8_t >::mask_t const mask,
      typename neon< uint8_t >::vector_t const a
   ) {
      uint8x16_t cmp = { 
         1, 2, 4, 8, 16, 32, 64, 128, 1, 2, 4, 8, 16, 32, 64, 128 
      };

      uint8x16_t mask_vec = 
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
      return vandq_u8( a, mask_vec );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   maskz_move< neon< uint16_t > >(
      typename neon< uint16_t >::mask_t const mask,
      typename neon< uint16_t >::vector_t const a
   ) {
      uint16x8_t cmp = { 
         1, 2, 4, 8, 16, 32, 64, 128
      };

      uint16x8_t mask_vec = 
         vceqq_u16(
            vandq_u16(
               vdupq_n_u16( ( uint16_t ) mask ),  
               cmp 
            ),  
            cmp 
         );
      return vandq_u16( a, mask_vec );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   maskz_move< neon< uint32_t > >(
      typename neon< uint32_t >::mask_t const mask,
      typename neon< uint32_t >::vector_t const a
   ) {
      uint32x4_t cmp = { 
         1, 2, 4, 8
      };

      uint32x4_t mask_vec = 
         vceqq_u32(
            vandq_u32(
               vdupq_n_u32( ( uint32_t ) mask ),  
               cmp 
            ),  
            cmp 
         );

      return vandq_u32( a, mask_vec );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   maskz_move< neon< uint64_t > >(
      typename neon< uint64_t >::mask_t const mask,
      typename neon< uint64_t >::vector_t const a
   ) {
      uint64x2_t cmp = { 
         1, 2
      };

      uint64x2_t mask_vec = 
         vceqq_u64(
            vandq_u64(
               vdupq_n_u64( ( uint64_t ) mask ),
               cmp 
            ),  
            cmp 
         );
      
      return vandq_u64( a, mask_vec );
   }



   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::mask_t
   move_mask< neon< uint8_t > >( 
      typename neon< uint8_t >::vector_t const mask_vec
   ) {
      typename neon< uint8_t >::vector_t t = vandq_u8( mask_vec, vdupq_n_u8( 0x80 ) );
      return
         (
            ( ( (typename neon< uint8_t >::mask_t) t[ 15 ] ) << 8 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[ 14 ] ) << 7 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[ 13 ] ) << 6 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[ 12 ] ) << 5 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[ 11 ] ) << 4 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[ 10 ] ) << 3 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  9 ] ) << 2 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  8 ] ) << 1 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  7 ] )      ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  6 ] ) >> 1 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  5 ] ) >> 2 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  4 ] ) >> 3 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  3 ] ) >> 4 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  2 ] ) >> 5 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  1 ] ) >> 6 ) |
            ( ( (typename neon< uint8_t >::mask_t) t[  0 ] ) >> 7 )
         );
   }


   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::mask_t
   move_mask< neon< uint16_t > >( 
      typename neon< uint16_t >::vector_t const mask_vec
   ) {
      typename neon< uint16_t >::vector_t t =
         vandq_u16( 
            vshrq_n_u16( 
               mask_vec,
               8
            ), 
            vdupq_n_u16( 0x80 ) 
         );
      return
         (
            ( ( (typename neon< uint16_t >::mask_t)  t[ 7 ] )      ) |
            ( ( (typename neon< uint16_t >::mask_t)  t[ 6 ] ) >> 1 ) |
            ( ( (typename neon< uint16_t >::mask_t)  t[ 5 ] ) >> 2 ) |
            ( ( (typename neon< uint16_t >::mask_t)  t[ 4 ] ) >> 3 ) |
            ( ( (typename neon< uint16_t >::mask_t)  t[ 3 ] ) >> 4 ) |
            ( ( (typename neon< uint16_t >::mask_t)  t[ 2 ] ) >> 5 ) |
            ( ( (typename neon< uint16_t >::mask_t)  t[ 1 ] ) >> 6 ) |
            ( ( (typename neon< uint16_t >::mask_t)  t[ 0 ] ) >> 7 )
         );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::mask_t
   move_mask< neon< uint32_t > >( 
      typename neon< uint32_t >::vector_t const mask_vec
   ) {
      typename neon< uint32_t >::vector_t t =
         vandq_u32( 
            vshrq_n_u32( 
               mask_vec,
               24
            ), 
            vdupq_n_u32( 0x80 ) 
         );
      return
         (
            ( ( (typename neon< uint32_t >::mask_t) t[ 3 ] ) >> 4 ) |
            ( ( (typename neon< uint32_t >::mask_t) t[ 2 ] ) >> 5 ) |
            ( ( (typename neon< uint32_t >::mask_t) t[ 1 ] ) >> 6 ) |
            ( ( (typename neon< uint32_t >::mask_t) t[ 0 ] ) >> 7 )
         );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::mask_t
   move_mask< neon< uint64_t > >( 
      typename neon< uint64_t >::vector_t const mask_vec
   ) {
      return ( ( mask_vec[ 0 ] >> 63 ) | ( ( mask_vec[ 1 ] >> 62 ) & 0b10 ) );
   }
}

#endif  //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_CREATE_NEON_H