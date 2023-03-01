cmake_minimum_required(VERSION 3.24)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled1 source/main.cpp source/Matrix.cpp header/Matrix.h source/Gauss.cpp header/Gauss.h source/SimpleFraction.cpp header/SimpleFraction.h source/FindAllBasicSolutions.cpp header/FindAllBasicSolutions.h source/SimplexTable.cpp header/SimplexTable.h header/SimplexMethod.h source/SimplexMethod.cpp source/StuffForGauss.cpp header/StuffForGauss.h)
