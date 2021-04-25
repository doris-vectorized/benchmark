export CC=gcc
export CXX=g++
export BOOST_ROOT=./thirdparty/boost_1_73_0
export FMT_ROOT=./thirdparty/fmt-7.1.3
export CITY_HASH=./thirdparty/cityhash102
export THIRDPARTY_INSTALL=$(shell pwd)/thirdparty/install
export PARALLEL=16

all: boost fmt cityhash
	echo "hello $(CC)"

boost: $(THIRDPARTY_INSTALL)/include/boost

fmt: $(THIRDPARTY_INSTALL)/include/fmt

cityhash: $(THIRDPARTY_INSTALL)/include/city.h

$(THIRDPARTY_INSTALL)/include/boost:
	cd $(BOOST_ROOT);./bootstrap.sh --prefix=$(THIRDPARTY_INSTALL);	./b2 link=static runtime-link=static -j$(PARALLEL) --without-mpi --without-graph --without-graph_parallel --without-python cxxflags="-std=c++17 -g -fPIC" install
	echo "boost finish"

$(THIRDPARTY_INSTALL)/include/fmt:
	cd $(FMT_ROOT);rm -rf build;mkdir build;cd build;cmake .. -DFMT_TEST=OFF -DCMAKE_INSTALL_PREFIX=$(THIRDPARTY_INSTALL);make -j $(PARALLEL);make install
	echo "fmt finish"	
$(THIRDPARTY_INSTALL)/include/city.h:
	cd $(CITY_HASH);rm -rf build;mkdir build;cd build;cmake .. ;make -j $(PARALLE);cp libcityhash.a $(THIRDPARTY_INSTALL)/lib;cp ../include/* $(THIRDPARTY_INSTALL)/include
	echo "cityhash finish"
