[[ -s "./env.sh" ]] && source "./env.sh"

BASE=`pwd`
PARALLEL=56

make

cd $BASE
mkdir build;
cd build;
cmake .. -DCMAKE_BUILD_TYPE=Debug $LIBRT -DSNAPPY_BUILD_BENCHMARKS=OFF -DSNAPPY_BUILD_TESTS=OFF && make -j$PARALLEL 
