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


class MaskBroadcastIndexMaskPair:
    def __init__(self, vector_register: VectorRegister, positions_list: list):
        self.index = positions_list[0]
        self.vector_register = vector_register
        self.mask = self.create_mask(positions_list)

    def create_mask(self, positions_list: list):
        masklist = []
        mask_size = self.vector_register.mask_size
        for i in range(mask_size):
            masklist.append(str(0))
        for i in positions_list:
            masklist[ i ] = str(1)
        masklist.reverse()
        return "0b{}".format(''.join(masklist))


class MaskBroadcastMaskGenerator:
    def __init__(self, simq_vector_view: SIMQVectorView):
        self.simq_vector_view = simq_vector_view
        self.index_mask_pairs = []
        self.__column_offset_pairs_dict = defaultdict(list)
        for i in range(len(simq_vector_view.column_offset_pairs)):
            self.__column_offset_pairs_dict[ simq_vector_view.column_offset_pairs[ i ] ].append( i )
        for mask_key in self.__column_offset_pairs_dict.keys():
            self.index_mask_pairs.append(
                MaskBroadcastIndexMaskPair(
                    self.simq_vector_view.vector_register,
                    self.__column_offset_pairs_dict[mask_key]
                )
            )
    def to_cpp(self):
        loop_code = ""
        for pair in self.index_mask_pairs:
            if pair.index != 0:
                loop_code += "result = mask_broadcast< VectorExtension >(*svw.column_data_ptr[{idx}], {mask}, result);\n" \
                             "svw.column_data_ptr[ {idx} ] += {increment};\n".format(
                    idx=pair.index,
                    mask=pair.mask,
                    increment=self.simq_vector_view.column_offset_incrementor
                )
        indented_init_method_code = "\n".join(["   {0}".format(l) for l in iter(loop_code.splitlines())])
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
   typename {vecext}::vector_t result = broadcast< {vecext} >( *svw.column_data_ptr[ 0 ] );
   svw.column_data_ptr[ 0 ] += {increment};
{loop_code}
   return result;
}}
        '''.format(
            vecext=self.simq_vector_view.vector_register.to_cpp(),
            comment="\n".join(["   {0}".format(l) for l in iter(self.simq_vector_view.describe_to_cpp().splitlines())]),
            cc=self.simq_vector_view.column_count,
            qc=self.simq_vector_view.query_count,
            increment=self.simq_vector_view.column_offset_incrementor,
            loop_code=indented_init_method_code
        )


def write_SIMQBuilderMaskBroadCast_to_file(file_name, vector_spec_list):
    for vec_spec in vector_spec_list:
        init_method_code = ""
        vec_extension = vec_spec.vector_extension
        for datatype in vec_spec.data_type_list:
            vec_reg = VectorRegister(vec_extension, datatype)
            for column_query_pair in vec_reg.get_column_query_count_list():
                init_method_code += MaskBroadcastMaskGenerator(
                        SIMQVectorView(vec_reg, column_query_pair.column_count, column_query_pair.query_count)
                    ).to_cpp()
            indented_init_method_code = "\n".join(["      {0}".format(l) for l in iter(init_method_code.splitlines())])
        f = open("{}_{vecext}.h".format(file_name, vecext=vec_reg.vector_extension), "w")
        f.write(get_license_text())
        code = '''
#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_MASK_BROADCAST_INTEL_IMPL_{vecext}_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMQ_CONTROL_VECTOR_BUILDER_BUILD_VARIANTS_MASK_BROADCAST_INTEL_IMPL_{vecext}_H
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
   struct simq_vector_builder_mask_broadcast_t< ColumnContainer, NumberOfQueries, DepT, {vecext_stripped}< DepT > > {{ 
      using VectorExtension = typename ColumnContainer::vector_extension_t;
      using T = typename VectorExtension::base_t;
      static constexpr char const * get_name( void ) {{ return "BROADCAST"; }}
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
