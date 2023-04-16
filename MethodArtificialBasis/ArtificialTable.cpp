//
// Created by vorop on 13.04.2023.
//

#include <algorithm>
#include "ArtificialTable.h"
#include "../SimplexMethod/SimplexMethod.h"



void ArtificialTable::UpdateTargetFunction(){
    auto isContains = [](std::list<std::pair<int, int>> coordArtifBasis, int column) {
        for (auto &item: coordArtifBasis) {
            if (item.second == column)
                return false;
        }
        return true;
    };

    std::vector<SimpleFraction> tmpSum(rowZ.size() - 1);
    for (int j(0); j < basicVariables.size(); j++) {
        SimpleFraction zero = SimpleFraction(0, 1);
        if (rowZ[basicVariables[j].second] != zero)
            for (int i(0); i < rowZ.size() - 1; i++) {
//                std::cout << tmpSum[i] << " ";
                if(isContains(coordNewVar, i))
                    if (matrix(j, i) != zero and i != basicVariables[j].second)
                        tmpSum[i] = tmpSum[i] + matrix(j, i) * (rowZ[basicVariables[j].second] * -1);
            }
        rowZ[rowZ.size()-1] = rowZ[rowZ.size()-1] + (rowZ[basicVariables[j].second] * -1) * matrix(j, matrix.columnCount -1);
        rowZ[basicVariables[j].second] = zero;
    }
    for (int i = 0; i < rowZ.size() - 1; ++i) {
        rowZ[i] = tmpSum[i] + rowZ[i];
    }

    for (auto& item : basicVariables) {
        item.second += 1;
    }
    tmpSum = std::vector<SimpleFraction>(rowM.size());
    for (auto& item : coordNewVar) {
        SimpleFraction zero = SimpleFraction(0, 1);
        for (int i = 0; i < rowM.size(); ++i) {
            if (matrix(item.first, i) != zero and i != item.second){
                tmpSum[i] = tmpSum[i] + matrix(item.first, i) * -1;
            }
        }

    }

    for (int i = 0; i < rowM.size(); ++i) {
        rowM[i] = tmpSum[i] + rowM[i];
    }
}

std::pair<int, std::vector<bool>> ArtificialTable::FindingBasisColumns(){
    std::pair<int, std::vector<bool>> basis = std::make_pair(0,
                                                             std::vector<bool>(matrix.rowCount));
    SimpleFraction zero = SimpleFraction(0, 1), one = SimpleFraction(1, 1);
    for (int i = 0; i < matrix.columnCount; ++i) {
        int countNotZero(0), tmp(-1);
        for (int j = 0; j < matrix.rowCount; ++j) {
            if (matrix(j, i) != zero) {
                if (matrix(j, i) == one) {
                    tmp = j;
                }
                countNotZero++;
            }

        }
        if (countNotZero == 1 and tmp != -1) {
            basis.second[tmp] = true;
            basis.first++;
        }
    }
    return basis;
}

void ArtificialTable::DeleteColumn(int column){
    Matrix a = Matrix(matrix.rowCount, matrix.columnCount-1);
    std::vector<SimpleFraction> newRowZ(rowZ.size()-1), newRowM(rowM.size()-1);
    for (int i = 0, index(0); i < rowZ.size(); ++i) {
        if(i != column){
            newRowZ[index] = rowZ[i];
            newRowM[index++] = rowM[i];
        }
    }
    rowZ = newRowZ;
    rowM = newRowM;

    for (int i = 0; i < matrix.rowCount; ++i) {
        for (int j = 0, index = 0; j < matrix.columnCount; ++j) {
            if(j != column) {
                a(i, index, matrix(i, j));
                index++;
            }
        }
    }

    matrix = std::move(a);
}

void ArtificialTable::AddColumns(int count){

    Matrix a = Matrix(matrix.rowCount, matrix.columnCount+count);
    for (int i = 0; i < matrix.rowCount; ++i) {
        for (int j = 0; j < matrix.columnCount - 1; ++j) {

            a(i, j, matrix(i, j));
        }
        a(i, a.columnCount - 1, matrix(i, matrix.columnCount - 1));
    }
    rowZ.resize(rowZ.size() + count);
    rowM.resize(rowM.size() + count);

    matrix = std::move(a);
}

std::ostream& operator <<(std::ostream& out, ArtificialTable & data){
    out << "B.S.\t" << "1\t";
    for (int i = 0; i < data.matrix.columnCount - 1; ++i) {
        out << "x_" << i+1 << "\t";
    }
    out << "S.R.";
    out << "\n";
//    out << data.matrix;
    std::pair<int, int> coord;
    short isOptimalPlan = FindMinElement(data, coord);
    for (int i = 0; i < data.matrix.rowCount; ++i) {
        out << "x_" << data.basicVariables[i].second << "\t";
        for (int j = 0; j < data.matrix.columnCount; ++j) {
            out << data(i, j) << "\t";
        }
        if (data(i, coord.second) > SimpleFraction(0, 1) and isOptimalPlan != 1)
            out << data(i, 0) / data(i, coord.second);
        out << "\n";

    }

    out << "Z:\t";
    for (int i = 0; i < data.rowZ.size(); ++i) {
        out << data(data.matrix.rowCount, i) << "\t";
    }
    out << "\n";
    out << "M:\t";
    for (int i = 0; i < data.rowM.size(); ++i) {
        out << data(data.matrix.rowCount+1, i) << "\t";
    }
    out << "\n\n";
    return out;
}