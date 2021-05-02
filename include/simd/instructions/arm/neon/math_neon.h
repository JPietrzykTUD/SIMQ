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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_MATH_NEON_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_MATH_NEON_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/neon.h>
#include <simd/instructions/declarations/math.h>

#include <cstdint>

namespace tuddbs {

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   add< neon < uint8_t > >(
      typename neon< uint8_t >::vector_t const a,
      typename neon< uint8_t >::vector_t const b
   ) {
      return vaddq_u8( a, b );   
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   add< neon < uint16_t > >(
      typename neon< uint16_t >::vector_t const a,
      typename neon< uint16_t >::vector_t const b
   ) {
      return vaddq_u16( a, b );   
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   add< neon < uint32_t > >(
      typename neon< uint32_t >::vector_t const a,
      typename neon< uint32_t >::vector_t const b
   ) {
      return vaddq_u32( a, b );   
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   add< neon < uint64_t > >(
      typename neon< uint64_t >::vector_t const a,
      typename neon< uint64_t >::vector_t const b
   ) {
      return vaddq_u64( a, b );   
   }



   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   sub< neon < uint8_t > >(
   typename neon< uint8_t >::vector_t const a,
   typename neon< uint8_t >::vector_t const b
   ) {
      return vsubq_u8( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   sub< neon < uint16_t > >(
   typename neon< uint16_t >::vector_t const a,
   typename neon< uint16_t >::vector_t const b
   ) {
      return vsubq_u16( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   sub< neon < uint32_t > >(
   typename neon< uint32_t >::vector_t const a,
   typename neon< uint32_t >::vector_t const b
   ) {
      return vsubq_u32( a, b );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   sub< neon < uint64_t > >(
   typename neon< uint64_t >::vector_t const a,
   typename neon< uint64_t >::vector_t const b
   ) {
      return vsubq_u64( a, b );
   }



   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   mask_add< neon< uint8_t > >(
      typename neon< uint8_t >::vector_t const incrementor,
      typename neon< uint8_t >::vector_t const result,
      typename neon< uint8_t >::mask_t const mask
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
      return vorrq_u8( vandq_u8( vaddq_u8( result, incrementor ), mask_vec ), vbicq_u8( result, mask_vec ) );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   mask_add< neon< uint16_t > >(
      typename neon< uint16_t >::vector_t const incrementor,
      typename neon< uint16_t >::vector_t const result,
      typename neon< uint16_t >::mask_t const mask
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
      return vorrq_u16( vandq_u16( vaddq_u16( result, incrementor ), mask_vec ), vbicq_u16( result, mask_vec ) );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   mask_add< neon< uint32_t > >(
      typename neon< uint32_t >::vector_t const incrementor,
      typename neon< uint32_t >::vector_t const result,
      typename neon< uint32_t >::mask_t const mask
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
      return vorrq_u32( vandq_u32( vaddq_u32( result, incrementor ), mask_vec ), vbicq_u32( result, mask_vec ) );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   mask_add< neon< uint64_t > >(
      typename neon< uint64_t >::vector_t const incrementor,
      typename neon< uint64_t >::vector_t const result,
      typename neon< uint64_t >::mask_t const mask
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
      return vorrq_u64( vandq_u64( vaddq_u64( result, incrementor ), mask_vec ), vbicq_u64( result, mask_vec ) );
   }

}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_MATH_NEON_H