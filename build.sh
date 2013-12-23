# !/bin/bash

make clean

if make; then
echo "LIB BUILD OOK!"
echo
fi

g++ -std=c++11 ./tests/plotter.cpp -I./include -I /usr/include/qt4/ -L./lib -ltecplotlib  -lmgl -lmgl-qt -o ./plotter