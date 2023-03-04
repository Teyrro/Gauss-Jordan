//
// Created by vorop on 02.02.2023.
//

#include <iomanip>
#include "Matrix.h"

Matrix::Matrix(std::string filename) {
    std::ifstream file(filename);
    file >> rowCount;
    file >> columnCount;
    std::vector<SimpleFraction> a(rowCount * columnCount);
    int i(0);
    while (i < a.size()){
        a[i].denominator = 1;
        file >> a[i++].numerator;
    }
    matrix = std::move(a);
}

void Matrix::SwapLine(int const & index1, int const & index2) {
    if (index1 == index2) return;
    if (index2 < 0 or index2 >= rowCount or index1 < 0 or index1 >= rowCount) return;

    int line1 = index1 * columnCount;
    int line2 = index2 * columnCount;
    for (int i = 0; i < columnCount; ++i) {
        std::swap(matrix[line1 + i],
                  matrix[line2 + i]);
    }


}

void Matrix::resize(int size){
    matrix.resize(size);
}

void CheckMatrixOnZeroLine(Matrix& matrix){
    for (int i = matrix.rowCount - 1 ; i >= 0; --i) {
        int countZero(0);
        for (int j = matrix.columnCount - 1; j >= 0; --j)
            if (matrix(i, j) == SimpleFraction(0, 1)) ++countZero;

        if (countZero == matrix.columnCount){
            matrix.resize(matrix.columnCount * matrix.rowCount - countZero);
            matrix.rowCount -= 1;
        }
    }
}



std::ostream& operator<<(std::ostream& out, Matrix const& matrix){
    out << "Matrix: \n";
    for (int i = 0; i < matrix.rowCount; ++i) {
        for (int j = 0; j < matrix.columnCount; ++j) {
            out << std::setiosflags(std::ios::left);
            out << std::setw(15) << matrix(i, j);
        }
        out << "\n";
    }
    out << "\n";
    return out;
}