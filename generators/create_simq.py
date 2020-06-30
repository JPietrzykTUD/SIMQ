import copy
from pathlib import Path

# from intel.mask_broadcast_gen import MaskBroadCastCreator
#
# from simq.file_io.file_template import file_replace
#
# base_path = str(Path(__file__).parents[2])
#
# intel_path = "{}/include/generated/simq/intel/mask_broadcast".format(base_path)
# Path(intel_path).mkdir(parents=True, exist_ok=True)
# # mbcc = MaskBroadCastCreator(intel_path, base_path)
# # mbcc.create_all()
#
# copyfile("{}/test_template.h".format(intel_path), "{}/test.h".format(intel_path))
# # f = open("{}/test.h".format(intel_path), "w")
# file_replace("{}/test.h".format(intel_path), "@test", "yolo")
from simq.build_variants.buffer.buffer import write_SIMQBuilderBuffer_to_file
from simq.build_variants.mask_broadcast.mask_boradcast import write_SIMQBuilderMaskBroadCast_to_file
from simq.build_variants.set.set import write_SIMQBuilderSET_to_file
from simq.general.simq_vector_view import write_SIMQVectorView_to_file
from simq.vector.intel.instructions import CreateIntrinsicCreator
from simq.vector.types import VectorExtension, DataType, VectorSpec


# svv = SIMQVectorView(VectorRegister(VectorExtension.avx512, DataType.uint16_t), 2, 8)
# print("{}".format(svv.to_cpp()))


vector_spec_list_intel =[
    VectorSpec(VectorExtension.sse, [
        DataType.uint8_t,
        DataType.uint16_t,
        DataType.uint32_t,
        DataType.uint64_t,
    ]),
    VectorSpec(VectorExtension.avx2, [
        DataType.uint8_t,
        DataType.uint16_t,
        DataType.uint32_t,
        DataType.uint64_t,
    ]),
    VectorSpec(VectorExtension.avx512, [
        DataType.uint8_t,
        DataType.uint16_t,
        DataType.uint32_t,
        DataType.uint64_t,
    ])
]

def create_simqvector_view_structs(base_path: str):
    vector_spec = copy.deepcopy(vector_spec_list_intel)
    intel_path = "{}/include/generated/simq/control/vector_builder".format(base_path)
    Path(intel_path).mkdir(parents=True, exist_ok=True)
    write_SIMQVectorView_to_file(
        "{}/vector_view".format(intel_path),
        vector_spec
    )

def create_mask_broadcast_impl(base_path: str):
    intel_path = "{}/include/generated/simq/control/vector_builder/build_variants/broadcast".format(base_path)
    Path(intel_path).mkdir(parents=True, exist_ok=True)
    write_SIMQBuilderMaskBroadCast_to_file(
        "{}/mask_broadcast".format(intel_path),
        vector_spec_list_intel
    )

def create_set_impl(base_path: str):
    intel_path = "{}/include/generated/simq/control/vector_builder/build_variants/set".format(base_path)
    Path(intel_path).mkdir(parents=True, exist_ok=True)
    write_SIMQBuilderSET_to_file(
        "{}/set".format(intel_path),
        vector_spec_list_intel
    )

def create_buffer_impl(base_path: str):
    intel_path = "{}/include/generated/simq/control/vector_builder/build_variants/buffer".format(base_path)
    Path(intel_path).mkdir(parents=True, exist_ok=True)
    write_SIMQBuilderBuffer_to_file(
        "{}/buffer".format(intel_path),
        vector_spec_list_intel
    )

def create_intel_intrinsics(base_path:str):
    a = CreateIntrinsicCreator("{}/include/generated/simd".format(base_path))
    a.create_function_definition()
    a.create_function_implementation()

print("{}".format(str(Path(__file__))))
base_path = str(Path(__file__).resolve().parents[1])
create_simqvector_view_structs(base_path)
create_mask_broadcast_impl(base_path)
create_set_impl(base_path)
create_buffer_impl(base_path)
create_intel_intrinsics(base_path)