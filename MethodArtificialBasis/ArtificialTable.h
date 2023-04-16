//
// Created by vorop on 13.04.2023.
//

#ifndef UNTITLED1_ARTIFICIALTABLE_H
#define UNTITLED1_ARTIFICIALTABLE_H


#include <list>
#include "../SimplexMethod/SimplexTable.h"

class ArtificialTable : public SimplexTable {
    void UpdateTargetFunction() override;
public:
    std::vector<SimpleFraction> rowM;
    std::list<std::pair<int, int>> coordNewVar;
    void DeleteColumn(int column);
    void AddColumns(int count);
    std::pair<int, std::vector<bool>> FindingBasisColumns();

    ArtificialTable() : SimplexTable() {}

    std::vector<std::pair<int, int>> BasicVariables(){
        std::vector<std::pair<int, int>> bv(matrix.rowCount);
        int index(0);
        for (int i = 0; i < matrix.columnCount; ++i) {
            int countNotZero(0), tmp(-1);
            for (int j = 0; j < matrix.rowCount; ++j) {
                if (matrix(j, i) != SimpleFraction(0, 1)) {
                    if (matrix(j, i) == SimpleFraction(1, 1)) {
                        tmp = j;
                    }
                    countNotZero++;
                }

            }
            if (countNotZero == 1 and tmp != -1){
               bv[index++] = std::make_pair(tmp, i);
            }
        }


        return bv;
    }


    ArtificialTable(const std::string& fileName) : SimplexTable(){
        std::vector<int> matrixInfo = CalculateRowsAndColumns(fileName);
        matrix.rowCount = matrixInfo[ROW_SIZE];
        matrix.columnCount = matrixInfo[COLUMN_SIZE];
        rowZ.resize(matrixInfo[COLUMN_SIZE]);
        rowM.resize(matrixInfo[COLUMN_SIZE]);
        basicVariables.resize(matrixInfo[ROW_SIZE]);
        startBasic.resize((matrixInfo[COLUMN_SIZE] - matrixInfo[EXTRA_VAR_SIZE]) - 1);

        std::vector<SimpleFraction> a(matrix.rowCount * matrix.columnCount);
        FillMatrixData(matrixInfo, a, fileName);
        Matrix m(matrix.rowCount, matrix.columnCount, std::move(a));
        matrix = m;

        std::cout << (*this);

        std::pair<int, std::vector<bool>> basisInfo = FindingBasisColumns();
        int rowBefore = matrix.rowCount, countNewVar = rowBefore - basisInfo.first;
        AddColumns(countNewVar);
        if (basisInfo.first <= rowBefore){
            for (int i(matrix.columnCount - 1 - countNewVar), index(0); i < matrix.columnCount; i++){
                for (int j = 0; j < matrix.rowCount; ++j) {
                    if (!basisInfo.second[j]){
                        basisInfo.second[j] = true;
                        coordNewVar.push_back(std::make_pair(j, i));
                        matrix(j, i, SimpleFraction(1, 1));
                        break;
                    }
                }
            }
        }

        basicVariables = BasicVariables();

        UpdateTargetFunction();
    }

    SimpleFraction operator()(int row, int column) override {
        if (column == 0) column = matrix.columnCount - 1;
        else
            column -= 1;

        if (row == matrix.rowCount and (column >= 0 and column < matrix.columnCount))
            return rowZ[column];
        if(row == matrix.rowCount+1 and (column >= 0 and column < matrix.columnCount))
            return rowM[column];

        return matrix(row, column);
    }

    SimpleFraction operator()(int row, int column)  const override{
        if (column == 0) column = matrix.columnCount - 1;
        else
            column -= 1;

        if (row == matrix.rowCount and (column >= 0 and column < matrix.columnCount))
            return rowZ[column];
        if(row == matrix.rowCount+1 and (column >= 0 and column < matrix.columnCount))
            return rowM[column];

        return matrix(row, column);
    }

    void operator()(int row, int column, SimpleFraction inputAnswer) override{
        if (column == 0) column = matrix.columnCount - 1;
        else
            column -= 1;
        if (row == matrix.rowCount and (column >= 0 and column < matrix.columnCount)) {
            rowZ[column] = inputAnswer;
            return;
        }

        if(row == matrix.rowCount+1 and (column >= 0 and column < matrix.columnCount)) {
            rowM[column] = inputAnswer;
            return;
        }
        matrix(row, column, inputAnswer);
    }

};

std::ostream& operator <<(std::ostream& out, ArtificialTable & data);



#endif //UNTITLED1_ARTIFICIALTABLE_H
