//
// Created by vorop on 24.02.2023.
//

#ifndef UNTITLED1_SIMPLEXTABLE_H
#define UNTITLED1_SIMPLEXTABLE_H


#include "../Gauss/Matrix/Matrix.h"
#include "../Gauss/Gauss.h"
#include "../AllBasicSolutions/FindAllBasicSolutions.h"
#include <string>
#include <sstream>
#include <map>

class SimplexTable {
protected:
    enum {
        ROW_SIZE,
        COLUMN_SIZE,
        EXTRA_VAR_SIZE
    };
    std::vector<int> CalculateRowsAndColumns(std::string fileName);
    void FillRowZ(std::string& strBuffer, std::ifstream& file, std::vector<SimpleFraction>& row);
    void FillMatrixData(std::vector<int> matrixInfo, std::vector<SimpleFraction>& outDataVector, std::string fileName);
    virtual void UpdateTargetFunction();
    friend void GaussMod(Matrix& matrix);
    friend std::vector<std::pair<int, int>> FindBasicSolutions(Matrix& outDataMatrix, bool is);
    void OffsetToColumnAnswer(int& i, std::vector<int> matrixInfo, int countVar);
        public:
    enum{
        ANSWER_INDEX
    };
    Matrix matrix;
    short minOrMax;
    std::vector<SimpleFraction> rowZ;
    std::vector<std::pair<int, int>> basicVariables;
    std::vector<std::pair<SimpleFraction, SimpleFraction>> startBasic;

    SimplexTable(){}

    SimplexTable(std::string fileName);
    virtual SimpleFraction operator()(int row, int column) {
        if (column == 0) column = matrix.columnCount - 1;
        else
            column -= 1;

        if (row == matrix.rowCount and (column >= 0 and column < matrix.columnCount))
            return rowZ[column];
        return matrix(row, column);
    }

    virtual SimpleFraction operator()(int row, int column) const{
        if (column == 0) column = matrix.columnCount - 1;
        else
            column -= 1;

        if (row == matrix.rowCount and (column >= 0 and column < matrix.columnCount))
            return rowZ[column];
        return matrix(row, column);
    }

    virtual void operator()(int row, int column, SimpleFraction inputAnswer){
        if (column == 0) column = matrix.columnCount - 1;
        else
            column -= 1;
        if (row == matrix.rowCount and (column >= 0 and column < matrix.columnCount)) {
            rowZ[column] = inputAnswer;
            return;
        }
        matrix(row, column, inputAnswer);
    }
};
std::ostream& operator <<(std::ostream& out, SimplexTable & data);


#endif //UNTITLED1_SIMPLEXTABLE_H
