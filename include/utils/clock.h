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
#ifndef TUDDBS_SIMQ_INCLUDE_UTILS_CLOCK_H
#define TUDDBS_SIMQ_INCLUDE_UTILS_CLOCK_H

#ifdef INTEL_SIMDI
#include <chrono>
#elif defined(NEC_SIMDI)
#include <cstdint>
#endif

namespace tuddbs {
#ifdef INTEL_SIMDI
   static inline std::chrono::time_point< std::chrono::high_resolution_clock > now() {
      return std::chrono::high_resolution_clock::now();
   }
   static inline double time_elapsed_ms( std::chrono::time_point< std::chrono::high_resolution_clock > start, std::chrono::time_point< std::chrono::high_resolution_clock > end ) {
      return std::chrono::duration_cast< std::chrono::microseconds >( end - start ).count();
   }
   static inline double time_elapsed_ns( std::chrono::time_point< std::chrono::high_resolution_clock > start, std::chrono::time_point< std::chrono::high_resolution_clock > end ) {
      return std::chrono::duration_cast< std::chrono::nanoseconds >( end - start ).count();
   }
#endif
}

#endif //TUDDBS_SIMQ_INCLUDE_UTILS_CLOCK_H
