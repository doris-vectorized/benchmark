[[ -s "./env.sh" ]] && source "./env.sh"

BASE=`pwd`
PARALLEL=56

make

cd $BASE
mkdir build;
cd build;
cmake .. -DCMAKE_BUILD_TYPE=Debug $LIBRT && make -j$PARALLEL 
