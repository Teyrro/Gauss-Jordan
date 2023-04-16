
#include <list>
#include "SimplexMethod.h"
#include "../Gauss/StuffForGauss.h"

short FindMinElement(SimplexTable const& table, std::pair<int, int>& coord){
    std::vector<bool> basicVar(table.rowZ.size() - 1);
    for (auto& item : table.basicVariables) {
        basicVar[item.second] = true;
    }

    SimpleFraction tmpItem = SimpleFraction(0, 1);
    int column(-1);
    std::pair<SimpleFraction, int> currentColumn;
    std::list<std::pair<SimpleFraction, int>> tmpData;
    for (int i(1); i < table.rowZ.size(); i++) {
        SimpleFraction newItem = table(table.matrix.rowCount, i);
        if (SimpleFraction(0, 1) >= newItem and !basicVar[i])
            tmpData.push_back({newItem, i});
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

short FindMinRestriction(SimplexTable& table, std::pair<int, int>& coord){
    std::list<std::pair<SimpleFraction, int>> tmpData;
    int row(-1);
    for (int i = 0; i < table.matrix.rowCount; ++i) {
        SimpleFraction newItem = table(i, coord.second);
        if (newItem > SimpleFraction(0, 1)) {
            tmpData.emplace_back(table(i, table.ANSWER_INDEX) / newItem, i);
        }
    }
    if(!tmpData.empty())
        row = std::min_element(tmpData.begin(), tmpData.end(), [](auto a,
                auto b ){ return a.first < b.first; })->second;
    else
        return 2;
    coord.first = row;
    return 0;
}

void CopyColumnAnswer(SimplexTable const& table,std::vector<SimpleFraction>& outData, int column){
    for(int i(0); i < table.matrix.rowCount; i++){
        outData[table.basicVariables[i].second - 1] = table(i, column);
    }
}

void PrintSystemAnswer(SimplexTable& table, std::vector<SimpleFraction>& oldBacisSolution,
                       std::vector<SimpleFraction>& newBaiscSolution, short isAlternativeOptimum){
    std::cout << "Answer: \n";
    SimpleFraction answer = table(table.matrix.rowCount,table.ANSWER_INDEX) * table.minOrMax;
    CopyColumnAnswer(table, newBaiscSolution, table.ANSWER_INDEX);
    for (int i = 0; i < table.startBasic.size(); ++i) {
        table.startBasic[i].first = newBaiscSolution[i] - oldBacisSolution[i];
        table.startBasic[i].second = oldBacisSolution[i];
    }
    switch(isAlternativeOptimum) {
        case 0: {}
        case 1:{
            std::cout << "Z = Z( ";
            for (auto const &item: table.startBasic)
                std::cout << item.first << "; ";
            std::cout << ") = " << answer;
            break;
        }
        case 2:{
            throw  std::invalid_argument("The function is not limited from above");
        }
        case 3: {
            std::cout << "Z = Z( ";
            for (auto const &item: table.startBasic)
                std::cout << item.first << "y + " << item.second << "; ";
            std::cout << ") = " << answer;
            std::cout << "\nwhere 0 <= y <= 1";
            break;
        }
    }
}

void SimplexMethod(SimplexTable& table){
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
        Transformation(table, coord.first, coord, currentColumn, false, table.basicVariables);

        std::cout << table;
    }
    PrintSystemAnswer(table, oldBacisSolution, newBaiscSolution, isAlternativeOptimum);
}
