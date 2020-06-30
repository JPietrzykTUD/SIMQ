'''
This file is part of the SIMQ Project (https://github.com/JPietrzykTUD/SIMQ).
Copyright (c) 2020 Johannes Pietrzyk.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
'''
import copy

from simq.general.license import get_license_text
from simq.vector.types import VectorRegister


class ColumnAndOffsetPair:
   def __init__(self, column_id: int, column_offset: int):
      self.column_id = column_id
      self.column_offset = column_offset

   def __eq__(self, other):
      return \
         hasattr(other, 'column_id') and \
         hasattr(other, 'column_offset') and \
         self.column_offset == other.column_offset and \
         self.column_id == other.column_id

   def __hash__(self):
      return hash("{}-{}".format(self.column_id, self.column_offset))

   def __str__(self):
      return "{{{:^4}}}[{:^4}]".format(self.column_id, self.column_offset)



class SIMQVectorView:
   def __init__(self, vector_register: VectorRegister, column_count: int, query_count: int):
      if column_count > vector_register.element_count:
         raise Exception("Column Count has to be <= than Element Count")
      if query_count > vector_register.element_count:
         raise Exception("Query Count has to be <= than Element Count")
      if column_count > query_count:
         raise Exception("Column Count has to be <= than Query Count")
      self.vector_register = vector_register
      self.column_count = column_count
      self.query_count = query_count
      self.column_offset_pairs = []
      column_ids = []
      lanes_per_column = int(vector_register.element_count / column_count)
      for col_idx in range(column_count):
         for lane in range(lanes_per_column):
            column_ids.append(col_idx)
      column_offsets = []
      lanes_per_query = int(vector_register.element_count / query_count)
      for query_idx in range(query_count):
         for lane in range(lanes_per_query):
            column_offsets.append(lane)
      self.column_offset_incrementor = lanes_per_query
      if len(column_ids) != len(column_offsets):
         raise Exception("Something went wrong when creating SIMQVV: ColIdCount:{}. ColOffCount:{}".format(
            len(column_ids), len(column_offsets))
         )
      # helper_dict = dict()
      for i in range(len(column_ids)):
         pair = ColumnAndOffsetPair(column_ids[i], column_offsets[i])
         self.column_offset_pairs.append(pair)
         # if pair not in helper_dict:
         #    helper_dict[pair] = 0
         # else:
         #    helper_dict[pair] += 1
      # self.column_offset_incrementor = max(helper_dict.values()) + 1

   def describe_to_cpp(self):
      pairs = copy.deepcopy(self.column_offset_pairs)
      pairs.reverse()
      result = "/* { col_id }[ col_offset ]\n * | "
      for i in range(len(self.column_offset_pairs)):
         result += str(pairs[i])
         if (i+1) % 8 == 0:
            result += "|\n * | "
         else:
            result += " | "
      result += "\n */"
      return result

   def to_cpp(self):
      assign_cpp = ""
      for i in range(self.vector_register.element_count):
         if self.column_offset_pairs[i].column_offset==0:
            assign_cpp += "   column_data_ptr[ {id} ] = ( {type} * ) p_container.columns[ {col_id} ]->data_ptr;\n".format(
               id = i,
               col_id = self.column_offset_pairs[i].column_id,
               type = self.vector_register.data_type,
            )
         else:
            assign_cpp += "   column_data_ptr[ {id} ] = ( {type} * ) p_container.columns[ {col_id} ]->data_ptr + {col_offset};\n".format(
               id=i,
               col_id=self.column_offset_pairs[i].column_id,
               type=self.vector_register.data_type,
               col_offset=self.column_offset_pairs[i].column_offset
            )
      return '''
template< 
   std::size_t NoQ = NumberOfQueries, 
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if< ( ( NoQ == {qc} ) && ( NoC == {cc} ) && ( std::is_same< VecExt, {vecext} >::value )), std::nullptr_t >::type = nullptr 
>
constexpr static void init( ColumnContainer const & p_container, {datatype} * * const column_data_ptr ) {{
{init_code}
}}  
template< 
   std::size_t NoQ = NumberOfQueries, 
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if< ( ( NoQ == {qc} ) && ( NoC == {cc} ) && ( std::is_same< VecExt, {vecext} >::value )), std::nullptr_t >::type = nullptr 
>
constexpr static std::size_t get_incrementor( void ) {{
   return {incrementor};
}}
      '''.format(
         qc=self.query_count,
         cc=self.column_count,
         vecext=self.vector_register.to_cpp(),
         datatype=self.vector_register.data_type,
         init_code=assign_cpp,
         incrementor=self.column_offset_incrementor
      )


def write_SIMQVectorView_to_file(file_name, vector_spec_list):
   for vec_spec in vector_spec_list:
      init_method_code = ""
      vec_extension = vec_spec.vector_extension
      for datatype in vec_spec.data_type_list:
         vec_reg = VectorRegister(vec_extension, datatype)
         for column_query_pair in vec_reg.get_column_query_count_list():
            init_method_code += SIMQVectorView(vec_reg, column_query_pair.column_count, column_query_pair.query_count).to_cpp()
         indented_init_method_code = "\n".join(["      {0}".format(l) for l in iter(init_method_code.splitlines())])
      f = open("{}_impl_{vecext}.h".format(file_name, vecext=vec_reg.vector_extension), "w")
      f.write(get_license_text())
      code = '''
#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_VIEW_IMPL_{vecext}_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_VIEW_IMPL_{vecext}_H
#include <simd/intrin.h>
#include <data/column.h>
#include <data/container/column_array.h>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace tuddbs{{
   template<
      class ColumnContainer,
      std::size_t NumberOfQueries,
      typename DepT
   >
   struct simq_column_vector_view_impl_t< ColumnContainer, NumberOfQueries, DepT, {vecext_stripped}< DepT > > {{
      using VectorExtension = typename ColumnContainer::vector_extension_t;
      using T = typename VectorExtension::base_t;
      {init_method_code}
   }};
}}
#endif //TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_VECTOR_VIEW_H
      '''.format(
         vecext=str(vec_reg.vector_extension).upper(),
         vecext_stripped=vec_reg.vector_extension,
         init_method_code=indented_init_method_code
      )
      f.write(code)
      f.close()