#include <iostream>

#include "Gauss/SimpleFration/SimpleFraction.h"
#include "Gauss/Matrix/Matrix.h"
#include "Gauss/Gauss.h"
#include "AllBasicSolutions/FindAllBasicSolutions.h"
#include "SimplexMethod/SimplexTable.h"
#include "SimplexMethod/SimplexMethod.h"
#include "MethodArtificialBasis/ArtificialTable.h"
#include "MethodArtificialBasis/MethodArtificialBasis.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
//    Matrix matrix;
    std::vector<std::string> fileName = {{"../MatrixData.txt"}, {"../BasicData.txt"}, {"../Data.txt"}};
    try {
        ArtificialTable table = ArtificialTable(fileName[2]);
        std::cout << table;
        MethodArtificialBasis(table);
//        SimplexTable table = SimplexTable(fileName[2]);
//        SimplexMethod(table);

//        Matrix m = Matrix(fileName[1]);
//        FindBasicSolutions(m, false);
    }
    catch(const char* a) {
        std::cout << a;
    }
    catch(std::invalid_argument a) {
        std::cout << a.what();
    }

    return 0;
}
