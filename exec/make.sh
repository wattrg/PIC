#!/bin/bash

cd ../lua-5.3.5/src
make linux
cd ../../exec



g++ ../src/main.cpp                                          \
../src/particle.cpp                                          \
../src/advance.cpp                                           \
../src/mesh.cpp                                              \
../src/EM.cpp                                                 \
../src/io.cpp \
-o PIC.ex                                                    \
-I ../lua-5.3.5/src/                                         \
-I ../LuaBridge/Source/LuaBridge/                            \
-I ../LuaBridge/Source/                                      \
-I ../LuaBridge/Source                                       \
-L ../lua-5.3.5/src/ -llua -ldl 