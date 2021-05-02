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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_IO_NEON_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_IO_NEON_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/arm/neon.h>
#include <simd/instructions/declarations/io.h>

#include <cstdint>

namespace tuddbs {
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::vector_t
   load< neon < uint8_t > >(
      typename neon< uint8_t >::base_t * const a
   ) {
      return vld1q_u8( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::vector_t
   load< neon < uint16_t > >(
      typename neon< uint16_t >::base_t * const a
   ) {
      return vld1q_u16( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::vector_t
   load< neon < uint32_t > >(
      typename neon< uint32_t >::base_t * const a
   ) {
      return vld1q_u32( a );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::vector_t
   load< neon < uint64_t > >(
      typename neon< uint64_t >::base_t * const a
   ) {
      return vld1q_u64( a );
   }      


   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::base_t *
   store< neon < uint8_t > >(
      typename neon< uint8_t >::base_t * const target,
      typename neon< uint8_t >::vector_t const a
   ) {
      vst1q_u8( target, a );
      return ( target + vector_constants_t< neon < uint8_t > >::vector_element_count_t::value );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::base_t *
   store< neon < uint16_t > >(
      typename neon< uint16_t >::base_t * const target,
      typename neon< uint16_t >::vector_t const a
   ) {
      vst1q_u16( target, a );
      return ( target + vector_constants_t< neon < uint16_t > >::vector_element_count_t::value );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::base_t *
   store< neon < uint32_t > >(
      typename neon< uint32_t >::base_t * const target,
      typename neon< uint32_t >::vector_t const a
   ) {
      vst1q_u32( target, a );
      return ( target + vector_constants_t< neon < uint32_t > >::vector_element_count_t::value );
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::base_t *
   store< neon < uint64_t > >(
      typename neon< uint64_t >::base_t * const target,
      typename neon< uint64_t >::vector_t const a
   ) {
      vst1q_u64( target, a );
      return ( target + vector_constants_t< neon < uint64_t > >::vector_element_count_t::value );
   }
   
   template< typename T >
   struct stream_store_impl< neon < T > > {
      NO_DISCARD FORCE_INLINE
      static typename neon< T >::base_t *
      apply(
         typename neon< T >::base_t * const target,
         typename neon< T >::vector_t const a
      ) {
         return store< neon< T > >( target, a );
      }
   };

   template< typename T, std::size_t Scale >
   struct gather_impl< neon < T >, Scale > {
      NO_DISCARD FORCE_INLINE
      typename neon< T >::vector_t
      static apply(
         typename neon< T >::vector_t const vindex,
         typename neon< T >::base_t * const base
      ) {
         typename vector_constants_t< neon < T > > ::array_t idx;
         [[maybe_unused]] auto x = store< neon< T > >( idx.data(), vindex );
         typename vector_constants_t< neon < T > > ::array_t res;
         for(
            std::size_t i = 0; i < vector_constants_t< neon < T > >::vector_element_count_t::value; ++i
            ) {
            res[ i ] = *( base + ( ( ( std::size_t ) idx[ i ] ) * Scale ) );
         }
         return load< neon< T > >( res.data( ) );
      }
   };
   
   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint8_t >::mask_t
   load_mask< neon < uint8_t > >(
      typename neon< uint8_t >::mask_t * const mask_ptr
   ) {
      return *mask_ptr;
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint16_t >::mask_t
   load_mask< neon < uint16_t > >(
      typename neon< uint16_t >::mask_t * const mask_ptr
   ) {
      return *mask_ptr;
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint32_t >::mask_t
   load_mask< neon < uint32_t > >(
      typename neon< uint32_t >::mask_t * const mask_ptr
   ) {
      return *mask_ptr;
   }

   template< >
   NO_DISCARD FORCE_INLINE
   typename neon< uint64_t >::mask_t
   load_mask< neon < uint64_t > >(
      typename neon< uint64_t >::mask_t * const mask_ptr
   ) {
      return *mask_ptr;
   }


   template< >
   FORCE_INLINE
   void
   store_mask< neon < uint8_t > >(
      typename neon< uint8_t >::mask_t * const mask_ptr,
      typename neon< uint8_t >::mask_t const mask
   ) {
      *mask_ptr = mask;
   }
   template< >
   FORCE_INLINE
   void
   store_mask< neon < uint16_t > >(
      typename neon< uint16_t >::mask_t * const mask_ptr,
      typename neon< uint16_t >::mask_t const mask
   ) {
      *mask_ptr = mask;
   }
   template< >
   FORCE_INLINE
   void
   store_mask< neon < uint32_t > >(
      typename neon< uint32_t >::mask_t * const mask_ptr,
      typename neon< uint32_t >::mask_t const mask
   ) {
      *mask_ptr = mask;
   }
   template< >
   FORCE_INLINE
   void
   store_mask< neon < uint64_t > >(
      typename neon< uint64_t >::mask_t * const mask_ptr,
      typename neon< uint64_t >::mask_t const mask
   ) {
      *mask_ptr = mask;
   }
}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_IO_NEON_H