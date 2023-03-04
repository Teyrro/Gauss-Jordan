//
// Created by vorop on 02.02.2023.
//

#include <map>
#include "Gauss.h"
#include "StuffForGauss.h"


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


std::pair<int, int> CheckForSwapLinesByMainColumn(Matrix& matrix, int startRow, int startColumn){
    int indexMaxVal(startRow);
    SimpleFraction zero = SimpleFraction(0, 1);
    int mainRow(-1), mainColumn(-1);
    for (int column = startColumn; column < matrix.columnCount - 1; ++column) {
        for (int row = startRow; row < matrix.rowCount; ++row) {
            if (zero != matrix(row, column)) {
                mainRow = row;
                mainColumn = column;
                break;
            }
        }
        if (mainRow != -1) break;
    }
    if (mainRow == -1 and mainColumn == -1) return std::make_pair(-1, -1);
    indexMaxVal = mainRow;
    SimpleFraction maxVal = matrix(mainRow, mainColumn);

    for (int i = startRow; i < matrix.rowCount; ++i) {

        if (maxVal < matrix(i, mainColumn)) {
            maxVal = matrix(i, mainColumn);
            indexMaxVal = i;
        }
    }

    matrix.SwapLine(startRow, indexMaxVal);
    return std::make_pair(startRow, mainColumn);
}

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
    std::cout << "\n";

}

void Transformation(Matrix& matrix, int row, std::pair<int, int>const& coord, std::map<int, SimpleFraction> currentColumn,
                    short isNoSolution){

    for (int currentRow = 0; currentRow < matrix.rowCount; ++currentRow) {
        for (int column = row; column < matrix.columnCount; ++column) {
            if (coord.second == column){
                if (currentRow == coord.first) matrix(currentRow, column, SimpleFraction(1, 1));
                else matrix(currentRow, column, SimpleFraction(0, 1));
                continue;
            }
            if (coord.first == currentRow) {
                continue;
            }
            else {
                SimpleFraction c = matrix(coord.first, column) * currentColumn[currentRow] / currentColumn[row];
                SimpleFraction currentElem = matrix(currentRow, column) - (c);
                matrix(currentRow, column, currentElem);
            }

        }

    }
    if (isNoSolution != 2) {
        for (int index = coord.second + 1; index < matrix.columnCount; ++index) {
            SimpleFraction currentMainRowElem = matrix(coord.first, index) / currentColumn[row];
            matrix(coord.first, index, currentMainRowElem);
        }
    }
}


void GaussMod(Matrix& matrix){
    if (matrix.columnCount - 1 < matrix.rowCount) throw std::overflow_error("amount variables < column answer");
    std::cout << matrix;
    std::map<int, std::pair<int ,int>> futureAnswers;
    short isNoSolution = false;

    for (int f = 0; f < matrix.rowCount; ++f) {
        std::pair<int, int> mainElementCoord(0, 0);

        isNoSolution = CheckLineOnZero(matrix, f);
        if(isNoSolution == 1) break;

        mainElementCoord = CheckForSwapLinesByMainColumn(matrix, f, f);
        if (mainElementCoord == std::make_pair(-1, -1)) break;
//        findCoordMainElement(matrix, f,mainElementCoord);

        futureAnswers[f] = mainElementCoord;
        std::map<int, SimpleFraction> currentColumn;
        CopyCurrentColumn(matrix, mainElementCoord.second, currentColumn);
        Transformation(matrix, f, mainElementCoord, currentColumn, isNoSolution) ;
        std::cout << matrix;
    }
    CheckMatrixOnZeroLine(matrix);
    std::cout << matrix;
    PrintAnswer(matrix, futureAnswers, isNoSolution);
}


void PrintAnswer(std::map<int, SimpleFraction> & futureAnswers,
                 short isNoSolution, std::vector<std::pair<int, int>>& sample){
    if (isNoSolution == 1)
         std::cout << "No Solutions";
    else {
        std::cout << "(";
        for (int i = 0; i < futureAnswers.size(); ++i) {
            std::cout << futureAnswers[i] << "; ";
        }
        std::cout << ")\n";
    }

    std::cout << " \n";

}



std::pair<int, int> CheckForSwapLinesByMainColumn(Matrix& matrix, std::vector<std::pair<int, int>> sample
                                                  , int startRow, int startColumn){
    int indexMaxVal(startRow);
    SimpleFraction zero = SimpleFraction(0, 1);
    int mainRow(-1), mainColumn(-1);
    for (int column = startColumn; column < sample.size(); ++column) {
        for (int row = startRow; row < matrix.rowCount; ++row) {
            if (zero != matrix(row, sample[column].second)) {
                mainRow = row;
                mainColumn = column;
                break;
            }
        }
        if (mainRow != -1) break;
    }
    if (mainRow == -1 and mainColumn == -1) return std::make_pair(-1, -1);
    indexMaxVal = mainRow;
    SimpleFraction maxVal = matrix(mainRow, mainColumn);

    for (int i = startRow; i < matrix.rowCount; ++i) {

        if (maxVal < matrix(i, sample[mainColumn].second)) {
            maxVal = matrix(i, sample[mainColumn].second);
            indexMaxVal = i;
        }
    }

    matrix.SwapLine(startRow, indexMaxVal);
    return std::make_pair(startRow, sample[mainColumn].second);
}

short CheckLineOnZero(Matrix const & matrix, int row, std::vector<std::pair<int, int>> sample){
    int countZero(0);
    SimpleFraction zero = SimpleFraction(0, 1);
    for (int j = sample[0].second; j < sample.size(); ++j) {
        if (matrix(row, sample[j].second) == zero) ++countZero;
    }
    if (matrix(row, matrix.columnCount - 1) != zero and countZero == sample.size()) return 1;
    else if (countZero == sample.size()) return 2;

    return 0;
}

Matrix GaussMod(Matrix matrix, std::vector<std::pair<int, int>> sample){
    if (matrix.columnCount - 1 < matrix.rowCount) throw std::overflow_error("amount variables < column answer");
    std::cout << matrix;
    std::map<int, SimpleFraction> futureAnswers;
    short isNoSolution = false;
    for (int f = 0; f < matrix.rowCount; ++f) {
//        CheckOnZeroForSwapLines(matrix, f, f);
        std::pair<int, int> coord(0,0);
        isNoSolution = CheckLineOnZero(matrix, f, sample);
        if(isNoSolution == 1) break;
        // f поменять на sample[f].first
        coord = CheckForSwapLinesByMainColumn(matrix, sample, f, f);
        if (coord == std::make_pair(-1, -1)) break;
        sample[f].first = coord.first;
//        std::cout << matrix;

        futureAnswers[sample[f].second] = SimpleFraction(0, 1);
        std::map<int, SimpleFraction> currentColumn;
        CopyCurrentColumn(matrix, coord.second, currentColumn);

        Transformation(matrix, f, coord, currentColumn, isNoSolution, sample) ;
        std::cout << matrix;
    }

    {
        int i(0);
        for (auto &item: futureAnswers) {
            item.second = matrix(i++, matrix.columnCount - 1);
        }
    }

    for (int i = 0; i < matrix.columnCount - 1; ++i) {
        if(!futureAnswers.contains(i))
            futureAnswers[i] = SimpleFraction(0, 1);
    }

    CheckMatrixOnZeroLine(matrix);
//    std::cout << "\n" << matrix;
    PrintAnswer(futureAnswers, isNoSolution, sample);
    return matrix;
}
