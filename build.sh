source ./env.sh
BASE=`pwd`
PARALLEL=56

make

cd $BASE
mkdir build;
cd build;
cmake .. -DCMAKE_BUILD_TYPE=Debug && make -j$PARALLEL 
