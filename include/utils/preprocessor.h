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
#ifndef TUDDBS_SIMQ_INCLUDE_UTILS_PREPROCESSOR_H
#define TUDDBS_SIMQ_INCLUDE_UTILS_PREPROCESSOR_H

#ifndef FORCE_INLINE
#  define FORCE_INLINE inline __attribute__((always_inline))
#endif

#ifndef NO_DISCARD
#  ifdef C17
#     define NO_DISCARD [[nodiscard]]
#  else
#     define NO_DISCARD
#  endif
#endif

#endif //TUDDBS_SIMQ_INCLUDE_UTILS_PREPROCESSOR_H
