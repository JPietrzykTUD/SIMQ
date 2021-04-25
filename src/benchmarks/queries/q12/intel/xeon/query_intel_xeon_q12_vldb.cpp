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
#ifndef EXPERIMENT_MEASUREMENT_REPETITION_COUNT
#define EXPERIMENT_MEASUREMENT_REPETITION_COUNT 1
#endif

//#include <iostream>
//#include <limits>
//#include <random>
//#include <bitset>



//#include <simq/control/bitmask/complex_bitmask.h>


#ifndef EXPERIMENT_MEASUREMENT_REPETITION_COUNT
#define EXPERIMENT_MEASUREMENT_REPETITION_COUNT 1
#endif
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstddef>
#include <chrono>
#include <ctime>

#include <simd/intrin.h>
#include <benchmarks/queries/q12/query12_simq.h>
#include <benchmarks/queries/q12/query12_seq.h>

#include <cstddef>
#include <chrono>
#include <ctime>

namespace global {
   std::ofstream outputfile;
}

template< class VectorExtension, std::size_t NumberOfBits, std::size_t BitPositionOffset >
void test( void ) {
   using  mask_t = typename VectorExtension::mask_t;
   mask_t test[ 10 ];
   std::mt19937 engine( 0xABABA );
   std::uniform_int_distribution <mask_t> dist( 0, std::numeric_limits< mask_t >::max( ) - 1 );
   
   
   for( int i = 0; i < 4; ++i ) {
      test[ i ] = dist( engine );
      std::cout << "[" << std::setw( 2 ) << i << "]: " << std::bitset < sizeof( mask_t ) * 8 > { test[ i ] } << "\n";
   }

   using f = tuddbs::complex_bitmask_helper_t< VectorExtension, NumberOfBits, BitPositionOffset >;

   auto[result, newpos] =
      f::read_mask_and_increment( test );
   std::cout << std::bitset < sizeof( mask_t ) * 8 > { result } << " . Pos-Delta = " << ( newpos - test ) << "\n";
   std::cout << "-------------\n";

}
int main( void ) {
   using namespace tuddbs;
   auto t = std::time(nullptr);
   auto tm = *std::localtime(&t);
   std::ostringstream oss;
   oss << "query_intel_xeon_q11_sample_run_" << std::put_time(&tm, "%Y_%m_%d_%H-%M") << ".csv";
   auto str = oss.str();
   std::cerr << "Executing Benchmark Query 1.1 on Xeon Gold.\n";
   std::cout << str.c_str() << "\n";
   global::outputfile.open(str.c_str());
   if(! global::outputfile.is_open()) {
      std::cerr << "Could not open for writing: " << str << "\n";
      return 1;
   }
   global::outputfile << get_definitions("#");
   q11_header( );
   
   datagenerator_q11< uint64_t, 1, 8 > * datagenerator =
      new datagenerator_q11< uint64_t, 1, 8 >( 512 );
   
   
//   simq_wl_q12_one_Stage2_ops< simq_vector_builder_buffer_t, avx512< uint64_t >, 8 >::run(
//      datagenerator );
//   seq_wl_q12_one_Stage2_ops< avx512< uint64_t >, 8 >::run(
//      datagenerator );
   
   std::cerr << "------ SIMQ ------\n";
   simq_wl_q12_two_Stage2_ops< simq_vector_builder_buffer_t, avx512< uint64_t >, 4,4 >::run(
      datagenerator );
   std::cerr << "------ SEQ ------\n";
   seq_wl_q12_two_Stage2_ops< avx512< uint64_t >, 4,4 >::run(
      datagenerator );
   
//   simq_wl_q12_three_Stage2_ops< simq_vector_builder_buffer_t, avx512< uint64_t >, 4,2,2 >::run(
//      datagenerator );
   
   
   global::outputfile.close();
   return 0;
}