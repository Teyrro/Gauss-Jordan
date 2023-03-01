#include <iostream>

#include "../header/SimpleFraction.h"
#include "../header/Matrix.h"
#include "../header/Gauss.h"
#include "../header/FindAllBasicSolutions.h"
#include "../header/SimplexTable.h"
#include "../header/SimplexMethod.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
//    Matrix matrix;
    try {
        SimplexTable table = SimplexTable();
//        std::cout << table;
        SimplexMethod(table);
    }
    catch(const char* a) {
        std::cout << a;
    }
    catch(std::invalid_argument a) {
        std::cout << a.what();
    }

    return 0;
}
