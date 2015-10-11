#This script is for ubuntu 14.04 ONLY

sudo apt-get install \
    g++ \
    automake \
    autoconf \
    autoconf-archive \
    libtool \
    libboost-all-dev \
    libevent-dev \
    libdouble-conversion-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    liblz4-dev \
    liblzma-dev \
    libsnappy-dev \
    make \
    zlib1g-dev \
    binutils-dev \
    libjemalloc-dev \
    libssl-dev \
    libiberty-dev \
    flex \
    bison \
    libkrb5-dev \
    libsasl2-dev \
    libnuma-dev \
    pkg-config \
    libssl-dev

pushd /tmp

git clone https://github.com/facebook/folly.git
cd folly/folly
autoreconf -ivf
./configure
make
make check
sudo make install

cd /tmp
git clone https://github.com/facebook/fbthrift.git
cd fbthrift/thrift/
./build/deps_ubuntu_14.04.sh

cd /tmp
git clone https://github.com/facebook/thpp.git
cd thpp/thpp
./build.sh

sudo python setup.py install

popd