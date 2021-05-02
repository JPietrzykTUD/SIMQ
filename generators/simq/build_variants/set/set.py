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
from collections import defaultdict

from simq.general.license import get_license_text
from simq.general.simq_vector_view import SIMQVectorView
from simq.vector.types import VectorRegister


class SetGenerator:
    def __init__(self, simq_vector_view: SIMQVectorView):
        self.simq_vector_view = simq_vector_view
        self.column_offset_pairs_dict = defaultdict(list)
        for i in range(len(simq_vector_view.column_offset_pairs)):
            self.column_offset_pairs_dict[self.simq_vector_view.column_offset_pairs[i]].append(i)

    def to_cpp(self):
        code = ""
        idx = 0
        val_array = []
        for i in range(self.simq_vector_view.vector_register.element_count):
            val_array.append("0")
        for i in self.column_offset_pairs_dict.keys():
            code += "{data_type} val{idx} = *svw.column_data_ptr[ {col_idx} ]; " \
                    "svw.column_data_ptr[ {col_idx} ] += {increment};\n".format(
                data_type=self.simq_vector_view.vector_register.data_type,
                idx=idx,
                col_idx=self.column_offset_pairs_dict[i][0],
                increment=self.simq_vector_view.column_offset_incrementor,
            )
            for positions in self.column_offset_pairs_dict[i]:
                val_array[positions] = "val{idx}".format(idx=idx)
            idx += 1
        val_array.reverse()
        set_code = val_array[0]
        for i in range(1, len(val_array)):
            set_code += ", {}".format(val_array[i])
        code += "typename {vecext}::vector_t result = set< {vecext} >( {values} );".format(
            vecext=self.simq_vector_view.vector_register.to_cpp(),
            values=set_code
        )
        indented_init_method_code = "\n".join(["   {0}".format(l) for l in iter(code.splitlines())])
        return '''
template< 
   std::size_t NoQ = NumberOfQueries, 
   std::size_t NoC = ColumnContainer::number_or_columns_t::value,
   class VecExt = VectorExtension,
   typename std::enable_if< ( ( NoQ == {qc} ) && ( NoC == {cc} ) && ( std::is_same< VecExt, {vecext} >::value )), std::nullptr_t >::type = nullptr 
>  
FORCE_INLINE
static
typename {vecext}::vector_t
get_and_increment( simq_column_vector_view_t< ColumnContainer, NumberOfQueries > & svw ) {{
{comment}
{code}
   return result;
}}
                '''.format(
            vecext=self.simq_vector_view.vector_register.to_cpp(),
            comment="\n".join(["   {0}".format(l) for l in iter(self.simq_vector_view.describe_to_cpp().splitlines())]),
            cc=self.simq_vector_view.column_count,
            qc=self.simq_vector_view.query_count,
            increment=self.simq_vector_view.column_offset_incrementor,
            code=indented_init_method_code
        )


def write_SIMQBuilderSET_to_file(file_name, vector_spec_list):
    for vec_spec in vector_spec_list:
        init_method_code = ""
        vec_extension = vec_spec.vector_extension
        for datatype in vec_spec.data_type_list:
            vec_reg = VectorRegister(vec_extension, datatype)
            for column_query_pair in vec_reg.get_column_query_count_list():
                init_method_code += SetGenerator(
                        SIMQVectorView(vec_reg, column_query_pair.column_count, column_query_pair.query_count)
                    ).to_cpp()
            indented_init_method_code = "\n".join(["      {0}".format(l) for l in iter(init_method_code.splitlines())])
        f = open("{}_{vecext}.h".format(file_name, vecext=vec_reg.vector_extension), "w")
        f.write(get_license_text())
        code = '''
#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_SET_IMPL_{vecext}_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_SET_IMPL_{vecext}_H
#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <cstdint>
#include <cstddef>
#include <type_traits>
namespace tuddbs{{
   template<
      class ColumnContainer,
      std::size_t NumberOfQueries,
      typename DepT
   >
   struct simq_vector_builder_set_t< ColumnContainer, NumberOfQueries, DepT, {vecext_stripped}< DepT > > {{ 
      using VectorExtension = typename ColumnContainer::vector_extension_t;
      using T = typename VectorExtension::base_t;
      static constexpr char const * get_name( void ) {{ return "SET"; }}
      {code}
   }};
}} 
#endif
        '''.format(
            vecext=str(vec_reg.vector_extension).upper(),
            vecext_stripped=vec_reg.vector_extension,
            code=indented_init_method_code
        )
        f.write(code)
        f.close()
