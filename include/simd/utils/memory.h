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
#ifndef TUDDBS_SIMQ_INCLUDE_SIMD_UTILS_MEMORY_H
#define TUDDBS_SIMQ_INCLUDE_SIMD_UTILS_MEMORY_H

#ifdef INTEL_SIMDI

#define SIMD_MALLOC(size) _mm_malloc(size, 64)
#define SIMD_FREE(ptr) _mm_free(ptr)

#elif defined(ARM_SIMDI)

#define SIMD_MALLOC(size) malloc(size)
#define SIMD_FREE(ptr) free(ptr)

#endif

#endif //TUDDBS_SIMQ_INCLUDE_SIMD_UTILS_MEMORY_H
