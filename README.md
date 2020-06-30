

# Prerequisites

Docker v. 19

## Install Docker (Arch Linux)
This is a short description for installing docker on an ARCH Linux distribution. If you run a different distribution, 
you can find a description here: https://docs.docker.com/engine/install/ .

    sudo pacman -S docker #install docker
    sudo systemctl enable docker #Enable docker daemon
    sudo sysytemctl start docker #Start docker daemon
    grep docker /etc/group #Check whether docker group exists 
    #groupadd docker #if not: create it
    systemctl restart docker #if not: restart it
    ls -la /var/run/docker.sock #socket should be owned by docker group
    usermod -aG docker (user) #add user to docker group
    #log out, log in again

# Checkout

    $ git clone --recurse-submodules https://github.com/JPietrzykTUD/SIMQ.git
    
# Prepare
There are two options to get the docker images: Build it from scratch (I) or download it from docker hub (II).

## Build it from scratch
    
    $ ./build_docker.sh # initial step (needs to be executed just once)
    
## Download it from docker hub

    $ docker pull jpietrzyktud/simq:damon2020
    $ docker tag 59f0124b7651 simq_ubuntu:1.0
    
# Building
    
    $ ./build.sh -p PLATFORM -c COMPILER
    
    # PLATFORM : COMPILER
    #  intel   : gcc | clang 

`${PROJECT_ROOT}/bin` contains the built artifacts.

# Run Benchmark

    $ ./run_benchmark.sh
    
First all executables are listed like that:

    $ ./run_benchmark.sh
    [0]: ./intel/clang/benchmarks/micro_benchmark_build_variants_intel_xeon
    [1]: ./intel/clang/benchmarks/benchmark_query_1_1_damon2020_intel_xeon
    ...
    Choose file to execute (0-xxx): 

Choose a file to execute (maybe no test case ;) ) and wait until the script is done.

The results will be in `${PROJECT_ROOT}/benchmark/${PLATFORM}/${COMPILER_NAME}/benchmarks/[raw|processed]`


# Removing docker image
    
    ./remove_docker.sh
