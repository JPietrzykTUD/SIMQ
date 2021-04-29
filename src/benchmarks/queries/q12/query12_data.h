//
// Created by jpietrzyk on 25.04.21.
//

#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_DATA_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_DATA_H

#include <fstream>

namespace global {
   extern std::ofstream outputfile;
}

#include <data/column.h>
#include <data/container/column_array.h>

#include <simd/intrin.h>

#include <simq/control/vector_builder/vector_view.h>
#include <simq/control/vector_builder/vector_builder.h>
#include <simq/control/vector_builder/build_variants/buffer.h>
#include <simq/control/vector_builder/build_variants/gather.h>
#include <simq/control/vector_builder/build_variants/mask_broadcast.h>
#include <simq/control/vector_builder/build_variants/set.h>

#include <engine/operators/core/filter/point_filter_comparator_core.h>
#include <engine/operators/core/aggregate/aggregate_sum_core.h>

#include <engine/operators/bitmask_candidates/sequential/aggregate_bitmask_candidates.h>
#include <engine/operators/bitmask_candidates/sequential/filter_bitmask_candidates.h>

#include <engine/operators/bitmask_candidates/simq/aggregate_bitmask_candidates.h>
#include <engine/operators/bitmask_candidates/simq/filter_bitmask_candidates.h>

#include <utils/random.h>
#include <utils/clock.h>
#include <utils/helper.h>

#include <cstddef>
#include <iostream>

namespace tuddbs {
   void q12_header( void ) {
      global::outputfile << "rep;"
                         << "data_count;"
                         << "data_size;"
                         << "vector_extension_name;"
                         << "data_type;"
                         << "workload_processing_name;"
                         << "intermediate_format;"
                         << "build_variant_name;"
                         << "column_count;"
                         << "query_count_1st_stage;"
                         << "query_count_2nd_stage_op1;"
                         << "query_count_2nd_stage_op2;"
                         << "query_count_2nd_stage_op3;"
                         << "query_processing_variant_name;"
                         << "batch_size;"
                         << "simq_build_time_ns;"
                         << "execution_time_ns;"
                         << "result_op1;"
                         << "result_op2;"
                         << "result_op3;"
                         << "dummy\n";
   }
   
   template<
      class VectorExtension,
      std::size_t QueryCount2ndStageOp1,
      std::size_t QueryCount2ndStageOp2,
      std::size_t QueryCount2ndStageOp3,
      std::size_t ColumnCount = 1
   >
   struct experiment_query12 {
      static void print_experiment_result(
         std::size_t const rep,
         datagenerator_q11<
            typename VectorExtension::base_t, ColumnCount,
            QueryCount2ndStageOp1 + QueryCount2ndStageOp2 + QueryCount2ndStageOp3
         > * const
         datagenerator,
         std::string variant_name,
         std::string intermediate_name,
         std::string build_name,
         std::chrono::time_point <std::chrono::high_resolution_clock> start_simq_build,
         std::chrono::time_point <std::chrono::high_resolution_clock> end_simq_build,
         std::chrono::time_point <std::chrono::high_resolution_clock> start,
         std::chrono::time_point <std::chrono::high_resolution_clock> end,
         uint64_t const flush_dummy,
         column< typename VectorExtension::base_t > * const aggregation1_result,
         column< typename VectorExtension::base_t > * const aggregation2_result = nullptr,
         column< typename VectorExtension::base_t > * const aggregation3_result = nullptr
      ) {
         global::outputfile << rep << ";"
                            << datagenerator->data_size / sizeof( typename VectorExtension::base_t ) << ";"
                            << datagenerator->data_size << ";"
                            << vec_ext_to_string_t< VectorExtension >::apply( ) << ";"
                            << variant_name << ";"
                            << intermediate_name << ";"
                            << build_name << ";"
                            << 1 << ";"
                            << QueryCount2ndStageOp1 + QueryCount2ndStageOp2 + QueryCount2ndStageOp3 << ";"
                            << QueryCount2ndStageOp1 << ";"
                            << QueryCount2ndStageOp2 << ";"
                            << QueryCount2ndStageOp3 << ";"
                            << "Operator at a Time;0;"
                            << time_elapsed_ns( start_simq_build, end_simq_build ) << ";"
                            << time_elapsed_ns( start, end ) << ";"
                            << " | ";
         for(
            std::size_t query_id = 0; query_id < QueryCount2ndStageOp1; ++query_id
            ) {
            global::outputfile << ( uint64_t ) aggregation1_result->data_ptr[ query_id ] << " | ";
         }
         global::outputfile << ";";
         if( aggregation2_result != nullptr ) {
            global::outputfile << " | ";
            for(
               std::size_t query_id = 0; query_id < QueryCount2ndStageOp2; ++query_id
               ) {
               global::outputfile << ( uint64_t ) aggregation2_result->data_ptr[ query_id ] << " | ";
            }
         } else {
            global::outputfile << " / ";
         }
         global::outputfile << ";";
         if( aggregation3_result != nullptr ) {
            global::outputfile << " | ";
            for(
               std::size_t query_id = 0; query_id < QueryCount2ndStageOp3; ++query_id
               ) {
               global::outputfile << ( uint64_t ) aggregation3_result->data_ptr[ query_id ] << " | ";
            }
         } else {
            global::outputfile << " / ";
         }
         global::outputfile << ";" << flush_dummy << "\n";
      }
   };
}
#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_Q12_QUERY12_DATA_H
