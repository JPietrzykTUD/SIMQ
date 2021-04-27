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
#ifndef EXPERIMENT_MEASUREMENT_REPETITION_COUNT
#define EXPERIMENT_MEASUREMENT_REPETITION_COUNT 1
#endif
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstddef>
#include <chrono>
#include <ctime>

#include <benchmarks/queries/q11/query11_data.h>
<<<<<<< HEAD
#include <benchmarks/queries/q11/query11_seq.h>
=======
>>>>>>> ea5aa027a99e1d7d09246fdb7b25ca7a45b30f89
#include <benchmarks/queries/q11/query11_seq_parallel.h>
#include <benchmarks/queries/q11/query11_simq.h>

#include <cstddef>
#include <chrono>
#include <ctime>

namespace global {
   std::ofstream outputfile;
}

template<
   class VectorExtension,
   std::size_t ColumnCount,
   std::size_t QueryCount,
   std::size_t BatchSize
>
void run_build_variants(
   tuddbs::datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
) {
   using namespace tuddbs;
   std::cerr << "   " << vec_ext_to_string_t< VectorExtension >::apply( )
             << ". Queries: " << QueryCount << ". Columns: " << ColumnCount << ". BatchSize: " << BatchSize << "\n";
<<<<<<< HEAD
   sequential_wl_q11< VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
   sequential_parallel_wl_q11< VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
=======
   sequential_wl_q11_parallel< VectorExtension, ColumnCount, QueryCount, BatchSize, true >::run( datagenerator );
>>>>>>> ea5aa027a99e1d7d09246fdb7b25ca7a45b30f89
   simq_wl_q11< simq_vector_builder_buffer_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
   simq_wl_q11< simq_vector_builder_mask_broadcast_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
   simq_wl_q11< simq_vector_builder_set_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
   if( sizeof( typename VectorExtension::base_t ) > 2 ) {
      simq_wl_q11< simq_vector_builder_gather_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
   }
}

template< class VectorExtension, std::size_t ColumnCount, std::size_t QueryCount >
struct run_batch_sizes {
   template<
      typename VE = VectorExtension,
      typename std::enable_if< ( QueryCount <= tuddbs::vector_constants_t< VE >::vector_element_count_t::value ), std::nullptr_t >::type = nullptr
   >
   static void apply(
      std::size_t data_size
   ) {
      using namespace tuddbs;
      datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * datagenerator =
         new datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount >( data_size );
      run_build_variants< VectorExtension, ColumnCount, QueryCount, 0 >( datagenerator );
      delete datagenerator;
   }
   template<
      typename VE = VectorExtension,
      typename std::enable_if< ( QueryCount > tuddbs::vector_constants_t< VE >::vector_element_count_t::value ), std::nullptr_t >::type = nullptr
   >
   static void apply(
      tuddbs::datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator
   ) { }
};

void run_experiment( std::size_t data_size ) {
   using namespace tuddbs;
   std::cerr << "Experiment vector size\n";
   run_batch_sizes< sse< uint64_t >, 1, 2 >::apply( data_size );
   run_batch_sizes< avx2< uint64_t >, 1, 4 >::apply( data_size );
   run_batch_sizes< avx512< uint64_t >, 1, 8 >::apply( data_size );
   std::cerr << "Experiment value size\n";
//   run_batch_sizes< avx512< uint8_t >, 1, 64 >::apply( data_size );
//   run_batch_sizes< avx512< uint16_t >, 1, 32 >::apply( data_size );
   run_batch_sizes< avx512< uint32_t >, 1, 16 >::apply( data_size );
   std::cerr << "Experiment query count\n";
   run_batch_sizes< avx512< uint64_t >, 1, 1 >::apply( data_size );
   run_batch_sizes< avx512< uint64_t >, 1, 2 >::apply( data_size );
   run_batch_sizes< avx512< uint64_t >, 1, 4 >::apply( data_size );
   std::cerr << "Experiment column count\n";
   run_batch_sizes< avx512< uint64_t >, 2, 8 >::apply( data_size );
   run_batch_sizes< avx512< uint64_t >, 4, 8 >::apply( data_size );
   run_batch_sizes< avx512< uint64_t >, 8, 8 >::apply( data_size );
}


int main( void ) {
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
   
   auto start = std::chrono::system_clock::now();
   using namespace tuddbs;
   global::outputfile << get_definitions("#");
   q11_header( );
   run_experiment( 128_MiB );
//   run_experiment( 128 );
   auto end = std::chrono::system_clock::now();
   std::chrono::duration<double> elapsed_seconds = end-start;
   std::time_t start_time = std::chrono::system_clock::to_time_t(start);
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);
   global::outputfile << "#Started:  " << std::ctime(&start_time)
                      << "#End:      " << std::ctime(&end_time)
                      << "#Duration: " << elapsed_seconds.count() << "s.";
   
   global::outputfile.close();
   return 0;
}