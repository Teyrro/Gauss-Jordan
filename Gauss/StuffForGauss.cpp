//
// Created by vorop on 26.02.2023.
//

#include "StuffForGauss.h"
#include "../SimplexMethod/SimplexTable.h"


void CopyCurrentColumn(Matrix const& matrix, int column,  std::map<int, SimpleFraction>& columnChange){
    for (int index = 0; index < matrix.rowCount; ++index) {
        columnChange[index] = matrix(index, column);
    }
}

void CopyCurrentColumn(SimplexTable const& table, int column, std::map<int, SimpleFraction>& columnChange){
    for (int index = 0; index < table.matrix.rowCount + 1; ++index) {
        columnChange[index] = table(index, column);
    }
}

void CopyCurrentColumn(ArtificialTable const& table, int column, std::map<int, SimpleFraction>& columnChange){
    for (int index = 0; index <= table.matrix.rowCount + 1; ++index) {
        columnChange[index] = table(index, column);
    }
}


void Transformation(ArtificialTable& table, int row, std::pair<int, int>const& coord, std::map<int, SimpleFraction> currentColumn,
                    short isNoSolution, int rowSize){
    for (int i = 0; i <= rowSize; ++i) {
        for (int item(0); item < table.matrix.columnCount; item++) {
            if (coord.second == item){
                if (i == coord.first) table(i, item, SimpleFraction(1, 1));
                else table(i, item, SimpleFraction(0, 1));
                continue;
            }
            if (coord.first == i) {
                continue;
            }
            else {
                // row поменять на sample[row].first
                SimpleFraction c = table(coord.first, item) * currentColumn[i] / currentColumn[row];
                SimpleFraction currentElem = table(i, item) - (c);
                table(i, item, currentElem);
            }

        }

    }
    if (isNoSolution != 2) {
        for (int index = 0; index < coord.second; ++index) {

            SimpleFraction currentMainRowElem = table(coord.first, index) / currentColumn[row];
            table(coord.first, index, currentMainRowElem);
        }
        for (int index = coord.second + 1; index < table.matrix.columnCount; ++index) {
            SimpleFraction currentMainRowElem = table(coord.first, index) / currentColumn[row];
            table(coord.first, index, currentMainRowElem);
        }
//        std::cout << table;
    }
}

void Transformation(SimplexTable& table, int row, std::pair<int, int>const& coord, std::map<int, SimpleFraction> currentColumn,
                    short isNoSolution, std::vector<std::pair<int, int>> sample){
    for (int i = 0; i < table.matrix.rowCount + 1; ++i) {
        for (int item(0); item < table.matrix.columnCount; item++) {
            if (coord.second == item){
                if (i == coord.first) table(i, item, SimpleFraction(1, 1));
                else table(i, item, SimpleFraction(0, 1));
                continue;
            }
            if (coord.first == i) {
                continue;
            }
            else {
                // row поменять на sample[row].first
                SimpleFraction c = table(coord.first, item) * currentColumn[i] / currentColumn[row];
                SimpleFraction currentElem = table(i, item) - (c);
                table(i, item, currentElem);
            }

        }

    }
    if (isNoSolution != 2) {
        for (int index = 0; index < coord.second; ++index) {

            SimpleFraction currentMainRowElem = table(coord.first, index) / currentColumn[row];
            table(coord.first, index, currentMainRowElem);
        }
        for (int index = coord.second + 1; index < table.matrix.columnCount; ++index) {
            SimpleFraction currentMainRowElem = table(coord.first, index) / currentColumn[row];
            table(coord.first, index, currentMainRowElem);
        }
//        std::cout << table;
    }
}

void Transformation(Matrix& matrix, int row, std::pair<int, int>const& coord, std::map<int, SimpleFraction> currentColumn,
                    short isNoSolution, std::vector<std::pair<int, int>> sample){
    for (int i = 0; i < matrix.rowCount; ++i) {
        for (int item(0); item < matrix.columnCount; item++) {
            if (coord.second == item){
                if (i == coord.first) matrix(i, item, SimpleFraction(1,1));
                else matrix(i, item, SimpleFraction(0,1));
                continue;
            }
            if (coord.first == i) {
                continue;
            }
            else {
                // row поменять на sample[row].first
                SimpleFraction c = matrix(coord.first, item) * currentColumn[i] / currentColumn[row];
                SimpleFraction currentElem = matrix(i, item) - (c);
                matrix(i,item,currentElem);
            }

        }

    }
    if (isNoSolution != 2) {
        for (int index = 0; index < coord.second; ++index) {

            SimpleFraction currentMainRowElem = matrix(coord.first, index) / currentColumn[row];
            matrix(coord.first, index, currentMainRowElem);
        }
        for (int index = coord.second + 1; index < matrix.columnCount; ++index) {
            SimpleFraction currentMainRowElem = matrix(coord.first, index) / currentColumn[row];
            matrix(coord.first, index, currentMainRowElem);
        }
//        std::cout << matrix;
    }
}