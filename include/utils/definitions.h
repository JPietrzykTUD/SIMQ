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
#ifndef TUDDBS_SIMQ_INCLUDE_UTILS_DEFINITIONS_H
#define TUDDBS_SIMQ_INCLUDE_UTILS_DEFINITIONS_H

#include <string>
#ifndef GIT_REMOTE_URL
#define GIT_REMOTE_URL ""
#endif
#ifndef GIT_BRANCH_CMAKE
#define GIT_BRANCH_CMAKE ""
#endif
#ifndef GIT_COMMIT_ABBREV_HASH_CMAKE
#define GIT_COMMIT_ABBREV_HASH_CMAKE ""
#endif
#ifndef GIT_COMMIT_HASH_CMAKE
#define GIT_COMMIT_HASH_CMAKE ""
#endif
#ifndef BUILD_UNAME_CMAKE
#define BUILD_UNAME_CMAKE ""
#endif
#ifndef PROCESSOR_NAME
#define PROCESSOR_NAME ""
#endif
#ifndef L1D
#define L1D ""
#endif
#ifndef L2
#define L2 ""
#endif
#ifndef L3
#define L3 ""
#endif
#ifndef BUILD_HOSTNAME_CMAKE
#define BUILD_HOSTNAME_CMAKE ""
#endif
#ifndef BUILD_COMPILER_NAME_CMAKE
#define BUILD_COMPILER_NAME_CMAKE ""
#endif
#ifndef BUILD_COMPILER_VERSION_CMAKE
#define BUILD_COMPILER_VERSION_CMAKE ""
#endif
#ifndef BUILD_COMPILER_PATH_CMAKE
#define BUILD_COMPILER_PATH_CMAKE ""
#endif
#ifndef BUILD_TIME_CMAKE
#define BUILD_TIME_CMAKE ""
#endif
#ifndef COMPILE_OPTIONS
#define COMPILE_OPTIONS ""
#endif
#ifndef COMPILE_DEFINITIONS
#define COMPILE_DEFINITIONS ""
#endif

std::string get_definitions( std::string prefix ) {
   std::string result = "";
   result += prefix + "Git Repository: " + std::string(GIT_REMOTE_URL) + "\n";
   result += prefix + "Git Branch:     " + std::string(GIT_BRANCH_CMAKE) + "\n";
   result += prefix + "Git Commit:     " + std::string(GIT_COMMIT_ABBREV_HASH_CMAKE) + "(" + std::string( GIT_COMMIT_HASH_CMAKE ) + ")" + "\n";
   result += prefix + "\n";
   result += prefix + "System:         " + std::string(BUILD_UNAME_CMAKE) + "\n";
   result += prefix + "Processor:      " + std::string(PROCESSOR_NAME) + "\n";
   result += prefix + "L1D | L2 | L3:  " + std::string(L1D) + " | " + std::string(L2) + " | " + std::string(L3) + "\n";
   result += prefix + "Hostname:       " + std::string(BUILD_HOSTNAME_CMAKE) + "\n";
   result += prefix + "\n";
   result += prefix + "Compiler:       " + std::string(BUILD_COMPILER_NAME_CMAKE);
   result += "( v. " + std::string(BUILD_COMPILER_VERSION_CMAKE) + " ). Path: " + std::string(BUILD_COMPILER_PATH_CMAKE) + "\n";
   result += prefix + "Build-Time:     " + std::string(BUILD_TIME_CMAKE) + "\n";
   result += prefix + "Compile-Flags:  " + std::string(COMPILE_OPTIONS) + " ( " + std::string(COMPILE_DEFINITIONS) + " )\n";

   return result;
}

namespace tuddbs {
   constexpr std::size_t operator"" _MiB( unsigned long long int bytes ) {
      return bytes * 1024 * 1024;
   }
   constexpr std::size_t operator"" _GiB( unsigned long long int bytes ) {
      return bytes * 1024 * 1024 * 1024;
   }
   constexpr std::size_t operator"" _KiB( unsigned long long int bytes ) {
      return bytes * 1024;
   }
}

#endif //TUDDBS_SIMQ_INCLUDE_UTILS_DEFINITIONS_H
