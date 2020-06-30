#!/bin/bash
echo "$0  Copyright (C) 2020  Johannes Pietrzyk"
echo "This program comes with ABSOLUTELY NO WARRANTY."
echo "This is free software, and you are welcome to redistribute it"
echo "under certain conditions."

while getopts "p:c:" options; do
   case $options in
      p) platform=$OPTARG
         if [[ "$platform" != "intel" ]]; then
            echo "Unknown platform $platform"
            echo "Only intel supported so far."
            exit 1
         fi
         ;;
      c) compiler=$OPTARG
         if [[ "$compiler" != "gcc" ]] && [[ "$compiler" != "clang" ]] && [[ "$compiler" != "icc" ]]; then
            echo "Unknown compiler $compiler"
            echo "Only gcc, clang and icc supported so far."
            exit 1
         fi
         ;;
      \?) echo "Usage: ./build.sh -p intel -c COMPILER"
          echo "COMPILER:"
          echo "   On intel platforms:"
          echo "      (gcc|clang|icc)"
          exit 0
         ;;
   esac
done
shift $((OPTIND -1))
SCRIPTROOT=$(pwd)
BUILDPATH="$platform/$compiler"
mkdir -p $SCRIPTROOT/build/$BUILDPATH
mkdir -p $SCRIPTROOT/bin/$BUILDPATH
mkdir -p $SCRIPTROOT/bin/$BUILDPATH/benchmarks
mkdir -p $SCRIPTROOT/bin/$BUILDPATH/tests
echo "Generating required header files... "
./run_docker.sh
./exec_docker.sh simq_container ./generate_cfiles.sh "/src/generators"
docker rm simq_container --force
echo "Generating finished."

if [[ "$platform" == "intel" ]]; then
   PLATFORM="-DCPLATFORM=INTEL"
   lscpu | sed -nr '/Model name/ s/.*:\s*(.*) @ .*/\1/p' | grep 'Gold'
   if [[ $? -eq 0 ]]; then
      echo -n "Xeon Gold detected."
      PLATFORM="${PLATFORM} -DCPROC=XEON"
   else
      lscpu | sed -nr '/Model name/ s/.*:\s*(.*) @ .*/\1/p' | grep 'Phi'
      if [[ $? -eq 0 ]]; then
         echo "Xeon Phi detected."
         PLATFORM="${PLATFORM} -DCPROC=KNL"
      else
         echo "Unsupported Processor."
         exit 1
      fi
   fi
   if [[ "$compiler" == "icc" ]]; then
      COMPPATH=$(dirname $(which icc))
      COMPC="-DCMAKE_C_COMPILER=${COMPPATH}/icc"
      COMPCXX="-DCMAKE_CXX_COMPILER=${COMPPATH}/icpc"
      COMPADD=""
      INSTALL_PATH="${SCRIPTROOT}/bin/${BUILDPATH}"
      INSTALL_BENCHMARK_PATH="-DCMAKE_INSTALL_PATH=${INSTALL_PATH}/benchmarks"
      INSTALL_TEST_PATH="-DCMAKE_INSTALL_TEST_PATH=${INSTALL_PATH}/tests"
      ./build_sources.sh build/$BUILDPATH $SCRIPTROOT $INSTALL_BENCHMARK_PATH $INSTALL_TEST_PATH $COMPC $COMPCXX $COMPADD $PLATFORM
   else
      if [[ "$compiler" == "gcc" ]]; then
         COMPC="-DCMAKE_C_COMPILER=gcc"
         COMPCXX="-DCMAKE_CXX_COMPILER=g++"
         COMPADD=""
      elif [[ "$compiler" == "clang" ]]; then
         COMPC="-DCMAKE_C_COMPILER=clang"
         COMPCXX="-DCMAKE_CXX_COMPILER=clang++"
         COMPADD=""
      fi
      INSTALL_PATH="/dst_bin/${BUILDPATH}"
      INSTALL_BENCHMARK_PATH="-DCMAKE_INSTALL_PATH=${INSTALL_PATH}/benchmarks"
      INSTALL_TEST_PATH="-DCMAKE_INSTALL_TEST_PATH=${INSTALL_PATH}/tests"
      USER=$(whoami)
      ./run_docker.sh
      ./exec_docker.sh simq_container ./build_sources.sh "/dst_build/$BUILDPATH /src $INSTALL_BENCHMARK_PATH $INSTALL_TEST_PATH $COMPC $COMPCXX $COMPADD $PLATFORM"
      docker rm simq_container --force
   fi
   cd $SCRIPTROOT
fi