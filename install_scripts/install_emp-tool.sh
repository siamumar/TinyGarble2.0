
git clone https://github.com/siamumar/emp-tool.git
cd emp-tool
cmake . -DCMAKE_INSTALL_PREFIX=../include
make -j 
make install -j 
cd ..