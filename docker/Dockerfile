FROM ubuntu:xenial

USER root

RUN apt-get update && \
    apt install -y software-properties-common && \
    add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    apt-get update && \
    apt-get install -y build-essential cmake libtool autoconf libboost-all-dev libboost-filesystem-dev libboost-iostreams-dev libboost-serialization-dev libboost-thread-dev libboost-test-dev libsqlite3-dev libssl-dev autogen libcurl4-openssl-dev libjsoncpp-dev libjsonrpccpp-dev libjsonrpccpp-tools libsnappy-dev zlib1g-dev libbz2-dev liblz4-dev libzstd-dev libjemalloc-dev libsparsehash-dev gcc-7 g++-7 python3-dev python3-pip git wget curl liblmdb-dev libsparsehash-dev libargtable2-dev libmicrohttpd-dev libhiredis-dev catch libgflags-dev && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-7

RUN cd /root && \
    wget https://cmake.org/files/v3.10/cmake-3.10.0.tar.gz && \
    tar xzf cmake-3.10.0.tar.gz && \
    cd cmake-3.10.0/ && \
    cmake . && \
    make && \
    make install

ENV CMAKE_ROOT /root/cmake-3.10.0/

RUN cd /root && \
    git clone https://github.com/fyp2k18/BlockSci.git && \
    # git clone https://github.com/citp/BlockSci.git && \
    cd BlockSci && \
    mkdir release && \
    cd release && \
    CC=gcc-7 CXX=g++-7 cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_BUILD_TYPE=Release .. && \
    make && \
    make install

RUN cd /root/BlockSci && \
    pip3 install --upgrade pip && \
    hash -r pip3 && \
    CC=gcc-7 CXX=g++-7 pip3 install -e blockscipy && \
    pip3 install --upgrade jupyter

RUN curl -L https://github.com/krallin/tini/releases/download/v0.6.0/tini > tini && \
    echo "d5ed732199c36a1189320e6c4859f0169e950692f451c03e7854243b95f4234b *tini" | sha256sum -c - && \
    mv tini /usr/local/bin/tini && \
    chmod +x /usr/local/bin/tini

RUN mkdir -p -m 700 /root/.jupyter/ && \
    echo "c.NotebookApp.ip = '*'" >> /root/.jupyter/jupyter_notebook_config.py && \
    echo "c.NotebookApp.password = u'sha1:b7059f178a65:0f131166db948c9d7df378dc378ecd661b490d3e'" >> /root/.jupyter/jupyter_notebook_config.py

EXPOSE 8888
