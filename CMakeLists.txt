cmake_minimum_required(VERSION 3.6)
project(SIMQ)

#################################################
# Get Version Info Start                        #
#################################################
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(SPECS "GIT_BRANCH_CMAKE=\"${GIT_BRANCH}\"")
execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_ABBREV_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "GIT_COMMIT_ABBREV_HASH_CMAKE=\"${GIT_COMMIT_ABBREV_HASH}\"")
execute_process(
        COMMAND git log -1 --format=%H
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "GIT_COMMIT_HASH_CMAKE=\"${GIT_COMMIT_HASH}\"")
execute_process(
        COMMAND git config --get remote.origin.url
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_REMOTE_URL_TMP
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "GIT_REMOTE_URL=\"${GIT_REMOTE_URL_TMP}\"")
execute_process(
        COMMAND uname -s -o -m -r
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE UNAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "BUILD_UNAME_CMAKE=\"${UNAME}\"")
execute_process(
        COMMAND hostname
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE HOSTNAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "BUILD_HOSTNAME_CMAKE=\"${HOSTNAME}\"")
execute_process(
        COMMAND bash "-c" "lscpu | sed -nr '/Model name/ s/  / /g; s/.*:\\s*(.*) @ .*/\\1/p'"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE PROC_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "PROCESSOR_NAME=\"${PROC_NAME}\"")
execute_process(
        COMMAND bash "-c" "lscpu | sed -nr ';s/L1d cache://p' | sed 's/[\\t ]//g'"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE L1d
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "L1D=\"${L1d}\"")
execute_process(
        COMMAND bash "-c" "lscpu | sed -nr ';s/L2 cache://p' | sed 's/[\\t ]//g'"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE L2
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "L2=\"${L2}\"")
execute_process(
        COMMAND bash "-c" "lscpu | sed -nr ';s/L3 cache://p' | sed 's/[\\t ]//g'"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE L3
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "L3=\"${L3}\"")
execute_process(
        COMMAND date "+%d.%m.%Y %H:%M:%S"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE BUILD_TIME
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND SPECS "BUILD_TIME_CMAKE=\"${BUILD_TIME}\"")
IF(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    set(COMPILER_NAME "G++")
ELSEIF(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    set(COMPILER_NAME "Clang++")
ELSE()
    set(COMPILER_NAME "UNKNOWN Compiler ID: ${CMAKE_CXX_COMPILER_ID}" )
ENDIF()
list(APPEND SPECS "BUILD_COMPILER_NAME_CMAKE=\"${COMPILER_NAME}\"" "BUILD_COMPILER_VERSION_CMAKE=\"${CMAKE_CXX_COMPILER_VERSION}\"" "BUILD_COMPILER_PATH_CMAKE=\"${CMAKE_CXX_COMPILER}\"")
#################################################
# Get Version Info End                          #
#################################################


add_definitions(-std=c++17)
IF(${CPLATFORM} MATCHES "INTEL")
    set(GENERAL_LINK_OPTIONS "-static-libgcc;-static-libstdc++")
    set(GENERAL_COMPILE_DEFINITIONS "${SPECS};C17=True;X86=True;INTRIN=True;INTEL_SIMDI=True")
    IF(${CPROC} MATCHES "XEON")
        message("Platform Intel X86 XEON")
        set(GENERAL_COMPILE_DEFINITIONS "${GENERAL_COMPILE_DEFINITIONS};XEON=True;INTEL_INTRINSICS_AVX512_VL=True;INTEL_INTRINSICS_AVX512_DQ=True;INTEL_INTRINSICS_AVX512_BW=True;INTEL_INTRINSICS_AVX512_F=True")
        set(GENERAL_COMPILE_OPTIONS "-msse2;-msse4.2;-mpclmul;-mavx2;-mavx512f;-mavx512bw;-mavx512vl;-mavx512dq")
    ELSEIF(${CPROC} MATCHES "KNL")
        message("Platform Intel X86 XEON PHI KNL")
        set(GENERAL_COMPILE_DEFINITIONS "${GENERAL_COMPILE_DEFINITIONS};KNL=True;INTEL_INTRINSICS_AVX512_F=True")
        #Since mcdram does not have any effects we omit it here (HAS_MCD=True)
        set(GENERAL_COMPILE_OPTIONS "-msse4.2;-mpclmul;-mavx2;-mavx512f;-march=knl;-lmemkind")
        set(GENERAL_LINK_OPTIONS "${GENERAL_LINK_OPTIONS};-lmemkind")
    ENDIF()
    message("CXX-Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
    IF(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
        message("--- Using Clang")
        set(BENCHMARK_VECTOR_COMPILE_OPTIONS "-fno-slp-vectorize")
    ELSEIF(${CMAKE_CXX_COMPILER_ID} MATCHES "Intel")
        message("--- Using ICC")
        set(BENCHMARK_VECTOR_COMPILE_OPTIONS "")
    ELSE()
        message("--- Using GCC")
        set(BENCHMARK_VECTOR_COMPILE_OPTIONS "-fno-tree-vectorize")
    ENDIF()
    IF(${CMAKE_CXX_COMPILER_ID} MATCHES "Intel")
        set(BENCHMARK_COMPILE_OPTIONS "-ipo;-O2;-static;-march=skylake;-xSKYLAKE")

        set(BENCHMARK_LINK_OPTIONS "-ipo")

        set(TEST_COMPILE_DEFINITIONS "SIMQ_DEBUG=True;MEMORY_DEBUG=True")
        set(TEST_COMPILE_OPTIONS "-O0;-debug")

        set(GENERAL_COMPILE_WARNINGS_DEFINITIONS "-Werror;-Wall;-Wextra;-Wno-unused-parameter;-Wno-uninitialized;-Wno-missing-braces;-pedantic")
    ELSE()

        set(BENCHMARK_COMPILE_OPTIONS "-O3;-flto;${BENCHMARK_VECTOR_COMPILE_OPTIONS}")
        message(${BENCHMARK_COMPILE_OPTIONS})
        set(BENCHMARK_LINK_OPTIONS "-flto")

        set(TEST_COMPILE_DEFINITIONS "SIMQ_DEBUG=True;MEMORY_DEBUG=True")
        set(TEST_COMPILE_OPTIONS "-O0;-g")
        set(GENERAL_COMPILE_WARNINGS_DEFINITIONS "-Werror;-Wall;-Wextra;-Wno-ignored-attributes;-Wno-unused-parameter;-Wno-uninitialized;-Wno-missing-braces;-pedantic;-Wno-unused-command-line-argument")
    ENDIF()

ELSEIF(${CPLATFORM} MATCHES "ARM")
    set(GENERAL_LINK_OPTIONS "-static-libgcc;-static-libstdc++")
    message("Platform ARM")
    set(GENERAL_COMPILE_DEFINITIONS "${SPECS};C17=True;INTRIN=True;ARM_SIMDI=True")
    set(GENERAL_COMPILE_OPTIONS "-march=armv8-a+crypto")
    IF(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
        message("--- Using Clang")
        set(BENCHMARK_VECTOR_COMPILE_OPTIONS "-fno-slp-vectorize")
    ELSEIF(${CMAKE_CXX_COMPILER_ID} MATCHES "Intel")
        message("--- Using ICC")
        set(BENCHMARK_VECTOR_COMPILE_OPTIONS "")
    ELSE()
        message("--- Using GCC")
        set(BENCHMARK_VECTOR_COMPILE_OPTIONS "-fno-tree-vectorize")
    ENDIF()
    IF(${CMAKE_CXX_COMPILER_ID} MATCHES "Intel")
        set(BENCHMARK_COMPILE_OPTIONS "-ipo;-O2;-static;-march=skylake;-xSKYLAKE")

        set(BENCHMARK_LINK_OPTIONS "-ipo")

        set(TEST_COMPILE_DEFINITIONS "SIMQ_DEBUG=True;MEMORY_DEBUG=True")
        set(TEST_COMPILE_OPTIONS "-O0;-debug")

        set(GENERAL_COMPILE_WARNINGS_DEFINITIONS "-Werror;-Wall;-Wextra;-Wno-unused-parameter;-Wno-uninitialized;-Wno-missing-braces;-pedantic")
    ELSE()

        set(BENCHMARK_COMPILE_OPTIONS "-O3;-flto;${BENCHMARK_VECTOR_COMPILE_OPTIONS}")
        message(${BENCHMARK_COMPILE_OPTIONS})
        set(BENCHMARK_LINK_OPTIONS "-flto")

        set(TEST_COMPILE_DEFINITIONS "SIMQ_DEBUG=True;MEMORY_DEBUG=True")
        set(TEST_COMPILE_OPTIONS "-O0;-g")
        set(GENERAL_COMPILE_WARNINGS_DEFINITIONS "-Werror;-Wall;-Wextra;-Wno-ignored-attributes;-Wno-unused-parameter;-Wno-uninitialized;-Wno-missing-braces;-pedantic;-Wno-unused-command-line-argument")
    ENDIF()
ENDIF()

#    set(BENCHMARK_COMPILE_DEFINITIONS "NDEBUG;EXPERIMENT_MEASUREMENT_REPETITION_COUNT=500;EXPERIMENT_THROUGHPUT_TIME_SLOT=30")
set(BENCHMARK_COMPILE_DEFINITIONS "NDEBUG;EXPERIMENT_MEASUREMENT_REPETITION_COUNT=50;EXPERIMENT_THROUGHPUT_TIME_SLOT=30;EXPERIMENT_THROUGHPUT_THREAD_BUDGET=8")
#    set(BENCHMARK_COMPILE_DEFINITIONS "NDEBUG;EXPERIMENT_MEASUREMENT_REPETITION_COUNT=1;EXPERIMENT_THROUGHPUT_TIME_SLOT=1;EXPERIMENT_THROUGHPUT_THREAD_BUDGET=8")

include_directories( ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/submodules/memory_decorator/include ${PROJECT_SOURCE_DIR}/src )

#enable_testing()
#add_subdirectory(test)

add_subdirectory(src)
