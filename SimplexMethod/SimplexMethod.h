//
// Created by vorop on 26.02.2023.
//

#ifndef UNTITLED1_SIMPLEXMETHOD_H
#define UNTITLED1_SIMPLEXMETHOD_H

#include "SimplexTable.h"
short FindMinElement(SimplexTable const& table, std::pair<int, int>& coord);
void CopyColumnAnswer(SimplexTable const& table,std::vector<SimpleFraction>& outData, int column);
short FindMinRestriction(SimplexTable& table, std::pair<int, int>& coord);
void PrintSystemAnswer(SimplexTable& table, std::vector<SimpleFraction>& oldBacisSolution,
                       std::vector<SimpleFraction>& newBaiscSolution, short isAlternativeOptimum);
void SimplexMethod(SimplexTable& table);

#endif //UNTITLED1_SIMPLEXMETHOD_H
