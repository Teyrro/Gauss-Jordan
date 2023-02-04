//
// Created by vorop on 02.02.2023.
//

#include <map>
#include "../header/Gauss.h"

int Validate(Matrix& a){
    return a.columnSize != a.rowSize + 1;
}

int preparencetoWork(int f, Matrix& matrix, std::pair<int, int>& coordChange,
                     std::map<int, SimpleFraction>& columnChange){
    std::pair<int, int> coord = std::make_pair(-1, -1);
    for (int findOne = f; findOne < matrix.columnSize; ++findOne) {
        if (matrix(f, findOne) != SimpleFraction(0, 1)) {
            coord = std::make_pair(f, findOne);
            break;
        }
    }
    if (coord == std::make_pair(-1, -1)) return 1;
    else coordChange = coord;

    for (int index = 0; index < matrix.rowSize; ++index) {
        columnChange[index] = matrix(index, f);
    }

    return 0;
}

int CheckLineOnZero(Matrix& matrix, int row){
    int countZero(0);
    for (int j = 0; j < matrix.columnSize; ++j) {
        if (matrix(row, j) == SimpleFraction(0, 1)) ++countZero;
        else if (j == matrix.rowSize and matrix(row, j) != SimpleFraction(0, 1) and countZero == matrix.rowSize) return 1;
        else return 2;
    }
    return 0;
}

void CheckForSwapLines(Matrix& matrix, int startRow, int column){
    if (CheckLineOnZero(matrix, startRow) == 2) return ;
    SimpleFraction Zero = SimpleFraction(0, 1);
    int indexMaxVal(-1);
    for (int i = startRow; i < matrix.rowSize; ++i) {
        if (Zero != matrix(i, column)) {
            Zero = matrix(i, column);
            indexMaxVal = i;
            break;
        }
        else continue;
    }
    matrix.SwapLine(startRow, indexMaxVal);
}

int CheckLinesOnZero(Matrix& matrix){
    for (int i = 0; i < matrix.rowSize; ++i) {
        if (CheckLineOnZero(matrix, i) == 1) return 1;
    }
    return 0;
}


std::vector<double> GaussMod(Matrix& matrix){
    std::cout << matrix;
    if (Validate(matrix)) throw;
    std::map<int, std::pair<int ,int>> futureAnswers;

    for (int f = 0; f < matrix.columnSize-1; ++f) {
        std::pair<int, int> coord(0,0);
        std::map<int, SimpleFraction> currentColumn;
        SimpleFraction div = matrix(f,f);

        CheckForSwapLines(matrix, f, f);
//        std::cout << matrix;
        if(preparencetoWork(f, matrix, coord, currentColumn)) break;
        futureAnswers[f] = coord;

        for (int index = coord.second + 1; index < matrix.columnSize; ++index) {
            SimpleFraction currentMainRowElem = matrix(coord.first,index)/div;
            matrix(coord.first, index, currentMainRowElem);
        }
        std::cout << matrix;

        for (int i = 0; i < matrix.rowSize; ++i) {
            for (int j = f; j < matrix.columnSize; ++j) {
                if (coord.second == j){
                    if (i == j) matrix(i, j, SimpleFraction(1,1));
                    else matrix(i, j, SimpleFraction(0,1));
                    continue;
                }
                if (coord.first == i) {
                    continue;
                }
                else {
                    SimpleFraction c = matrix(coord.first, j) * currentColumn[i];
                    SimpleFraction currentElem = matrix(i, j) - (c);
                    matrix(i,j,currentElem);
                }

            }

        }
        std::cout << matrix;
    }

    if (CheckLinesOnZero(matrix)) std::cout << "No solutions";
    else
        for (int i = 0; i < futureAnswers.size(); ++i) {
            std::cout << "x_" << futureAnswers[i].second + 1 << " = ";
            for (int j = futureAnswers[i].second + 1; j < matrix.columnSize - 1; ++j) {
                if (matrix(i, j) != SimpleFraction(0, 1))
                 std::cout << matrix(i, j) * -1 << "x_" << j+1 << " + ";
            }
            if ( matrix(i, matrix.columnSize-1) != SimpleFraction(0, 1))
                std::cout << matrix(i, matrix.columnSize-1);
            std::cout << "\n";
        }
}