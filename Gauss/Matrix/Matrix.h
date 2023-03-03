

#ifndef UNTITLED1_MATRIX_H
#define UNTITLED1_MATRIX_H

#include <iostream>
#include "vector"
#include "stdexcept"
#include "fstream"
#include "../SimpleFration/SimpleFraction.h"

class Matrix {
    std::vector<SimpleFraction> matrix;
public:
    int rowCount;
    int columnCount;
    Matrix(int row, int column) : rowCount(row), columnCount(column) {
        matrix.resize(row * column);
    }

    Matrix(int row, int column, std::vector<SimpleFraction> a) : rowCount(row), columnCount(column), matrix(a) {
    }

    Matrix(std::string filename);

    SimpleFraction operator()(int row, int column){
        if (row >= rowCount or column >= columnCount or row < 0 or column < 0) throw std::invalid_argument("Overwrite");
        return matrix[row * columnCount + column];
    }

    SimpleFraction operator()(int row, int column) const{
        if (row >= rowCount or column >= columnCount or row < 0 or column < 0) throw std::invalid_argument("Overwrite");
        return matrix[row * columnCount + column];
    }

    void operator()(int row, int column, SimpleFraction inputAnswer){
        if (row >= rowCount or column >= columnCount or row < 0 or column < 0) throw std::invalid_argument("Overwrite");
        matrix[row * columnCount + column] = inputAnswer;
    }


    void SwapLine(int const & index1, int const & index2);

    void resize(int size);

};

void CheckMatrixOnZeroLine(Matrix& matrix);

std::ostream& operator<<(std::ostream& out, Matrix const& matrix);


#endif //UNTITLED1_MATRIX_H
