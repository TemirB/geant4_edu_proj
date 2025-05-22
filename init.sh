rm -rf build
mkdir build
cd build
cmake ..
make
cp ../init_vis.mac .
cp ../vis.mac .
./main.exe