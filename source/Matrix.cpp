//
// Created by vorop on 02.02.2023.
//

#include "../header/Matrix.h"

Matrix::Matrix() {
    std::ifstream file("../Data.txt");
    file >> rowSize;
    file >> columnSize;
    matrix.resize(rowSize* columnSize);
    int i(0);
    while (!file.eof()){
        matrix[i].denominator = 1;
        file >> matrix[i++].numerator;

    }
}

void Matrix::SwapLine(int const & index1, int const & index2){
    if (index1 == index2) return;
    if (index2 == -1) return;
    int line1 = index1 * columnSize;
    int line2 = index2 * columnSize;
    for (int i = 0; i < columnSize; ++i) {
        std::swap(matrix[line1 + i], matrix[line2 + i]);
    }
}

std::ostream& operator<<(std::ostream& out, Matrix const& matrix){
    std::cout << "Matrix: \n";
    for (int i = 0; i < matrix.rowSize; ++i) {
        for (int j = 0; j < matrix.columnSize; ++j) {
            std::cout << matrix(i, j) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}