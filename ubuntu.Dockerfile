FROM ubuntu:19.10

#ENV DEBIAN_FRONTEND noninteractive

RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt-get update 
RUN apt-get -y install apt-utils libprotobuf-dev protobuf-compiler cmake g++ clang

ENV TZ=Europe/Berlin
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get -y install build-essential checkinstall 
RUN apt-get -y install libreadline-gplv2-dev libncursesw5-dev libssl-dev wget \
    libsqlite3-dev tk-dev libgdbm-dev libc6-dev libbz2-dev libffi-dev zlib1g-dev \
    libmemkind0 libmemkind-dev git

RUN cd /opt                                                       &&\
    wget https://www.python.org/ftp/python/3.8.2/Python-3.8.2.tgz &&\
    tar xzf Python-3.8.2.tgz                                      &&\
    cd /opt/Python-3.8.2                                          &&\
    ./configure --enable-optimizations                            &&\
    make altinstall 

RUN apt-get -y install python3-pip python3-seaborn python3-pandas

RUN python3 -m pip install --upgrade pandas

RUN cmake --version|head -1 &&\
    clang --version|head -1 &&\
    g++   --version|head -1 &&\
    python3.8 -V            &&\
    pip3 freeze|grep pandas  &&\
    pip3 freeze|grep seaborn

RUN mkdir /src /dst

ENTRYPOINT ["/bin/bash"]

