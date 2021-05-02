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

#ifndef TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_DATA_MEASUREMENT_HELPER_H
#define TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_DATA_MEASUREMENT_HELPER_H

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
#include <engine/operators/core/aggregate/aggregate_min_core.h>
#include <engine/operators/core/aggregate/aggregate_max_core.h>

#include <engine/operators/bitmask_candidates/sequential/aggregate_bitmask_candidates.h>
#include <engine/operators/bitmask_candidates/sequential/filter_bitmask_candidates.h>

#include <engine/operators/bitmask_candidates/simq/aggregate_bitmask_candidates.h>
#include <engine/operators/bitmask_candidates/simq/filter_bitmask_candidates.h>

#include <utils/random.h>
#include <utils/clock.h>
#include <utils/helper.h>

#include <cstddef>
#include <iostream>

#include <benchmarks/queries/q11/query11_data.h>
namespace tuddbs {
   
   
   void measurement_header( void ) {
      global::outputfile << "rep;"
                         << "data_count;"
                         << "data_size;"
                         << "vector_extension_name;"
                         << "data_type;"
                         << "workload_processing_name;"
                         << "intermediate_format;"
                         << "build_variant_name;"
                         << "column_count;"
                         << "query_count;"
                         << "succeeding_operators;"
                         << "query_processing_variant_name;"
                         << "batch_size;"
                         << "executed_queries;"
                         << "thread_count;"
                         << "simq_build_time_ns;"
                         << "execution_time_ns;"
                         << "total_cpu_time_ns;"
                         << "cpu_freq_over_time;"
                         << "dummy;"
                         << "result0;"
                         << "result1;"
                         << "result2\n";
   }
   
   template<
      class VectorExtension,
      std::size_t ColumnCount,
      std::size_t QueryCount,
      std::size_t BatchSize,
      std::size_t QueryCount2ndStageOp2 = 0,
      std::size_t QueryCount2ndStageOp3 = 0
   >
   struct experiment_query_11_12 {
      static void print_experiment_result(
         std::size_t const rep,
         datagenerator_q11< typename VectorExtension::base_t, ColumnCount, QueryCount > * const datagenerator,
         std::string variant_name,
         std::string intermediate_name,
         std::string build_name,
         std::size_t executed_queries,
         std::size_t thread_count,
         std::chrono::time_point <std::chrono::high_resolution_clock> start_simq_build,
         std::chrono::time_point <std::chrono::high_resolution_clock> end_simq_build,
         std::chrono::time_point <std::chrono::high_resolution_clock> start_execution,
         std::chrono::time_point <std::chrono::high_resolution_clock> end_execution,
         double total_cpu_time_ns,
         std::string discrete_cpu_freq,
         uint64_t const dummy,
         column< typename VectorExtension::base_t > * const aggregation_result_column1,
         [[maybe_unused]]column< typename VectorExtension::base_t > * const aggregation_result_column2 = nullptr,
         [[maybe_unused]]column< typename VectorExtension::base_t > * const aggregation_result_column3 = nullptr
      ) {
         std::size_t succ_op_count = 0;
         if( QueryCount2ndStageOp3 > 0 ) {
            succ_op_count = 3;
         } else if( QueryCount2ndStageOp2 > 0 ) {
            succ_op_count = 2;
         } else {
            succ_op_count = 1;
         }
         global::outputfile << rep << ";"
         << datagenerator->data_size / sizeof( typename VectorExtension::base_t ) << ";"
         << datagenerator->data_size << ";"
         << vec_ext_to_string_t< VectorExtension >::apply( ) << ";"
         << variant_name << ";"
         << intermediate_name << ";"
         << build_name << ";"
         << ColumnCount << ";"
         << QueryCount << ";"
         << succ_op_count << ";"
         << ( ( BatchSize == 0 ) ? "Operator at a Time" : "Batch at a Time" ) << ";"
         << BatchSize << ";"
         << executed_queries << ";"
         << thread_count << ";"
         << time_elapsed_ns( start_simq_build, end_simq_build ) << ";"
         << time_elapsed_ns( start_execution, end_execution ) << ";"
         << total_cpu_time_ns << ";"
         << discrete_cpu_freq << ";"
         << dummy << ";";
         for(
            std::size_t query_id = 0; query_id < QueryCount; ++query_id
            ) {
            global::outputfile << ( uint64_t ) aggregation_result_column1->data_ptr[ query_id ] << " | ";
         }
         global::outputfile << ";";
         if constexpr (QueryCount2ndStageOp2 > 0 ) {
            for(
               std::size_t query_id = 0; query_id < QueryCount2ndStageOp2; ++query_id
               ) {
               global::outputfile << ( uint64_t ) aggregation_result_column2->data_ptr[ query_id ] << " | ";
            }
         }
         global::outputfile << ";";
         if constexpr (QueryCount2ndStageOp3 > 0 ) {
            for(
               std::size_t query_id = 0; query_id < QueryCount2ndStageOp3; ++query_id
               ) {
               global::outputfile << ( uint64_t ) aggregation_result_column3->data_ptr[ query_id ] << " | ";
            }
         }
         global::outputfile << "\n";
      }
   };
   
}
#endif //TUDDBS_SIMQ_SRC_BENCHMARKS_QUERIES_DATA_MEASUREMENT_HELPER_H
