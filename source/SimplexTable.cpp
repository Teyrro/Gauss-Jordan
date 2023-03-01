//
// Created by vorop on 24.02.2023.
//

#include "../header/SimplexTable.h"
#include "../header/SimplexMethod.h"

SimplexTable::SimplexTable() : matrix(0,0){
    std::vector<int> matrixInfo = CalculateRowsAndColumns();
    matrix.rowCount = matrixInfo[ROW_SIZE];
    matrix.columnCount = matrixInfo[COLUMN_SIZE];
    rowZ.resize(matrixInfo[COLUMN_SIZE]);
    basicVariables.resize(matrixInfo[EXTRA_VAR_SIZE]);
    startBasic.resize((matrixInfo[COLUMN_SIZE] - matrixInfo[EXTRA_VAR_SIZE]) - 1);

    std::vector<SimpleFraction> a(matrix.rowCount * matrix.columnCount);
    FillMatrixData(matrixInfo, a);
    Matrix m(matrix.rowCount, matrix.columnCount, std::move(a));
    matrix = m;
    if (matrixInfo[EXTRA_VAR_SIZE] < matrixInfo[ROW_SIZE])
        GaussMod(matrix);
    basicVariables = FindBasicSolutions(matrix, true);

    UpdateTargetFunction();
}

void SimplexTable::UpdateTargetFunction(){
    std::vector<SimpleFraction> tmpSum(rowZ.size() - 1);
    for (int j(0); j < basicVariables.size(); j++) {
        SimpleFraction zero = SimpleFraction(0, 1);
        if (rowZ[basicVariables[j].second] != zero)
            for (int i(0); i < rowZ.size() - 1; i++) {
//                std::cout << tmpSum[i] << " ";
                if (matrix(j, i) != zero and i != basicVariables[j].second) {
                    tmpSum[i] = tmpSum[i] + matrix(j, i) * (rowZ[basicVariables[j].second] * -1);
                }
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
}

std::vector<int> SimplexTable::CalculateRowsAndColumns(){
    std::vector<std::string> inequalSymb {{"<="}, {">="}};
    std::vector<std::string> targetFunctionSymb{{"max"}, { "min"}};
    std::ifstream file("../Data.txt");
    std::string strBuffer;
    std::vector<int> matrixInfo(3);
    int countRow(0), countInequalSymbols(0);
    bool isTargetFunc(false);
    do {
        getline(file, strBuffer);
        for (auto& item: targetFunctionSymb) {
            if(strBuffer.contains(item))
                isTargetFunc = true;
        }
    } while (!strBuffer.empty());
    if (!isTargetFunc)
        std::invalid_argument("Fill target function like that \"1 2 3 4 max\" or \"1 2 3 4 min\"");
    while(!file.eof()){
        getline(file, strBuffer);
        if (strBuffer.empty())
            throw std::invalid_argument("Fill Data.txt only with one empty row between target function and restrictions");
        countRow++;
        for (auto& item: inequalSymb) {
            if(strBuffer.contains(item))
                countInequalSymbols++;
        }
    }
    matrixInfo[0] = countRow;
    matrixInfo[1] = std::count(strBuffer.cbegin(), strBuffer.cend(),' ') + countInequalSymbols;
    matrixInfo[2] = countInequalSymbols;
    return matrixInfo;
}

void SimplexTable::FillRowZ(std::string& strBuffer, std::ifstream& file, std::vector<SimpleFraction>& row){
    file >> strBuffer;
    {
        std::stringstream bufferToLongLong;
        bufferToLongLong << strBuffer;
        bufferToLongLong >> row[row.size() - 1].numerator;
    }
    file >> strBuffer;
    int i(0);
    while(true){
        std::stringstream bufferToLongLong;
        bufferToLongLong << strBuffer;
        bufferToLongLong >> row[i].numerator;
        i++;
        file >> strBuffer;
        if (strBuffer == "max" or strBuffer == "min")
            break;
    }
    for (int j = 0; j < row.size() - 1; ++j)
        row[j].numerator *= -1;
    minOrMax = 1;
    if (strBuffer == "min") {
        minOrMax = -1;
        for (auto &item: row)
            item.numerator *= -1;
    }

}

void SimplexTable::FillMatrixData(std::vector<int> matrixInfo, std::vector<SimpleFraction>& outDataVector){
    std::ifstream file("../Data.txt");
    int i(0);
    std::string strBuffer;
    int mainElement(0);
    FillRowZ(strBuffer, file, rowZ);

    std::map<std::string, int> coefficient {{"<=", 1}, {">=", -1}, {"=", 0}};
    while (!file.eof()){
        std::stringstream bufferToLongLong;
        file >> strBuffer;
        if (strBuffer == "<=" or strBuffer == ">=") {
            for (int j = 0; j < mainElement; ++j)
                outDataVector[i++].numerator = coefficient["="];
            outDataVector[i++].numerator = coefficient[strBuffer];
            mainElement++;
            for (int j = mainElement; j < matrixInfo[EXTRA_VAR_SIZE]; ++j)
                outDataVector[i++].numerator = coefficient["="];
            continue;
        }
        else if (strBuffer == "="){
            for (int j = 0; j < matrixInfo[EXTRA_VAR_SIZE]; ++j)
                outDataVector[i++].numerator = coefficient["="];
            continue;
        }
        else {
            bufferToLongLong << strBuffer;
            bufferToLongLong >> outDataVector[i].numerator;
        }
        i++;
    }
}

std::ostream& operator <<(std::ostream& out, SimplexTable const & data){
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
    out << "\n\n";
    return out;
}