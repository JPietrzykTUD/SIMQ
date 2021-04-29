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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_IO_AVX512_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_IO_AVX512_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/avx512.h>
#include <simd/instructions/declarations/io.h>

#include <cstdint>
#include <tuple>

namespace tuddbs {
   
   template< >
   NO_DISCARD FORCE_INLINE
   typename avx512< uint8_t >::vector_t
              load< avx512 < uint8_t >
   >(
   typename avx512< uint8_t >::base_t * const a
   ) {
   return _mm512_load_si512( reinterpret_cast
   < void const * >( a )
   );
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::vector_t
           load< avx512 < uint16_t >
>(
typename avx512< uint16_t >::base_t * const a
) {
return _mm512_load_si512( reinterpret_cast
< void const * >( a )
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::vector_t
           load< avx512 < uint32_t >
>(
typename avx512< uint32_t >::base_t * const a
) {
return _mm512_load_si512( reinterpret_cast
< void const * >( a )
);
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::vector_t
           load< avx512 < uint64_t >
>(
typename avx512< uint64_t >::base_t * const a
) {
return _mm512_load_si512( reinterpret_cast
< void const * >( a )
);
}

template< >
NO_DISCARD                         FORCE_INLINE
typename avx512< uint8_t >::base_t *
                                      store< avx512 < uint8_t >
>(
typename avx512< uint8_t >::base_t * const target,
typename avx512< uint8_t >::vector_t const a
) {
_mm512_store_si512( reinterpret_cast
< void * >( target ), a
);
return ( target + vector_constants_t< avx512 < uint8_t > >::vector_element_count_t::value );
}

template< >
NO_DISCARD                          FORCE_INLINE
typename avx512< uint16_t >::base_t *
                                       store< avx512 < uint16_t >
>(
typename avx512< uint16_t >::base_t * const target,
typename avx512< uint16_t >::vector_t const a
) {
_mm512_store_si512( reinterpret_cast
< void * >( target ), a
);
return ( target + vector_constants_t< avx512 < uint16_t > >::vector_element_count_t::value );
}

template< >
NO_DISCARD                          FORCE_INLINE
typename avx512< uint32_t >::base_t *
                                       store< avx512 < uint32_t >
>(
typename avx512< uint32_t >::base_t * const target,
typename avx512< uint32_t >::vector_t const a
) {
_mm512_store_si512( reinterpret_cast
< void * >( target ), a
);
return ( target + vector_constants_t< avx512 < uint32_t > >::vector_element_count_t::value );
}

template< >
NO_DISCARD                          FORCE_INLINE
typename avx512< uint64_t >::base_t *
                                       store< avx512 < uint64_t >
>(
typename avx512< uint64_t >::base_t * const target,
typename avx512< uint64_t >::vector_t const a
) {
_mm512_store_si512( reinterpret_cast
< void * >( target ), a
);
return ( target + vector_constants_t< avx512 < uint64_t > >::vector_element_count_t::value );
}

/*   template< typename T >
   struct store_impl< avx512< T > > {
      NO_DISCARD FORCE_INLINE
      static
      typename avx512< T >::base_t *
      apply(
         typename avx512< T >::base_t * const target,
         typename avx512< T >::vector_t const a
      ) {
         _mm512_store_si512( reinterpret_cast< void * >( target ), a );
         return ( target + vector_constants_t< avx512< T > >::vector_element_count_t::value );
      }
   };
*/
template< typename T >
struct stream_store_impl< avx512 < T > > {
NO_DISCARD FORCE_INLINE

static
typename avx512< T >::base_t *
apply(
   typename avx512< T >::base_t * const target,
   typename avx512< T >::vector_t const a
) {
   _mm512_stream_si512( reinterpret_cast< typename avx512< T >::vector_t * >( target ), a );
   return ( target + vector_constants_t < avx512 < T > > ::vector_element_count_t::value );
}

};

template< std::size_t Scale >
struct gather_impl< avx512 < uint8_t >, Scale > {
NO_DISCARD FORCE_INLINE

typename avx512< uint8_t >::vector_t
static apply(
   typename avx512< uint8_t >::vector_t const vindex,
   typename avx512< uint8_t >::base_t * const base
) {
   typename vector_constants_t< avx512 < uint8_t > > ::array_t
   tmp;
   _mm512_store_si512( reinterpret_cast< void * >( tmp.data( ) ), vindex );
   for(
      std::size_t i = 0; i < vector_constants_t < avx512 < uint8_t > > ::vector_element_count_t::value; ++i
      ) {
      tmp[ i ] = *( base + ( tmp[ i ] * Scale ) );
   }
   return _mm512_load_si512( reinterpret_cast< void const * >( tmp.data( ) ) );
}

};
template< std::size_t Scale >
struct gather_impl< avx512 < uint16_t >, Scale > {
NO_DISCARD FORCE_INLINE

typename avx512< uint16_t >::vector_t
static apply(
   typename avx512< uint16_t >::vector_t const vindex,
   typename avx512< uint16_t >::base_t * const base
) {
   typename vector_constants_t< avx512 < uint16_t > > ::array_t
   tmp;
   _mm512_store_si512( reinterpret_cast< void * >( tmp.data( ) ), vindex );
   for(
      std::size_t i = 0; i < vector_constants_t < avx512 < uint16_t > > ::vector_element_count_t::value; ++i
      ) {
      tmp[ i ] = *( base + ( tmp[ i ] * Scale ) );
   }
   return _mm512_load_si512( reinterpret_cast< void const * >( tmp.data( ) ) );
}

};
template< std::size_t Scale >
struct gather_impl< avx512 < uint32_t >, Scale > {
NO_DISCARD FORCE_INLINE

typename avx512< uint32_t >::vector_t
static apply(
   typename avx512< uint32_t >::vector_t const vindex,
   typename avx512< uint32_t >::base_t * const base
) {
   return _mm512_i32gather_epi32( vindex, reinterpret_cast< void const * >( base ), Scale );
}

};
template< std::size_t Scale >
struct gather_impl< avx512 < uint64_t >, Scale > {
NO_DISCARD FORCE_INLINE

typename avx512< uint64_t >::vector_t
static apply(
   typename avx512< uint64_t >::vector_t const vindex,
   typename avx512< uint64_t >::base_t * const base
) {
   return _mm512_i64gather_epi64( vindex, reinterpret_cast< void const * >( base ), Scale );
}

};

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint8_t >::mask_t
           load_mask< avx512 < uint8_t >
>(
typename avx512< uint8_t >::mask_t * const mask_ptr
) {
return *
mask_ptr;
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint16_t >::mask_t
           load_mask< avx512 < uint16_t >
>(
typename avx512< uint16_t >::mask_t * const mask_ptr
) {
return *
mask_ptr;
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint32_t >::mask_t
           load_mask< avx512 < uint32_t >
>(
typename avx512< uint32_t >::mask_t * const mask_ptr
) {
return *
mask_ptr;
}

template< >
NO_DISCARD FORCE_INLINE
typename avx512< uint64_t >::mask_t
           load_mask< avx512 < uint64_t >
>(
typename avx512< uint64_t >::mask_t * const mask_ptr
) {
return *
mask_ptr;
}

template< >
FORCE_INLINE
void
   store_mask< avx512 < uint8_t >
>(
typename avx512< uint8_t >::mask_t * const mask_ptr,
typename avx512< uint8_t >::mask_t const mask
) {
*
mask_ptr = mask;
}

template< >
FORCE_INLINE
void
   store_mask< avx512 < uint16_t >
>(
typename avx512< uint16_t >::mask_t * const mask_ptr,
typename avx512< uint16_t >::mask_t const mask
) {
*
mask_ptr = mask;
}

template< >
FORCE_INLINE
void
   store_mask< avx512 < uint32_t >
>(
typename avx512< uint32_t >::mask_t * const mask_ptr,
typename avx512< uint32_t >::mask_t const mask
) {
*
mask_ptr = mask;
}

template< >
FORCE_INLINE
void
   store_mask< avx512 < uint64_t >
>(
typename avx512< uint64_t >::mask_t * const mask_ptr,
typename avx512< uint64_t >::mask_t const mask
) {
*
mask_ptr = mask;
}




}

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_INTEL_AVX512_IO_AVX512_H
