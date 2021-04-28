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

template<
   class VectorExtension,
   std::size_t QueryCount,
   std::size_t ColumnCount = 1
>
struct simq_query_distr_helper_1stage_t {
   template<template< class, std::size_t, typename, class > class Strategy>
   using simq_t    = tuddbs::simq_wl_q12_one_Stage2_ops< Strategy, VectorExtension, QueryCount, ColumnCount >;
   using seq_t     = tuddbs::seq_wl_q12_one_Stage2_ops< VectorExtension, QueryCount, ColumnCount >;
};
template<
   class VectorExtension,
   std::size_t QueryCount,
   std::size_t ColumnCount = 1
>
struct simq_query_distr_helper_2stages_t {
   using colcount2ndstage_op1 =
   std::conditional_t<
      ( ColumnCount == 1 ),
      std::integral_constant< std::size_t, 1 >,
      std::integral_constant< std::size_t, (ColumnCount>>1) >
   >;
   template<template< class, std::size_t, typename, class > class Strategy>
   using simq_t    = tuddbs::simq_wl_q12_two_Stage2_ops<
      Strategy, VectorExtension, (QueryCount>>1), (QueryCount>>1),
      ColumnCount, colcount2ndstage_op1::value
   >;
   using seq_t     = tuddbs::seq_wl_q12_two_Stage2_ops<
      VectorExtension, ( QueryCount>>1 ), ( QueryCount>>1 ), ColumnCount, colcount2ndstage_op1::value
   >;
};
template<
   class VectorExtension,
   std::size_t QueryCount,
   std::size_t ColumnCount = 1
>
struct simq_query_distr_helper_3stages_t {
   
   using colcount2ndstage_op1 =
      std::conditional_t<
      ( ( ColumnCount == 1 ) || ( ColumnCount == 2 ) ),
         std::integral_constant< std::size_t, 1 >,
         std::integral_constant< std::size_t, (ColumnCount>>1) >
      >;
   using colcount2ndstage_op2 =
   std::conditional_t<
      ( ( ColumnCount == 1 ) || ( ColumnCount == 2 ) ),
      std::integral_constant< std::size_t, 1 >,
      std::integral_constant< std::size_t, (ColumnCount>>2) >
   >;
   template<template< class, std::size_t, typename, class > class Strategy>
   using simq_t  = tuddbs::simq_wl_q12_three_Stage2_ops<
      Strategy, VectorExtension, ( QueryCount>>1 ), ( QueryCount>>2 ), ( QueryCount>>2 ), ColumnCount,
      colcount2ndstage_op1::value, colcount2ndstage_op2::value
   >;
   using seq_t   = tuddbs::seq_wl_q12_three_Stage2_ops<
      VectorExtension, ( QueryCount>>1 ), ( QueryCount>>2 ), ( QueryCount>>2 ), ColumnCount,
      colcount2ndstage_op1::value, colcount2ndstage_op2::value
   >;
};



template<
   class VectorExtension,
   std::size_t ColumnCount,
   std::size_t QueryCount
>
void run_build_variants(
   std::size_t data_size
) {
   using namespace tuddbs;
   std::cerr << "   " << vec_ext_to_string_t< VectorExtension >::apply( )
             << ". Queries: " << QueryCount << ". Columns: " << ColumnCount << "\n";
   
   datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * datagenerator =
      new datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount >( data_size );
   
   using helper_1stage = simq_query_distr_helper_1stage_t< VectorExtension, QueryCount, ColumnCount >;
   helper_1stage::seq_t::run( datagenerator );
   helper_1stage::template simq_t< simq_vector_builder_buffer_t >::run( datagenerator );
   helper_1stage::template simq_t< simq_vector_builder_mask_broadcast_t >::run( datagenerator );
   helper_1stage::template simq_t< simq_vector_builder_set_t >::run( datagenerator );
   if constexpr ( sizeof( typename VectorExtension::base_t ) > 2 ) {
      helper_1stage::template simq_t< simq_vector_builder_gather_t >::run( datagenerator );
   }
   
   if constexpr( QueryCount > 2 ) {
      using helper_2stage = simq_query_distr_helper_2stages_t<
         VectorExtension, QueryCount, ColumnCount >;
      helper_2stage::seq_t::run( datagenerator );
      helper_2stage::template simq_t< simq_vector_builder_buffer_t >::run( datagenerator );
      helper_2stage::template simq_t< simq_vector_builder_mask_broadcast_t >::run( datagenerator );
      helper_2stage::template simq_t< simq_vector_builder_set_t >::run( datagenerator );
      if constexpr( sizeof( typename VectorExtension::base_t ) > 2 ) {
         helper_2stage::template simq_t< simq_vector_builder_gather_t >::run( datagenerator );
      }
   }
   
   if constexpr( QueryCount > 4 ){
      using helper_3stage = simq_query_distr_helper_3stages_t< VectorExtension, QueryCount, ColumnCount >;
      
      helper_3stage::seq_t::run( datagenerator );
      helper_3stage::template simq_t< simq_vector_builder_buffer_t >::run( datagenerator );
      helper_3stage::template simq_t< simq_vector_builder_mask_broadcast_t >::run( datagenerator );
      helper_3stage::template simq_t< simq_vector_builder_set_t >::run( datagenerator );
      if constexpr( sizeof( typename VectorExtension::base_t ) > 2 ) {
         helper_3stage::template simq_t< simq_vector_builder_gather_t >::run( datagenerator );
      }
   }
   
   delete datagenerator;
}

void run_experiment( std::size_t data_size ) {
   using namespace tuddbs;
   std::cerr << "Experiment vector size\n";
   run_build_variants< sse< uint64_t >, 1, 2 >( data_size );
   run_build_variants< avx2< uint64_t >, 1, 4 >( data_size );
   run_build_variants< avx512< uint64_t >, 1, 8 >( data_size );
   std::cerr << "Experiment value size\n";
   run_build_variants< avx512< uint8_t >, 1, 64 >( data_size );
   run_build_variants< avx512< uint16_t >, 1, 32 >( data_size );
   run_build_variants< avx512< uint32_t >, 1, 16 >( data_size );
   std::cerr << "Experiment query count\n";
   run_build_variants< avx512< uint64_t >, 1, 1 >( data_size );
   run_build_variants< avx512< uint64_t >, 1, 2 >( data_size );
   run_build_variants< avx512< uint64_t >, 1, 4 >( data_size );
   std::cerr << "Experiment column count\n";
//   run_build_variants< avx512< uint64_t >, 2, 8 >( data_size );
   run_build_variants< avx512< uint64_t >, 4, 8 >( data_size );
   run_build_variants< avx512< uint64_t >, 8, 8 >( data_size );
}

int main( void ) {
   using namespace tuddbs;
   auto t = std::time(nullptr);
   auto tm = *std::localtime(&t);
   std::ostringstream oss;
   oss << "query_intel_xeon_q12_sample_run_" << std::put_time(&tm, "%Y_%m_%d_%H-%M") << ".csv";
   auto str = oss.str();
   std::cerr << "Executing Benchmark Query 1.2 on Xeon Gold.\n";
   std::cout << str.c_str() << "\n";
   global::outputfile.open(str.c_str());
   if(! global::outputfile.is_open()) {
      std::cerr << "Could not open for writing: " << str << "\n";
      return 1;
   }
   global::outputfile << get_definitions("#");
   q12_header( );
   auto start = std::chrono::system_clock::now();
   run_experiment(128_MiB);
   
   
   auto end = std::chrono::system_clock::now();
   std::chrono::duration<double> elapsed_seconds = end-start;
   std::time_t start_time = std::chrono::system_clock::to_time_t(start);
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);
   global::outputfile << "#Started:  " << std::ctime(&start_time)
                      << "#End:      " << std::ctime(&end_time)
                      << "#Duration: " << elapsed_seconds.count() << "s.";
   return 0;
}