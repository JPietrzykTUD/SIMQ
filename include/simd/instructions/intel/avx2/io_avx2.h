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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_IO_AVX2_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_IO_AVX2_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx2.h>
#include <simd/instructions/declarations/io.h>

#include <cstdint>
#include <tuple>

namespace tuddbs {
   
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx2< uint8_t >::vector_t
              load< avx2 < uint8_t >
   >(
   typename avx2< uint8_t >::base_t * const a
   ) {
   return _mm256_load_si256( reinterpret_cast< __m256i const * >( a ) );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx2< uint16_t >::vector_t
           load< avx2 < uint16_t >
>(
typename avx2< uint16_t >::base_t * const a
) {
return _mm256_load_si256( reinterpret_cast< __m256i const * >( a ) );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx2< uint32_t >::vector_t
           load< avx2 < uint32_t >
>(
typename avx2< uint32_t >::base_t * const a
) {
return _mm256_load_si256( reinterpret_cast< __m256i const * >( a ) );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx2< uint64_t >::vector_t
           load< avx2 < uint64_t >
>(
typename avx2< uint64_t >::base_t * const a
) {
return _mm256_load_si256( reinterpret_cast< __m256i const * >( a ) );
}

template< >
NO_DISCARD                       FORCE_INLINE
typename avx2< uint8_t >::base_t *
                                    store< avx2 < uint8_t >
>(
typename avx2< uint8_t >::base_t * const target,
typename avx2< uint8_t >::vector_t const a
) {
_mm256_store_si256( reinterpret_cast< __m256i * >( target ), a );
return ( target + vector_constants_t< avx2 < uint8_t > >::vector_element_count_t::value );
}

template< >
NO_DISCARD                        FORCE_INLINE
typename avx2< uint16_t >::base_t *
                                     store< avx2 < uint16_t >
>(
typename avx2< uint16_t >::base_t * const target,
typename avx2< uint16_t >::vector_t const a
) {
_mm256_store_si256( reinterpret_cast< __m256i * >( target ), a );
return ( target + vector_constants_t< avx2 < uint16_t > >::vector_element_count_t::value );
}

template< >
NO_DISCARD                        FORCE_INLINE
typename avx2< uint32_t >::base_t *
                                     store< avx2 < uint32_t >
>(
typename avx2< uint32_t >::base_t * const target,
typename avx2< uint32_t >::vector_t const a
) {
_mm256_store_si256( reinterpret_cast< __m256i * >( target ), a );
return ( target + vector_constants_t< avx2 < uint32_t > >::vector_element_count_t::value );
}

template< >
NO_DISCARD                        FORCE_INLINE
typename avx2< uint64_t >::base_t *
                                     store< avx2 < uint64_t >
>(
typename avx2< uint64_t >::base_t * const target,
typename avx2< uint64_t >::vector_t const a
) {
_mm256_store_si256( reinterpret_cast< __m256i * >( target ), a );
return ( target + vector_constants_t< avx2 < uint64_t > >::vector_element_count_t::value );
}

/*   template< typename T >
   struct store_impl< avx2< T > > {
      NO_DISCARD FORCE_INLINE
      static
      typename avx2< T >::base_t *
      apply(
         typename avx2< T >::base_t * const target,
         typename avx2< T >::vector_t const a
      ) {
         _mm256_store_si256( reinterpret_cast< __m256i * >( target ), a );
         return ( target + vector_constants_t< avx2< T > >::vector_element_count_t::value );
      }
   };
*/
template< typename T >
struct stream_store_impl< avx2 < T > > {
NO_DISCARD FORCE_INLINE

static
typename avx2< T >::base_t *
apply(
   typename avx2< T >::base_t * const target,
   typename avx2< T >::vector_t const a
) {
   _mm256_stream_si256( reinterpret_cast< __m256i * >( target ), a );
   return ( target + vector_constants_t < avx2 < T > > ::vector_element_count_t::value );
}

};



template< std::size_t Scale >
struct gather_impl< avx2 < uint8_t >, Scale > {
NO_DISCARD FORCE_INLINE

typename avx2< uint8_t >::vector_t
static apply(
   typename avx2< uint8_t >::vector_t const vindex,
   typename avx2< uint8_t >::base_t * const base
) {
   typename vector_constants_t< avx2 < uint8_t > > ::array_t
   tmp;
   _mm256_store_si256( reinterpret_cast< __m256i * >( tmp.data( ) ), vindex );
   for(
      std::size_t i = 0; i < vector_constants_t < avx2 < uint8_t > > ::vector_element_count_t::value; ++i
      ) {
      tmp[ i ] = *( base + ( tmp[ i ] * Scale ) );
   }
   return _mm256_load_si256( reinterpret_cast< __m256i const * >( tmp.data( ) ) );
}

};
template< std::size_t Scale >
struct gather_impl< avx2 < uint16_t >, Scale > {
NO_DISCARD FORCE_INLINE

typename avx2< uint16_t >::vector_t
static apply(
   typename avx2< uint16_t >::vector_t const vindex,
   typename avx2< uint16_t >::base_t * const base
) {
   typename vector_constants_t< avx2 < uint16_t > > ::array_t
   tmp;
   _mm256_store_si256( reinterpret_cast< __m256i * >( tmp.data( ) ), vindex );
   for(
      std::size_t i = 0; i < vector_constants_t < avx2 < uint16_t > > ::vector_element_count_t::value; ++i
      ) {
      tmp[ i ] = *( base + ( tmp[ i ] * Scale ) );
   }
   return _mm256_load_si256( reinterpret_cast< __m256i const * >( tmp.data( ) ) );
}

};
template< std::size_t Scale >
struct gather_impl< avx2 < uint32_t >, Scale > {
NO_DISCARD FORCE_INLINE

typename avx2< uint32_t >::vector_t
static apply(
   typename avx2< uint32_t >::vector_t const vindex,
   typename avx2< uint32_t >::base_t * const base
) {
   return _mm256_i32gather_epi32( reinterpret_cast< int const * >( base ), vindex, Scale );
}

};
template< std::size_t Scale >
struct gather_impl< avx2 < uint64_t >, Scale > {
NO_DISCARD FORCE_INLINE

typename avx2< uint64_t >::vector_t
static apply(
   typename avx2< uint64_t >::vector_t const vindex,
   typename avx2< uint64_t >::base_t * const base
) {
   return _mm256_i64gather_epi64( reinterpret_cast< long long int const * >( base ), vindex, Scale );
}

};

template< >
NO_DISCARD FORCE_INLINE
typename avx2< uint8_t >::mask_t
           load_mask< avx2 < uint8_t >
>(
typename avx2< uint8_t >::mask_t * const mask_ptr
) {
return *
mask_ptr;
}

template< >
NO_DISCARD FORCE_INLINE
typename avx2< uint16_t >::mask_t
           load_mask< avx2 < uint16_t >
>(
typename avx2< uint16_t >::mask_t * const mask_ptr
) {
return *
mask_ptr;
}

template< >
NO_DISCARD FORCE_INLINE
typename avx2< uint32_t >::mask_t
           load_mask< avx2 < uint32_t >
>(
typename avx2< uint32_t >::mask_t * const mask_ptr
) {
return *
mask_ptr;
}

template< >
NO_DISCARD FORCE_INLINE
typename avx2< uint64_t >::mask_t
           load_mask< avx2 < uint64_t >
>(
typename avx2< uint64_t >::mask_t * const mask_ptr
) {
return *
mask_ptr;
}

template< >
FORCE_INLINE
void
   store_mask< avx2 < uint8_t >
>(
typename avx2< uint8_t >::mask_t * const mask_ptr,
typename avx2< uint8_t >::mask_t const mask
) {
*
mask_ptr = mask;
}

template< >
FORCE_INLINE
void
   store_mask< avx2 < uint16_t >
>(
typename avx2< uint16_t >::mask_t * const mask_ptr,
typename avx2< uint16_t >::mask_t const mask
) {
*
mask_ptr = mask;
}

template< >
FORCE_INLINE
void
   store_mask< avx2 < uint32_t >
>(
typename avx2< uint32_t >::mask_t * const mask_ptr,
typename avx2< uint32_t >::mask_t const mask
) {
*
mask_ptr = mask;
}

template< >
FORCE_INLINE
void
   store_mask< avx2 < uint64_t >
>(
typename avx2< uint64_t >::mask_t * const mask_ptr,
typename avx2< uint64_t >::mask_t const mask
) {
*
mask_ptr = mask;
}




}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX2_IO_AVX2_H
