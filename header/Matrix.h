

#ifndef UNTITLED1_MATRIX_H
#define UNTITLED1_MATRIX_H

#include <iostream>
#include "vector"
#include "stdexcept"
#include "fstream"
#include "SimpleFraction.h"

class Matrix {
    std::vector<SimpleFraction> matrix;
public:
    int rowSize;
    int columnSize;
    Matrix(int row, int column, std::vector<SimpleFraction>& a) : rowSize(row), columnSize(column), matrix(a) {

    }

    Matrix();

    SimpleFraction operator()(int row, int column){
        if (row > rowSize or column > columnSize) throw std::invalid_argument("Overwrite");
        return matrix[row * columnSize + column];
    }

    SimpleFraction operator()(int row, int column) const{
        if (row > rowSize or column > columnSize) throw std::invalid_argument("Overwrite");
        return matrix[row * columnSize + column];
    }

    void operator()(int row, int column, SimpleFraction inputAnswer){
        if (row > rowSize or column > columnSize) throw std::invalid_argument("Overwrite");
        matrix[row * columnSize + column] = inputAnswer;
    }

    void SwapLine(int const & index1, int const & index2);

    void PrintM(){

    }



};

std::ostream& operator<<(std::ostream& out, Matrix const& matrix);


#endif //UNTITLED1_MATRIX_H
