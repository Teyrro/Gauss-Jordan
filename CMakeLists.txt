cmake_minimum_required(VERSION 3.24)
project(untitled1)

set(CMAKE_CXX_STANDARD 23)

add_executable(untitled1 main.cpp Gauss/Matrix/Matrix.cpp Gauss/Matrix/Matrix.h Gauss/Gauss.cpp Gauss/Gauss.h Gauss/SimpleFration/SimpleFraction.cpp Gauss/SimpleFration/SimpleFraction.h AllBasicSolutions/FindAllBasicSolutions.cpp AllBasicSolutions/FindAllBasicSolutions.h SimplexMethod/SimplexTable.cpp SimplexMethod/SimplexTable.h SimplexMethod/SimplexMethod.h SimplexMethod/SimplexMethod.cpp Gauss/StuffForGauss.cpp Gauss/StuffForGauss.h MethodArtificialBasis/MethodArtificialBasis.cpp MethodArtificialBasis/MethodArtificialBasis.h MethodArtificialBasis/ArtificialTable.cpp MethodArtificialBasis/ArtificialTable.h)
