//
// Created by vorop on 05.02.2023.
//

#include <list>
#include <map>
#include "../header/Matrix.h"
#include "../header/FindAllBasicSolutions.h"
#include "../header/Gauss.h"

long long factorial(int x){
    long long answer(1);
    for (int i = 1; i <= x; ++i) {
        answer *= i;
    }
    return answer;
}

int FindRowIndex(Matrix& matrix, int column, int minIndex, std::vector<std::pair<bool, bool>>& takenLine){

    for (int i = 0; i < matrix.rowCount; ++i) {
        if (matrix(i, column) != SimpleFraction(0, 1) and !takenLine[i].first) {
            takenLine[i].first = true;
            takenLine[minIndex].second = true;
            return i;
        }
    }
    return -1;
}

int CheckOnHaveLineDependence(Matrix& matrix, std::vector<std::pair<int, int>>& sample){
    std::vector<int> lineD(sample.size() - 1);
    SimpleFraction zero = SimpleFraction(0, 1);
    int size = sample.size() - 1;
    int max = 0;
    for (int i = 0; i < size; ++i) {

        for (int j = 0; j < matrix.rowCount; j++){
            if (matrix(j, sample[i].second) != zero)
                lineD[i]++;

        }
    }

    for (int i = 0; i < size - 1; ++i) {
        if (lineD[max] > lineD[i+1])
            max = i;
    }
    if (lineD[max] < lineD[size - 1])
        max = size - 1;

    std::vector<std::pair<bool, bool>> takenLine(matrix.rowCount);
    for (int i = 0; i < size; ++i) {
        int minIndex = max;
        for (int j = 0; j < size; ++j) {
            if (lineD[j] <= lineD[minIndex] and !takenLine[j].second)
                minIndex = j;
        }

        sample[minIndex].first = FindRowIndex(matrix,sample[minIndex].second, minIndex, takenLine);
        int row = sample[minIndex].first;

        if (row == -1) return row;
        for(int j(0); j < size ; j++){

            if (takenLine[row].first and matrix(row, sample[j].second) != zero)
                lineD[j]--;
        }
    }
//    for (auto& item : sample) {
//        std::cout << item.first << " " << item.second << "\n";
//    }


    return 0;
}

bool NextSet(std::vector<std::pair<int, int>>& a, int variables, int cells){
//    variables = 6, cells = 4, 6 >= 4

    for (int i = cells - 1; i >= 0; --i) {
        int f = variables - cells + i + 1;
        if (a[i].second < f) {
            ++a[i].second;
            for (int j = i + 1; j < cells; ++j)
                a[j].second = a[j - 1].second + 1;
            return true;
        }
    }
    return false;
}

    void CreateCoordsBS(Matrix& matrix, std::vector<std::vector<std::pair<int, int>>>& coords){
    int variables = (matrix.columnCount - 2);
    int cells = matrix.rowCount;
    std::vector<std::pair<int, int>> sample(cells);


    for (int i = 0; i < cells; ++i) {
        sample[i].second = i;
    }


    coords.push_back(sample);
    if (variables > cells){
        while (NextSet(sample, variables, cells)){

            coords.push_back(sample);
            }
    }

}

bool ColumnAnswerIsPositive(Matrix const & matrix){
    for (int i = 0; i < matrix.rowCount; ++i) {
        if (SimpleFraction(0, 1) > matrix(i, matrix.columnCount - 1))
            return false;
    }
    return true;
}


std::vector<std::pair<int, int>> FindBasicSolutions(Matrix& outDataMatrix, bool isFindPositiveSolution){
    Matrix matrix = outDataMatrix;
    std::vector<std::vector<std::pair<int, int>>> coordBS /*= {{{0, 2}, {0, 3}, {0, 4}}}*/;
    CreateCoordsBS(matrix, coordBS);

    for (int i(coordBS.size() - 1); i >= 0 ; i--) {
        std::cout << "\n";
        for (auto &item: coordBS[i])
            std::cout  << item.first << ":" << item.second << " ";
        std::cout << "\n";
        for (int i(0); i < coordBS[i].size(); i++)
            std::cout << "x_" << coordBS[i][i].second + 1 << " ";
        std::cout << ": \n";
        matrix = GaussMod(matrix, coordBS[i]);

        if (isFindPositiveSolution)
            if (ColumnAnswerIsPositive(matrix)) {
                outDataMatrix = matrix;
                return coordBS[i];
            }
    }
    return {};
}