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

#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstddef>
#include <chrono>
#include <ctime>

#include <benchmarks/queries/q11/query11_data.h>
#include <benchmarks/queries/data/measurement_helper.h>

#include <benchmarks/queries/q11/query11_seq.h>
#include <benchmarks/queries/q11/query11_simq.h>
#include <benchmarks/queries/q11/query11_seq_parallel.h>
#include <benchmarks/queries/q11/query11_seq_parallel_tput.h>
#include <benchmarks/queries/q11/query11_simq_parallel_tput.h>

#include <benchmarks/queries/q12/query12_seq.h>
#include <benchmarks/queries/q12/query12_simq.h>
//#include <benchmarks/queries/q12/query12_seq_parallel.h>
//#include <benchmarks/queries/q12/query12_seq_parallel_tput.h>
#include <benchmarks/queries/q12/query12_simq_parallel_tput.h>


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
   std::size_t NumberOfSucceedingOperators,
   std::size_t BatchSize = 0
>
struct workload {
   template<
      std::size_t SO = NumberOfSucceedingOperators,
      typename std::enable_if< SO == 1, std::nullptr_t >::type = nullptr
   >
   static void run(
      std::size_t data_size
   ) {
      using namespace tuddbs;
      datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount >
         * datagenerator = new datagenerator_q11<
         typename VectorExtension::base_t, ColumnCount, QueryCount
      >( data_size );
      std::cerr << "   " << vec_ext_to_string_t< VectorExtension >::apply( )
                << ". Queries: " << QueryCount << ". Columns: " << ColumnCount << ".\n";
      std::cerr << "      Single Threaded... ";
      sequential_wl_q11< VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
      simq_wl_q11< simq_vector_builder_buffer_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run(
         datagenerator
      );
      simq_wl_q11< simq_vector_builder_mask_broadcast_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run(
         datagenerator
      );
      simq_wl_q11< simq_vector_builder_set_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
      if( sizeof( typename VectorExtension::base_t ) > 2 ) {
         simq_wl_q11< simq_vector_builder_gather_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run(
            datagenerator
         );
      }
      std::cerr << "Done.\n       Multi Threaded... ";
      if constexpr( QueryCount > 1 ) { //otherwise sequential_parallel_wl_q11 == sequential_wl_q11
         sequential_parallel_wl_q11< VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
      }
      sequential_parallel_wl_q11_tput< VectorExtension, ColumnCount, QueryCount, BatchSize >::run( datagenerator );
      simq_wl_q11_parallel_tput< simq_vector_builder_buffer_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run(
         datagenerator
      );
      simq_wl_q11_parallel_tput< simq_vector_builder_mask_broadcast_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run(
         datagenerator
      );
      simq_wl_q11_parallel_tput< simq_vector_builder_set_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run(
         datagenerator
      );
      if( sizeof( typename VectorExtension::base_t ) > 2 ) {
         simq_wl_q11_parallel_tput< simq_vector_builder_gather_t, VectorExtension, ColumnCount, QueryCount, BatchSize >::run(
            datagenerator
         );
      }
      std::cerr << "Done.\n";
   }
   template<
      std::size_t SO = NumberOfSucceedingOperators,
      typename std::enable_if< SO == 2, std::nullptr_t >::type = nullptr
   >
   static void run(
      std::size_t data_size
   ) {
      using namespace tuddbs;
      static_assert(
         std::is_same_v< VectorExtension, avx512< uint64_t > >,
         "For this experiment, only avx512< uint64_t > is provided."
      );
      
      datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount >
         * datagenerator = new datagenerator_q11<
         typename VectorExtension::base_t, ColumnCount, QueryCount
      >( data_size );
      std::cerr << "   " << vec_ext_to_string_t< VectorExtension >::apply( )
                << ". Queries: " << QueryCount << ". Columns: " << ColumnCount << ".\n";
      std::cerr << "      Single Threaded... ";
      seq_wl_q12_two_Stage2_ops < avx512 < uint64_t > , 4, 4 > ::run(
         datagenerator
      );
      simq_wl_q12_two_Stage2_ops < simq_vector_builder_buffer_t, VectorExtension, 4, 4 > ::run(
         datagenerator
      );
      simq_wl_q12_two_Stage2_ops < simq_vector_builder_mask_broadcast_t, VectorExtension, 4, 4 > ::run(
         datagenerator
      );
      simq_wl_q12_two_Stage2_ops < simq_vector_builder_set_t, VectorExtension, 4, 4 > ::run(
         datagenerator
      );
      simq_wl_q12_two_Stage2_ops < simq_vector_builder_gather_t, VectorExtension, 4, 4 > ::run(
         datagenerator
      );
      std::cerr << "Done.\n       Multi Threaded... ";
//      seq_parallel_wl_q12_two_Stage2_ops< avx512< uint64_t >, 4, 4 >::run()
//      seq_parallel_wl_q12_two_Stage2_ops_tput< avx512< uint64_t >, 4, 4 >::run()
      simq_wl_q12_two_Stage2_ops_tput< simq_vector_builder_buffer_t, VectorExtension, 4, 4 >::run(
         datagenerator
      );
      simq_wl_q12_two_Stage2_ops_tput< simq_vector_builder_mask_broadcast_t, VectorExtension, 4, 4 >::run(
         datagenerator
      );
      simq_wl_q12_two_Stage2_ops_tput< simq_vector_builder_set_t, VectorExtension, 4, 4 >::run(
         datagenerator
      );
      simq_wl_q12_two_Stage2_ops_tput< simq_vector_builder_gather_t, VectorExtension, 4, 4 >::run(
         datagenerator
      );
   }
   
   template<
      std::size_t SO = NumberOfSucceedingOperators,
      typename std::enable_if< SO == 3, std::nullptr_t >::type = nullptr
   >
   static void run(
      std::size_t data_size
   ) {
      using namespace tuddbs;
      static_assert(
         std::is_same_v< VectorExtension, avx512< uint64_t > >,
         "For this experiment, only avx512< uint64_t > is provided."
      );
      
      datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount >
         * datagenerator = new datagenerator_q11<
         typename VectorExtension::base_t, ColumnCount, QueryCount
      >( data_size );
      std::cerr << "   " << vec_ext_to_string_t< VectorExtension >::apply( )
                << ". Queries: " << QueryCount << ". Columns: " << ColumnCount << ".\n";
      std::cerr << "      Single Threaded... ";
      seq_wl_q12_three_Stage2_ops < avx512 < uint64_t > , 4, 2, 2 > ::run(
         datagenerator
      );
      simq_wl_q12_three_Stage2_ops < simq_vector_builder_buffer_t, VectorExtension, 4, 2, 2 > ::run(
         datagenerator
      );
      simq_wl_q12_three_Stage2_ops < simq_vector_builder_mask_broadcast_t, VectorExtension, 4, 2, 2 > ::run(
         datagenerator
      );
      simq_wl_q12_three_Stage2_ops < simq_vector_builder_set_t, VectorExtension, 4, 2, 2 > ::run(
         datagenerator
      );
      simq_wl_q12_three_Stage2_ops < simq_vector_builder_gather_t, VectorExtension, 4, 2, 2 > ::run(
         datagenerator
      );
//      std::cerr << "Done.\n       Multi Threaded... ";
//      seq_parallel_wl_q12_three_Stage2_ops< avx512< uint64_t >, 4, 2, 2 >::run()
//      seq_parallel_wl_q12_three_Stage2_ops_tput< avx512< uint64_t >, 4, 2, 2 >::run()
//      simq_wl_q12_three_Stage2_ops_tput< simq_vector_builder_buffer_t, VectorExtension, 4, 2, 2 >::run(
//         datagenerator
//      );
//      simq_wl_q12_three_Stage2_ops_tput< simq_vector_builder_mask_broadcast_t, VectorExtension, 4, 2, 2 >::run(
//         datagenerator
//      );
//      simq_wl_q12_three_Stage2_ops_tput< simq_vector_builder_set_t, VectorExtension, 4, 2, 2 >::run(
//         datagenerator
//      );
//      simq_wl_q12_three_Stage2_ops_tput< simq_vector_builder_gather_t, VectorExtension, 4, 2, 2 >::run(
//         datagenerator
//      );
   }
};

void run_experiment( std::size_t data_size ) {
   using namespace tuddbs;
//   std::cerr << "Experiment Batch Size\n";
//   workload< avx512< uint64_t >, 1,  8, 1, 4_KiB >::run( data_size );
//   workload< avx512< uint64_t >, 1,  8, 1, 4_MiB >::run( data_size );
   std::cerr << "Experiment vector size\n";
   workload<    sse< uint64_t >, 1,  2, 1 >::run( data_size );
   workload<   avx2< uint64_t >, 1,  4, 1 >::run( data_size );
   workload< avx512< uint64_t >, 1,  8, 1 >::run( data_size );
   std::cerr << "Experiment value size\n";
   workload< avx512<  uint8_t >, 1, 64, 1 >::run( data_size );
   workload< avx512< uint16_t >, 1, 32, 1 >::run( data_size );
   workload< avx512< uint32_t >, 1, 16, 1 >::run( data_size );
   std::cerr << "Experiment query count\n";
   workload< avx512< uint64_t >, 1,  1, 1 >::run( data_size );
   workload< avx512< uint64_t >, 1,  2, 1 >::run( data_size );
   workload< avx512< uint64_t >, 1,  4, 1 >::run( data_size );
   std::cerr << "Experiment column count\n";
   workload< avx512< uint64_t >, 2,  8, 1 >::run( data_size );
   workload< avx512< uint64_t >, 4,  8, 1 >::run( data_size );
   workload< avx512< uint64_t >, 8,  8, 1 >::run( data_size );
   std::cerr << "Experiment succeeding operators\n";
   workload< avx512< uint64_t >, 1,  8, 2 >::run( data_size );
   workload< avx512< uint64_t >, 1,  8, 3 >::run( data_size );
}

int main( void ) {
   auto               t  = std::time( nullptr );
   auto               tm = *std::localtime( &t );
   std::ostringstream oss;
   oss << "vldbj_results_" << std::put_time( &tm, "%Y_%m_%d_%H-%M" ) << ".csv";
   auto str = oss.str( );
   std::cerr << "Executing Benchmarks for VLDB on Xeon Gold.\n";
   std::cout << str.c_str( ) << "\n";
   global::outputfile.open( str.c_str( ) );
   if( !global::outputfile.is_open( ) ) {
      std::cerr << "Could not open for writing: " << str << "\n";
      return 1;
   }
   
   auto start = std::chrono::system_clock::now( );
   using namespace tuddbs;
   global::outputfile << get_definitions( "#" );
   measurement_header( );
   run_experiment( 128_MiB );
   auto                            end             = std::chrono::system_clock::now( );
   std::chrono::duration< double > elapsed_seconds = end - start;
   std::time_t                     start_time      = std::chrono::system_clock::to_time_t( start );
   std::time_t                     end_time        = std::chrono::system_clock::to_time_t( end );
   global::outputfile << "#Started:  " << std::ctime( &start_time )
                      << "#End:      " << std::ctime( &end_time )
                      << "#Duration: " << elapsed_seconds.count( ) << "s.";
   
   global::outputfile.close( );
   return 0;
}