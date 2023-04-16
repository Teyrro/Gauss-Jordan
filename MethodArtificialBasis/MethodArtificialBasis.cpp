//
// Created by vorop on 13.04.2023.
//

#include "MethodArtificialBasis.h"
#include "../Gauss/StuffForGauss.h"


short FindMinElement(ArtificialTable const& table, std::pair<int, int>& coord){
    std::vector<bool> basicVar(table.rowM.size() - 1);
    for (auto& item : table.basicVariables) {
        basicVar[item.second] = true;
    }

    SimpleFraction tmpItem = SimpleFraction(0, 1);
    int column(-1);
    std::pair<SimpleFraction, int> currentColumn;
    std::list<std::pair<SimpleFraction, int>> tmpData;
    for (int i(1); i < table.rowM.size(); i++) {
        SimpleFraction newItem = table(table.matrix.rowCount + 1, i);
        if (SimpleFraction(0, 1) >= newItem and !basicVar[i])
            tmpData.emplace_back(newItem, i);
    }
    if(!tmpData.empty())
        currentColumn = *std::min_element(tmpData.begin(), tmpData.end(), [](auto a,
                                                                             auto b ){ return b.first > a.first; });
    else
        return 1;
    column = currentColumn.second;
    coord = std::make_pair(0, column);
    if (currentColumn.first == SimpleFraction(0, 1)) return 3;
    return 0;
}

void FindAndDeleteUnnecesssaryColumn(ArtificialTable& table){
    auto isContains = [](std::list<std::pair<int, int>> coordArtifBasis, int column) {
        for (auto &item: coordArtifBasis) {
            if (item.second == column)
                return false;
        }
        return true;
    };

    SimpleFraction zero = SimpleFraction(0, 1);
    for (int i(0); i < table.rowM.size(); i++) {
        if (zero != table.rowM[i] and !isContains(table.coordNewVar, i)){
            table.DeleteColumn(i);
        }
    }
}

void MethodArtificialBasis(ArtificialTable &table){

    std::vector<SimpleFraction> oldBacisSolution(table.matrix.columnCount), newBaiscSolution(table.matrix.columnCount);
    std::pair<int, int> coord(0, 0);
    std::cout << table;
    short isAlternativeOptimum = false;
    while (isAlternativeOptimum != 3) {
        std::map<int, SimpleFraction> currentColumn;
        isAlternativeOptimum = FindMinElement(table, coord);
        if (isAlternativeOptimum == 1)
            break;
        else if (isAlternativeOptimum == 3)
            CopyColumnAnswer(table, oldBacisSolution, table.ANSWER_INDEX);
        short isUnlimitedFunction = FindMinRestriction(table, coord);
        if (isUnlimitedFunction) {
            isAlternativeOptimum = isUnlimitedFunction;
            break;
        }

        table.basicVariables[coord.first] = coord;
        CopyCurrentColumn(table, coord.second, currentColumn);
        Transformation(table, coord.first, coord, currentColumn, false, table.matrix.rowCount + 1);
        FindAndDeleteUnnecesssaryColumn(table);

        std::cout << table;
    }
    SimplexMethod(table);
//    PrintSystemAnswer(table, oldBacisSolution, newBaiscSolution, isAlternativeOptimum);
}