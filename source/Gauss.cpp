//
// Created by vorop on 02.02.2023.
//

#include <map>
#include "../header/Gauss.h"

void CopyCurrentColumn(Matrix const& matrix, int column,  std::map<int, SimpleFraction>& columnChange){
    for (int index = 0; index < matrix.rowCount; ++index) {
        columnChange[index] = matrix(index, column);
    }
}

short CheckLineOnZero(Matrix const & matrix, int row){
    int countZero(0);
    SimpleFraction zero = SimpleFraction(0, 1);
    for (int j = 0; j < matrix.columnCount; ++j) {
        if (matrix(row, j) == zero) ++countZero;
    }
    if (matrix(row, matrix.columnCount - 1) != zero and countZero == matrix.columnCount - 1) return 1;
    else if (countZero == matrix.columnCount) return 2;

    return 0;
}

//short CheckOnZeroForSwapLines(Matrix & matrix, int startRow, int column){
//    if (CheckLineOnZero(matrix, startRow) == 1) return 1;
//    SimpleFraction Zero = SimpleFraction(0, 1);
//    int indexVal(-1);
//    for (int j = column; j < matrix.columnCount - 1; ++j)
//        for (int i = startRow; i < matrix.rowCount; ++i) {
//            if (Zero != matrix(i, j)) {
//                Zero = matrix(i, j);
//                indexVal = i;
//                break;
//            }
//            else continue;
//        }
//
//    matrix.SwapLine(startRow, indexVal);
//    return 0;
//}

std::pair<int, int> CheckForSwapLinesByMainColumn(Matrix& matrix, int startRow, int column){
    int indexMaxVal(startRow);
    SimpleFraction zero = SimpleFraction(0, 1);
    int mainRow(-1), mainColumn(-1);
    for (int j = column; j < matrix.columnCount - 1; ++j) {
        for (int i = startRow; i < matrix.rowCount; ++i) {
            if (zero != matrix(i, j)) {
                mainRow = i;
                mainColumn = j;
                break;
            }
        }
        if (mainRow != -1) break;
    }
    if (mainRow == -1 and mainColumn == -1) return std::make_pair(-1, -1);
    indexMaxVal = mainRow;
    SimpleFraction maxVal = matrix(mainRow, mainColumn);

    for (int i = mainRow + 1; i < matrix.rowCount; ++i) {

        if (maxVal < matrix(i, mainColumn)) {
            maxVal = matrix(i, mainColumn);
            indexMaxVal = i;
        }
    }

    matrix.SwapLine(startRow, indexMaxVal);
    return std::make_pair(startRow, mainColumn);
}

//int CheckLinesOnZero(Matrix& matrix){
//    for (int i = 0; i < matrix.rowCount; ++i) {
//        if (CheckLineOnZero(matrix, i) == 1) return 1;
//    }
//    return 0;
//}

void PrintAnswer(Matrix const& matrix,  std::map<int, std::pair<int ,int>> & futureAnswers, short isNoSolution){
    if (isNoSolution == 1)
        throw std::invalid_argument("No Solutions");
    else
        for (int i = 0; i < futureAnswers.size(); ++i) {
            std::cout << "x_" << futureAnswers[i].second + 1 << " = ";
            for (int j = futureAnswers[i].second + 1; j < matrix.columnCount - 1; ++j) {
                if (matrix(i, j) != SimpleFraction(0, 1))
                    std::cout << matrix(i, j) * -1 << "x_" << j+1 << " + ";
            }

            std::cout << matrix(i, matrix.columnCount - 1);
            std::cout << "\n";
        }
}

void Transformation(Matrix& matrix, int f, std::pair<int, int>const& coord, std::map<int, SimpleFraction> currentColumn,
                    short isNoSolution){
    for (int i = 0; i < matrix.rowCount; ++i) {
        for (int j = f; j < matrix.columnCount; ++j) {
            if (coord.second == j){
                if (i == coord.first) matrix(i, j, SimpleFraction(1,1));
                else matrix(i, j, SimpleFraction(0,1));
                continue;
            }
            if (coord.first == i) {
                continue;
            }
            else {
                SimpleFraction c = matrix(coord.first, j) * currentColumn[i] / currentColumn[f];
                SimpleFraction currentElem = matrix(i, j) - (c);
                matrix(i,j,currentElem);
            }

        }

    }
    if (isNoSolution != 2) {
        for (int index = coord.second + 1; index < matrix.columnCount; ++index) {
            SimpleFraction currentMainRowElem = matrix(coord.first, index) / currentColumn[f];
            matrix(coord.first, index, currentMainRowElem);
        }
        std::cout << matrix;
    }
}

void GaussMod(Matrix& matrix){
    if (matrix.columnCount - 1 < matrix.rowCount) throw std::overflow_error("amount variables < column answer");
    std::cout << matrix;
    std::map<int, std::pair<int ,int>> futureAnswers;
    short isNoSolution = false;
    for (int f = 0; f < matrix.rowCount; ++f) {
//        CheckOnZeroForSwapLines(matrix, f, f);
        std::pair<int, int> coord(0,0);
        isNoSolution = CheckLineOnZero(matrix, f);
        if(isNoSolution == 1) break;

        coord = CheckForSwapLinesByMainColumn(matrix, f, f);
        if (coord == std::make_pair(-1, -1)) break;
//        findCoordMainElement(matrix, f,coord);

        futureAnswers[f] = coord;
        std::map<int, SimpleFraction> currentColumn;
        CopyCurrentColumn(matrix, coord.second, currentColumn);
        std::cout << matrix;
        Transformation(matrix, f, coord, currentColumn, isNoSolution) ;
    }
    CheckMatrixOnZeroLine(matrix);
    std::cout << matrix;
    PrintAnswer(matrix, futureAnswers, isNoSolution);
}