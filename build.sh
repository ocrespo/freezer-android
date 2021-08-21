rm -R -f build
rm -R -f Debug
git submodule deinit -f .
git submodule init
git submodule update
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX:PATH=.. -DCMAKE_C_COMPILER="clang" -DCMAKE_CXX_COMPILER="clang++" -DCMAKE_PREFIX_PATH="${HOME}/Qt/5.10.0/gcc_64/lib" ..
make VERBOSE=1 install