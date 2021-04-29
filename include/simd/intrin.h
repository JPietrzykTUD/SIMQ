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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_INTRIN_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_INTRIN_H

#ifdef INTEL_SIMDI
#  include <immintrin.h>
#endif

//TYPES
#include <simd/types/simd.h>

#ifdef INTEL_SIMDI
#  include <simd/types/intel/sse.h>
#  include <simd/types/intel/avx2.h>
#  include <simd/types/intel/avx512.h>
#endif
//Functions
#include <simd/instructions/declarations/misc.h>
#include <simd/instructions/declarations/create.h>
#include <simd/instructions/declarations/io.h>
#include <simd/instructions/declarations/compare.h>
#include <simd/instructions/declarations/math.h>
#include <simd/instructions/declarations/bitwise.h>
//Implementations
#ifdef INTEL_SIMDI
#  include <simd/instructions/intel/sse/misc_sse.h>
#  include <simd/instructions/intel/sse/create_sse.h>
#  include <simd/instructions/intel/sse/io_sse.h>
#  include <simd/instructions/intel/sse/compare_sse.h>
#  include <simd/instructions/intel/sse/math_sse.h>
#  include <simd/instructions/intel/sse/bitwise_sse.h>
#  include <simd/instructions/intel/avx2/misc_avx2.h>
#  include <simd/instructions/intel/avx2/create_avx2.h>
#  include <simd/instructions/intel/avx2/io_avx2.h>
#  include <simd/instructions/intel/avx2/compare_avx2.h>
#  include <simd/instructions/intel/avx2/math_avx2.h>
#  include <simd/instructions/intel/avx2/bitwise_avx2.h>
#  include <simd/instructions/intel/avx512/misc_avx512.h>
#  include <simd/instructions/intel/avx512/create_avx512.h>
#  include <simd/instructions/intel/avx512/io_avx512.h>
#  include <simd/instructions/intel/avx512/compare_avx512.h>
#  include <simd/instructions/intel/avx512/math_avx512.h>
#  include <simd/instructions/intel/avx512/bitwise_avx512.h>
//Generated Implementations
#  include <generated/simd/instructions/intel/sse/create_sse.h>
#  include <generated/simd/instructions/intel/avx2/create_avx2.h>
#  include <generated/simd/instructions/intel/avx512/create_avx512.h>
#  include <simd/utils/print.h>
#endif

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_INTRIN_H
