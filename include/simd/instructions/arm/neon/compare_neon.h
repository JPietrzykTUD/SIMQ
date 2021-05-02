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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_COMPARE_NEON_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_COMPARE_NEON_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/arm/neon.h>
#include <simd/instructions/declarations/compare.h>

#include <cstdint>


namespace tuddbs {
   

   template< > NO_DISCARD           FORCE_INLINE
   typename neon< uint8_t >::mask_t cmp_lt< neon < uint8_t >
   >(
      typename neon< uint8_t >::vector_t const a,
      typename neon< uint8_t >::vector_t const b
   ) {
      typename neon< uint8_t >::vector_t t = vandq_u8( vcltq_u8( a, b ), vdupq_n_u8( 0x80 ) );
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

   template< > NO_DISCARD           FORCE_INLINE
   typename neon< uint16_t >::mask_t cmp_lt< neon < uint16_t > 
   >(
      typename neon< uint16_t >::vector_t const a,
      typename neon< uint16_t >::vector_t const b
   ) {
      typename neon< uint16_t >::vector_t t =
         vandq_u16( 
            vshrq_n_u16( 
               vcltq_u16( a, b ),
               8
            ), 
            vdupq_n_u16( 0x80 ) 
         );
      return
         (
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 7 ] )      ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 6 ] ) >> 1 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 5 ] ) >> 2 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 4 ] ) >> 3 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 3 ] ) >> 4 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 2 ] ) >> 5 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 1 ] ) >> 6 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 0 ] ) >> 7 )
         );
   }


   template< > NO_DISCARD           FORCE_INLINE
   typename neon< uint32_t >::mask_t cmp_lt< neon < uint32_t >
   >(
      typename neon< uint32_t >::vector_t const a,
      typename neon< uint32_t >::vector_t const b
   ) {
      typename neon< uint32_t >::vector_t t =
         vandq_u32( 
            vshrq_n_u32( 
               vcltq_u32( a, b ),
               24
            ), 
            vdupq_n_u32( 0x80 ) 
         );
      return
         (
            ( ( (typename neon< uint32_t >::mask_t) t[ 3 ] )      ) |
            ( ( (typename neon< uint32_t >::mask_t) t[ 2 ] ) >> 1 ) |
            ( ( (typename neon< uint32_t >::mask_t) t[ 1 ] ) >> 2 ) |
            ( ( (typename neon< uint32_t >::mask_t) t[ 0 ] ) >> 3 )
         );
   }

   template< > NO_DISCARD           FORCE_INLINE
   typename neon< uint64_t >::mask_t cmp_lt< neon < uint64_t > 
   >(
      typename neon< uint64_t >::vector_t const a,
      typename neon< uint64_t >::vector_t const b
   ) {
      typename neon< uint64_t >::vector_t result = vcltq_u64( a, b );
      return ( ( result[ 0 ] >> 63 ) | ( ( result[ 1 ] >> 62 ) & 0b10 ) );
   }

   template< > NO_DISCARD           FORCE_INLINE
   typename neon< uint8_t >::mask_t cmp_neq< neon < uint8_t >
   >(
      typename neon< uint8_t >::vector_t const a,
      typename neon< uint8_t >::vector_t const b
   ) {
      typename neon< uint8_t >::vector_t t = veorq_u8( vceqq_u8( a, b ), vdupq_n_u8( 0x80 ) ); // ( a == b ) ^ 0x80 <=> (a!=b)
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

   template< > NO_DISCARD           FORCE_INLINE
   typename neon< uint16_t >::mask_t cmp_neq< neon < uint16_t > 
   >(
      typename neon< uint16_t >::vector_t const a,
      typename neon< uint16_t >::vector_t const b
   ) {
      typename neon< uint16_t >::vector_t t =
         veorq_u16( 
            vshrq_n_u16( 
               vceqq_u16( a, b ),
               8
            ), 
            vdupq_n_u16( 0x80 ) 
         );
      return
         (
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 7 ] )      ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 6 ] ) >> 1 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 5 ] ) >> 2 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 4 ] ) >> 3 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 3 ] ) >> 4 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 2 ] ) >> 5 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 1 ] ) >> 6 ) |
            ( ( (typename neon< uint16_t >::mask_t) ( t[ 0 ] ) >> 7 )
         );
   }


   template< > NO_DISCARD           FORCE_INLINE
   typename neon< uint32_t >::mask_t cmp_neq< neon < uint32_t >
   >(
      typename neon< uint32_t >::vector_t const a,
      typename neon< uint32_t >::vector_t const b
   ) {
      typename neon< uint32_t >::vector_t t =
         veorq_u32( 
            vshrq_n_u32( 
               vceqq_u32( a, b ),
               24
            ), 
            vdupq_n_u32( 0x80 ) 
         );
      return
         (
            ( ( (typename neon< uint32_t >::mask_t) t[ 3 ] )      ) |
            ( ( (typename neon< uint32_t >::mask_t) t[ 2 ] ) >> 1 ) |
            ( ( (typename neon< uint32_t >::mask_t) t[ 1 ] ) >> 2 ) |
            ( ( (typename neon< uint32_t >::mask_t) t[ 0 ] ) >> 3 )
         );
   }

   template< > NO_DISCARD           FORCE_INLINE
   typename neon< uint64_t >::mask_t cmp_neq< neon < uint64_t > 
   >(
      typename neon< uint64_t >::vector_t const a,
      typename neon< uint64_t >::vector_t const b
   ) {
      typename neon< uint64_t >::vector_t result = vceqq_u64( a, b );
      return ( ( ( result[ 0 ] >> 63 ) ^ 0b1 ) | ( ( result[ 1 ] >> 62 ) ^ 0b10 ) );
   }



   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   min< neon < uint8_t >
   >(
      typename neon< uint8_t >::vector_t const a,
      typename neon< uint8_t >::vector_t const b
   ) {
      return vminq_u8( a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   min< neon < uint16_t >
   >(
      typename neon< uint16_t >::vector_t const a,
      typename neon< uint16_t >::vector_t const b
   ) {
      return vminq_u16( a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   min< neon < uint32_t >
   >(
      typename neon< uint32_t >::vector_t const a,
      typename neon< uint32_t >::vector_t const b
   ) {
      return vminq_u32( a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   min< neon < uint64_t >
   >(
      typename neon< uint64_t >::vector_t const a,
      typename neon< uint64_t >::vector_t const b
   ) {
      typename neon< uint64_t >::vector_t tmp = vcltq_u64( a, b );
      return vorrq_u64(
         vandq_u64( a, tmp ),
         vbicq_u64( b, tmp )
      );
   }

      template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   mask_min< neon < uint8_t >
   >(
      typename neon< uint8_t >::vector_t const a,
      typename neon< uint8_t >::vector_t const b,
      typename neon< uint8_t >::mask_t const mask
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
      return vorrq_u8( vandq_u8( vminq_u8( a, b ), mask_vec ), vbicq_u8(b, mask_vec ));
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   mask_min< neon < uint16_t >
   >(
      typename neon< uint16_t >::vector_t const a,
      typename neon< uint16_t >::vector_t const b,
      typename neon< uint16_t >::mask_t const mask
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
      return vorrq_u16( vandq_u16( vminq_u16( a, b ), mask_vec ), vbicq_u16(b, mask_vec ));
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   mask_min< neon < uint32_t >
   >(
      typename neon< uint32_t >::vector_t const a,
      typename neon< uint32_t >::vector_t const b,
      typename neon< uint32_t >::mask_t const mask
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
      return vorrq_u32( vandq_u32( vminq_u32( a, b ), mask_vec ), vbicq_u32(b, mask_vec ));
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   mask_min< neon < uint64_t >
   >(
      typename neon< uint64_t >::vector_t const a,
      typename neon< uint64_t >::vector_t const b,
      typename neon< uint64_t >::mask_t const mask
   ) {
      typename neon< uint64_t >::vector_t tmp = vcltq_u64( a, b );
      typename neon< uint64_t >::vector_t min_vec = 
         vorrq_u64(
            vandq_u64( a, tmp ),
            vbicq_u64( b, tmp )
         );
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
      return vorrq_u64( vandq_u64( min_vec, mask_vec ), vbicq_u64(b, mask_vec ));
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   max< neon < uint8_t >
   >(
      typename neon< uint8_t >::vector_t const a,
      typename neon< uint8_t >::vector_t const b
   ) {
      return vmaxq_u8( a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   max< neon < uint16_t >
   >(
      typename neon< uint16_t >::vector_t const a,
      typename neon< uint16_t >::vector_t const b
   ) {
      return vmaxq_u16( a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   max< neon < uint32_t >
   >(
      typename neon< uint32_t >::vector_t const a,
      typename neon< uint32_t >::vector_t const b
   ) {
      return vmaxq_u32( a, b );
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   max< neon < uint64_t >
   >(
      typename neon< uint64_t >::vector_t const a,
      typename neon< uint64_t >::vector_t const b
   ) {
      typename neon< uint64_t >::vector_t tmp = vcgtq_u64( a, b );
      return vorrq_u64(
         vandq_u64( a, tmp ),
         vbicq_u64( b, tmp )
      );
   }

      template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   mask_max< neon < uint8_t >
   >(
      typename neon< uint8_t >::vector_t const a,
      typename neon< uint8_t >::vector_t const b,
      typename neon< uint8_t >::mask_t const mask
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
      return vorrq_u8( vandq_u8( vmaxq_u8( a, b ), mask_vec ), vbicq_u8(b, mask_vec ));
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   mask_max< neon < uint16_t >
   >(
      typename neon< uint16_t >::vector_t const a,
      typename neon< uint16_t >::vector_t const b,
      typename neon< uint16_t >::mask_t const mask
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
      return vorrq_u16( vandq_u16( vmaxq_u16( a, b ), mask_vec ), vbicq_u16(b, mask_vec ));
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   mask_max< neon < uint32_t >
   >(
      typename neon< uint32_t >::vector_t const a,
      typename neon< uint32_t >::vector_t const b,
      typename neon< uint32_t >::mask_t const mask
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
      return vorrq_u32( vandq_u32( vmaxq_u32( a, b ), mask_vec ), vbicq_u32(b, mask_vec ));
   }
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   mask_max< neon < uint64_t >
   >(
      typename neon< uint64_t >::vector_t const a,
      typename neon< uint64_t >::vector_t const b,
      typename neon< uint64_t >::mask_t const mask
   ) {
      typename neon< uint64_t >::vector_t tmp = vcltq_u64( a, b );
      typename neon< uint64_t >::vector_t min_vec = 
         vorrq_u64(
            vandq_u64( a, tmp ),
            vbicq_u64( b, tmp )
         );
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
      return vorrq_u64( vandq_u64( min_vec, mask_vec ), vbicq_u64(b, mask_vec ));
   }
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_COMPARE_NEON_H