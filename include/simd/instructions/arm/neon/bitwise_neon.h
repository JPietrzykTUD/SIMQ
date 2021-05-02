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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_BITWISE_NEON_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INSTRUCTIONS_ARM_NEON_BITWISE_NEON_H

#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/arm/neon.h>
#include <simd/instructions/declarations/bitwise.h>

#include <cstdint>

namespace tuddbs {
   template< >
   struct bitwise_xor_t< uint64_t, neon < uint64_t > > {
   NO_DISCARD FORCE_INLINE
   
   static
   typename neon< uint64_t >::vector_t
   apply(
      typename neon< uint64_t >::vector_t const a,
      typename neon< uint64_t >::vector_t const b
   ) {
      return veorq_u64( a, b );
   }
};
template< >
struct bitwise_xor_t< uint32_t, neon < uint32_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint32_t >::vector_t
apply(
   typename neon< uint32_t >::vector_t const a,
   typename neon< uint32_t >::vector_t const b
) {
   return veorq_u32( a, b );
}

};
template< >
struct bitwise_xor_t< uint16_t, neon < uint16_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint16_t >::vector_t
apply(
   typename neon< uint16_t >::vector_t const a,
   typename neon< uint16_t >::vector_t const b
) {
   return veorq_u16( a, b );
}

};
template< >
struct bitwise_xor_t< uint8_t, neon < uint8_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint8_t >::vector_t
apply(
   typename neon< uint8_t >::vector_t const a,
   typename neon< uint8_t >::vector_t const b
) {
   return veorq_u8( a, b );
}

};

template< >
struct bitwise_or_t< uint64_t, neon < uint64_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint64_t >::vector_t
apply(
   typename neon< uint64_t >::vector_t const a,
   typename neon< uint64_t >::vector_t const b
) {
   return vorrq_u64( a, b );
}

};
template< >
struct bitwise_or_t< uint32_t, neon < uint32_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint32_t >::vector_t
apply(
   typename neon< uint32_t >::vector_t const a,
   typename neon< uint32_t >::vector_t const b
) {
   return vorrq_u32( a, b );
}

};
template< >
struct bitwise_or_t< uint16_t, neon < uint16_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint16_t >::vector_t
apply(
   typename neon< uint16_t >::vector_t const a,
   typename neon< uint16_t >::vector_t const b
) {
   return vorrq_u16( a, b );
}

};
template< >
struct bitwise_or_t< uint8_t, neon < uint8_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint8_t >::vector_t
apply(
   typename neon< uint8_t >::vector_t const a,
   typename neon< uint8_t >::vector_t const b
) {
   return vorrq_u8( a, b );
}

};


template< >
struct bitwise_and_t< uint64_t, neon < uint64_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint64_t >::vector_t
apply(
   typename neon< uint64_t >::vector_t const a,
   typename neon< uint64_t >::vector_t const b
) {
   return vandq_u64( a, b );
}

};
template< >
struct bitwise_and_t< uint32_t, neon < uint32_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint32_t >::vector_t
apply(
   typename neon< uint32_t >::vector_t const a,
   typename neon< uint32_t >::vector_t const b
) {
   return vandq_u32( a, b );
}

};
template< >
struct bitwise_and_t< uint16_t, neon < uint16_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint16_t >::vector_t
apply(
   typename neon< uint16_t >::vector_t const a,
   typename neon< uint16_t >::vector_t const b
) {
   return vandq_u16( a, b );
}

};
template< >
struct bitwise_and_t< uint8_t, neon < uint8_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint8_t >::vector_t
apply(
   typename neon< uint8_t >::vector_t const a,
   typename neon< uint8_t >::vector_t const b
) {
   return vandq_u8( a, b );
}

};

template< >
struct bitwise_and_not_t< uint64_t, neon < uint64_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint64_t >::vector_t
apply(
   typename neon< uint64_t >::vector_t const a,
   typename neon< uint64_t >::vector_t const b
) {
   return vbicq_u64( b, a );
}

};
template< >
struct bitwise_and_not_t< uint32_t, neon < uint32_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint32_t >::vector_t
apply(
   typename neon< uint32_t >::vector_t const a,
   typename neon< uint32_t >::vector_t const b
) {
   return vbicq_u32( b, a );
}

};
template< >
struct bitwise_and_not_t< uint16_t, neon < uint16_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint16_t >::vector_t
apply(
   typename neon< uint16_t >::vector_t const a,
   typename neon< uint16_t >::vector_t const b
) {
   return vbicq_u16( b, a );
}

};
template< >
struct bitwise_and_not_t< uint8_t, neon < uint8_t > > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint8_t >::vector_t
apply(
   typename neon< uint8_t >::vector_t const a,
   typename neon< uint8_t >::vector_t const b
) {
   return vbicq_u8( b, a );
}

};



//use this with care!
template< int I >
struct bitshift_left_t< neon < uint64_t >, I > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint64_t >::vector_t
apply(
   typename neon< uint64_t >::vector_t const a
) {
   return vshlq_n_u64( a, I );
}

};
//use this with care!
template< int I >
struct bitshift_left_t< neon < uint32_t >, I > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint32_t >::vector_t
apply(
   typename neon< uint32_t >::vector_t const a
) {
   return vshlq_n_u32( a, I );
}

};
//use this with care!
template< int I >
struct bitshift_left_t< neon < uint16_t >, I > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint16_t >::vector_t
apply(
   typename neon< uint16_t >::vector_t const a
) {
   return vshlq_n_u16( a, I );
}

};
//use this with care!
template< int I >
struct bitshift_left_t< neon < uint8_t >, I > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint8_t >::vector_t
apply(
   typename neon< uint8_t >::vector_t const a
) {
   return vshlq_n_u8( a, I );
}

};

//use this with care!
template< int I >
struct bitshift_right_t< neon < uint64_t >, I > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint64_t >::vector_t
apply(
   typename neon< uint64_t >::vector_t const a
) {
   return vshrq_n_u64( a, I );
}

};
//use this with care!
template< int I >
struct bitshift_right_t< neon < uint32_t >, I > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint32_t >::vector_t
apply(
   typename neon< uint32_t >::vector_t const a
) {
   return vshrq_n_u32( a, I );
}

};
//use this with care!
template< int I >
struct bitshift_right_t< neon < uint16_t >, I > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint16_t >::vector_t
apply(
   typename neon< uint16_t >::vector_t const a
) {
   return vshrq_n_u16( a, I );
}

};
//use this with care!
template< int I >
struct bitshift_right_t< neon < uint8_t >, I > {
NO_DISCARD FORCE_INLINE

static
typename neon< uint8_t >::vector_t
apply(
   typename neon< uint8_t >::vector_t const a
) {
   return vshrq_n_u8( a, I );
}

};
}

#endif