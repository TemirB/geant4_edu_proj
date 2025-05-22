rm -rf build
mkdir build
cd build
mkdir results
cmake ..
make
cp ../res/init_vis.mac .
cp ../res/vis.mac .
make ../res