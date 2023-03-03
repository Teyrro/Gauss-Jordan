//
// Created by vorop on 26.02.2023.
//

#ifndef UNTITLED1_STUFFFORGAUSS_H
#define UNTITLED1_STUFFFORGAUSS_H

#include <map>
#include "Matrix/Matrix.h"
#include "../SimplexMethod/SimplexTable.h"

void CopyCurrentColumn(Matrix const& matrix, int column, std::map<int, SimpleFraction>& columnChange);
void CopyCurrentColumn(SimplexTable const& table, int column, std::map<int, SimpleFraction>& columnChange);
void Transformation(Matrix& matrix, int row, std::pair<int, int>const& coord, std::map<int, SimpleFraction> currentColumn,
                    short isNoSolution, std::vector<std::pair<int, int>> sample);
void Transformation(SimplexTable& table, int row, std::pair<int, int>const& coord, std::map<int, SimpleFraction> currentColumn,
                    short isNoSolution, std::vector<std::pair<int, int>> sample);
#endif //UNTITLED1_STUFFFORGAUSS_H
