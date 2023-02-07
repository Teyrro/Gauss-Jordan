#include <iostream>

#include "../header/SimpleFraction.h"
#include "../header/Matrix.h"
#include "../header/Gauss.h"
#include "../header/FindAllBasicSolutions.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Matrix matrix;
    try {
        GaussMod(matrix);
//        FindBasicSolutions(matrix);
    }
    catch(std::invalid_argument a) {
        std::cout << a.what();
    }

    return 0;
}
