/* 
 * This file is part of the SIMQ Project (https://github.com/JPietrzykTUD/SIMQ).
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
#ifndef TUDDBS_SIMQ_INCLUDE_UTILS_RANDOM_H
#define TUDDBS_SIMQ_INCLUDE_UTILS_RANDOM_H

#include <random>

namespace tuddbs {
   template< typename T >
   struct rng {
      using engine_t =
      typename std::conditional<
         sizeof( T ) == 8,
         std::mt19937_64,
         std::mt19937
      >::type;
   };
}

#endif //TUDDBS_SIMQ_INCLUDE_UTILS_RANDOM_H
