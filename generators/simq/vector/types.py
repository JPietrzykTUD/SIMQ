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
from enum import Enum

from simq.general.general import ColumnQueryPair


class VectorExtension(Enum):
   sse = 128
   avx2 = 256
   avx512 = 512
   def __str__(self):
      return "{}".format(self.name)
   def to_intrin_prefix(self):
      result = "_mm"
      if self.value==128:
         return "{}".format(result)
      elif self.value==16384:
         return "_vel"
      else:
         return "{}{}".format(result, self.value)


class DataType(Enum):
   uint8_t = 8
   uint16_t = 16
   uint32_t = 32
   uint64_t = 64
   def __str__(self):
      return "{}".format(self.name)
   def to_intrin_postfix(self):
      return "epi{}".format(self.value)

class VectorSpec:
   def __init__(self, vector_extension: VectorExtension, data_type_list: list):
      self.vector_extension = vector_extension
      self.data_type_list = data_type_list

class VectorRegister:
   def __init__(self, vector_extension: VectorExtension, data_type: DataType):
      self.vector_extension = vector_extension
      self.data_type = data_type
      self.element_count = int(vector_extension.value / data_type.value)
      self.mask_size = self.__get_mask_size(vector_extension, data_type)

   def get_column_query_count_list(self):
      result = []
      query_count = 1
      while query_count <= self.element_count:
         column_count = 1
         while column_count <= query_count:
            result.append(
               ColumnQueryPair(
                  column_count,
                  query_count
               )
            )
            column_count *= 2
         query_count *= 2
      return result

   def __get_mask_size(self, vector_extension: VectorExtension, data_type: DataType):
      val = int(vector_extension.value / data_type.value)
      if val < 8:
         return 8
      else:
         return val

   def __str__(self):
      return "{}({})".format(self.vector_extension, self.data_type)

   def to_cpp(self):
      return "{}< {} >".format(self.vector_extension, self.data_type)