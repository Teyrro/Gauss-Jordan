//
// Created by vorop on 13.04.2023.
//

#ifndef UNTITLED1_METHODARTIFICIALBASIS_H
#define UNTITLED1_METHODARTIFICIALBASIS_H

#include <utility>

#include "../SimplexMethod/SimplexTable.h"
#include "../SimplexMethod/SimplexMethod.h"
#include "ArtificialTable.h"
short FindMinElement(ArtificialTable const& table, std::pair<int, int>& coord);
void MethodArtificialBasis(ArtificialTable &table);

#endif //UNTITLED1_METHODARTIFICIALBASIS_H
