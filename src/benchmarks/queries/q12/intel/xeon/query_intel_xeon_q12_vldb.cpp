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

template<
   class VectorExtension,
   std::size_t QueryCount2ndStageOp1,
   std::size_t QueryCount2ndStageOp2,
   std::size_t QueryCount2ndStageOp3
>
void print3( ) {
   std::cout
      << "\"VPM - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp1, 0 >::vecs_per_mask_t::value
      << ". INC - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp1, 0 >::incrementor_t::value << "\",";
   std::cout
      << "\"VPM - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp2, 0 >::vecs_per_mask_t::value
      << ". INC - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp2, 0 >::incrementor_t::value << "\",";
   std::cout
      << "\"VPM - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp3, 0 >::vecs_per_mask_t::value
      << ". INC - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp3, 0 >::incrementor_t::value << "\",";
}

template<
   class VectorExtension,
   std::size_t QueryCount2ndStageOp1,
   std::size_t QueryCount2ndStageOp2
>
void print2( ) {
   std::cout
      << "\"VPM - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp1, 0 >::vecs_per_mask_t::value
      << ". INC - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp1, 0 >::incrementor_t::value << "\",";
   std::cout
      << "\"VPM - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp2, 0 >::vecs_per_mask_t::value
      << ". INC - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp2, 0 >::incrementor_t::value << "\",";
}

template<
   class VectorExtension,
   std::size_t QueryCount2ndStageOp1
>
void print1( ) {
   std::cout
      << "\"VPM - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp1, 0 >::vecs_per_mask_t::value
      << ". INC - "
      << tuddbs::complex_bitmask_helper_t< VectorExtension, QueryCount2ndStageOp1, 0 >::incrementor_t::value << "\",";
}

void run_experiment( std::size_t data_size ) {
   using namespace tuddbs;
   datagenerator_q11< uint64_t, 1, 8 > * datagenerator =
      new datagenerator_q11< uint64_t, 1, 8 >( 128_MiB );
   
   
   
   delete datagenerator;
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
      new datagenerator_q11< uint64_t, 1, 8 >( 128_MiB );

   
//   simq_wl_q12_one_Stage2_ops< simq_vector_builder_buffer_t, avx512< uint64_t >, 8 >::run(
//      datagenerator );
//   seq_wl_q12_one_Stage2_ops< avx512< uint64_t >, 8 >::run(
//      datagenerator );

//   simq_wl_q12_two_Stage2_ops< simq_vector_builder_buffer_t, avx512< uint64_t >, 4,4 >::run(
//      datagenerator );
//   seq_wl_q12_two_Stage2_ops< avx512< uint64_t >, 4,4 >::run(
//      datagenerator );
   
   simq_wl_q12_three_Stage2_ops< simq_vector_builder_buffer_t, avx512< uint64_t >, 4,2,2 >::run(
      datagenerator );
   seq_wl_q12_three_Stage2_ops< avx512< uint64_t >, 4,2,2 >::run(
      datagenerator );
   
   
   global::outputfile.close();

/*
   std::cout << "[";
   print1< avx512< uint64_t >, 8 >();
   print2< avx512< uint64_t >, 4, 4 >();
   print3< avx512< uint64_t >, 4, 2, 2 >();
   
   print1< avx512< uint32_t >, 16 >();
   print2< avx512< uint32_t >, 8, 8 >();
   print3< avx512< uint32_t >, 8, 4, 4 >();
   
   print1< avx512< uint16_t >, 32 >();
   print2< avx512< uint16_t >, 16, 16 >();
   print3< avx512< uint16_t >, 16, 8, 8 >();
   
   print1< avx512< uint8_t >, 64 >();
   print2< avx512< uint8_t >, 32, 32 >();
   print3< avx512< uint8_t >, 32, 16, 16 >();
   
   print1< avx2< uint64_t >, 4 >();
   print2< avx2< uint64_t >, 2, 2 >();
   print3< avx2< uint64_t >, 2, 1, 1 >();
   
   print1< avx2< uint32_t >, 8 >();
   print2< avx2< uint32_t >, 4, 4 >();
   print3< avx2< uint32_t >, 4, 2, 2 >();
   
   print1< avx2< uint16_t >, 16 >();
   print2< avx2< uint16_t >, 8, 8 >();
   print3< avx2< uint16_t >, 8, 4, 4 >();
   
   print1< avx2< uint8_t >, 32 >();
   print2< avx2< uint8_t >, 16, 16 >();
   print3< avx2< uint8_t >, 16, 8, 8 >();
   
   print1< sse< uint64_t >, 2 >();
   print2< sse< uint64_t >, 1, 1 >();
   
   print1< sse< uint32_t >, 4 >();
   print2< sse< uint32_t >, 2, 2 >();
   print3< sse< uint32_t >, 2, 1, 1 >();
   
   print1< sse< uint16_t >, 8 >();
   print2< sse< uint16_t >, 4, 4 >();
   print3< sse< uint16_t >, 4, 2, 2 >();
   
   print1< sse< uint8_t >, 16 >();
   print2< sse< uint8_t >, 8, 8 >();
   print3< sse< uint8_t >, 8, 4, 4 >();
   std::cout << "]\n";
*/
   
   return 0;
}