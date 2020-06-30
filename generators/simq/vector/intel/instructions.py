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
from pathlib import Path

from simq.general.license import get_license_text
from simq.vector.types import VectorExtension, DataType, VectorRegister


class CreateIntrinsicCreator:
    def __init__(self, base_path: str):
        Path(base_path).mkdir(parents=True, exist_ok=True)
        self.definition_path = "{}/instructions/declarations".format(base_path)
        Path(self.definition_path).mkdir(parents=True, exist_ok=True)
        self.implementation_path = "{}/instructions/intel".format(base_path)
        Path(self.implementation_path).mkdir(parents=True, exist_ok=True)

    def create_function_definition(self):
        f = open("{}/create.h".format(self.definition_path), "w")
        elem_count_set = set()
        for data_type in DataType:
            for vector_extension in VectorExtension:
                elem_count_set.add(VectorRegister(vector_extension, data_type).element_count)
        elem_count_list = []
        for val in elem_count_set:
            elem_count_list.append(val)
        elem_count_list.sort()
        set_intel_definition = ""
        for elem_count in elem_count_list:
            parameter = "   typename VectorExtension::base_t const val{}".format(elem_count - 1)
            for i in range(1, elem_count):
                parameter += ",\n   typename VectorExtension::base_t const val{}".format(elem_count-i-1)
            set_intel_definition += '''
template< class VectorExtension >
typename VectorExtension::vector_t
set(
{parameter} 
);
            '''.format(parameter=parameter)
        indented_init_method_code = "\n".join(["   {0}".format(l) for l in iter(set_intel_definition.splitlines())])
        code = '''
#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_DECLARATIONS_CREATE_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_DECLARATIONS_CREATE_H
#include <simd/types/simd.h>
namespace tuddbs {{
   {code}
}}
#endif
        '''.format(code=indented_init_method_code)
        f.write(get_license_text())
        f.write(code)
        f.close()

    def create_function_implementation(self):
        for vector_extension in VectorExtension:
            path = "{}/{}".format(self.implementation_path, vector_extension)
            Path(path).mkdir(parents=True, exist_ok=True)
            f = open("{}/create_{}.h".format(path, vector_extension), "w")
            f.write(get_license_text())
            function_code = ""
            for data_type in DataType:
                vector_register = VectorRegister(vector_extension, data_type)
                parameter = "typename {vecext}::base_t const val{idx}".format(vecext=vector_register.to_cpp(), idx = vector_register.element_count-1)
                additional_spec = ""
                if data_type == DataType.uint64_t:
                    if vector_extension == VectorExtension.sse or vector_extension == VectorExtension.avx2:
                        additional_spec = "x"
                instruction = "return {}_set_{}{}(val{}".format(vector_extension.to_intrin_prefix(), data_type.to_intrin_postfix(), additional_spec, vector_register.element_count-1)
                for i in range(1, vector_register.element_count):
                    parameter += ",\n   typename {vecext}::base_t const val{idx}".format(vecext=vector_register.to_cpp(), idx = vector_register.element_count-i-1)
                    instruction += ", val{}".format(vector_register.element_count-i-1)
                instruction += ");"
                function_code += '''
template< >
NO_DISCARD
FORCE_INLINE
typename {vecext}::vector_t
set< {vecext} > (
   {parameter}
) {{
   {instruction}
}}
                '''.format(
                    vecext=vector_register.to_cpp(),
                    parameter=parameter,
                    instruction=instruction
                )
            indented_init_method_code = "\n".join(
                ["   {0}".format(l) for l in iter(function_code.splitlines())])
            code = '''
#ifndef TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_INTEL_{vecext_upper}_CREATE_{vecext_upper}_H
#define TUDDBS_SIMQ_INCLUDE_GENERATED_SIMD_INSTRUCTIONS_INTEL_{vecext_upper}_CREATE_{vecext_upper}_H
#include <utils/preprocessor.h>
#include <simd/types/simd.h>
#include <simd/types/intel/{vecext_lower}.h>
#include <simd/instructions/declarations/create.h>
#include <cstdint>
namespace tuddbs {{
{code}
}}
#endif
                    '''.format(vecext_upper=str(vector_extension).upper(),vecext_lower=str(vector_extension).lower(), code=indented_init_method_code)
            f.write(code)
            f.close()