source ./env.sh
BASE=`pwd`
INSTALL=/home/happen/baidu/bdg/doris/thirdparty/installed
PARALLEL=56

#cd thirdparty/boost_1_73_0
#./bootstrap.sh --prefix=$INSTALL
#./b2 link=static runtime-link=static -j$PARALLEL --without-mpi --without-graph --without-graph_parallel --without-python cxxflags="-std=c++11 -g -fPIC" install

#cd $BASE
#cd thirdparty/googletest-release-1.8.0
#mkdir build;cd build;cmake .. -DCMAKE_INSTALL_PREFIX=$INSTALL;make -j $PARALLEL;make install

#cd $BASE
#cd thirdparty/cityhash102
#rm -rf build;mkdir build;cd build;cmake .. ;make -j $PARALLEL
#cp libcityhash.a $INSTALL/lib
#cp ../include/* $INSTALL/include

#cd $BASE
#cd thirdparty/fmt-7.1.3
#rm -rf build;mkdir build;cd build;cmake .. -DCMAKE_INSTALL_PREFIX=$INSTALL;make -j $PARALLEL;make install

cd $BASE
mkdir build;
cd build;
cmake .. -DCMAKE_BUILD_TYPE=Debug && make -j$PARALLEL 
