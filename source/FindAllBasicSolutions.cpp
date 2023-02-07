//
// Created by vorop on 05.02.2023.
//

#include <list>
#include <map>
#include "../header/Matrix.h"
#include "../header/FindAllBasicSolutions.h"

long long factorial(int x){
    long long answer(1);
    for (int i = 1; i <= x; ++i) {
        answer *= i;
    }
    return answer;
}

int FindRowIndex(Matrix& matrix, int column){

    for (int i = 0; i < matrix.rowCount; ++i) {
        if (matrix(i, column) != SimpleFraction(0, 1))
            return i;
    }
    return -1;
}

int CheckOnHaveLineDependence(Matrix& matrix, std::vector<std::pair<int, int>>& sample){
    std::vector<int> lineD(sample.size());
    SimpleFraction zero = SimpleFraction(0, 1);
    for (int i = 0; i < sample.size(); ++i) {
        for (int j = 0; j < matrix.rowCount; j++){
            if (matrix(j, sample[i].second) != zero)
                lineD[i]++;
        }+
    }

    for (int i = 0; i < lineD.size(); ++i) {
        int minIndex = 0;
        for (int j = 1; j < lineD.size(); ++j) {
            if (lineD[minIndex] > lineD[j])
                minIndex = j;
        }

        sample[minIndex].first = FindRowIndex(matrix,sample[minIndex].second);
    }

    return 0;
}

bool NextSet(std::vector<std::pair<int, int>>& a, int n, int m){
    // m = 4, n = 6

    for (int i = m - 1; i >= 0; --i) {
        int f = n - m + i + 1;
        if (a[i].second < f) {
            ++a[i].second;
            for (int j = i + 1; j < m; ++j)
                a[j].second = a[j - 1].second + 1;
            return true;
        }
    }
    return false;
    }


    void CreateCoordsBS(Matrix& matrix, std::vector<std::vector<std::pair<int, int>>>& coords){
    int variables = (matrix.columnCount-1);
    int cells = matrix.rowCount;
    std::vector<std::pair<int, int>> sample(cells);


    for (int i = 0; i < cells; ++i) {
        sample[i].second = i;
    }

    coords.push_back(sample);
    if (variables >= cells){
        while (NextSet(sample, variables, cells))
            coords.push_back(sample);
    }

}


void FindBasicSolutions(Matrix& matrix){
    std::vector<std::vector<std::pair<int, int>>> coordBS;
    int countBS(factorial(matrix.columnCount - 1) /
                (factorial((matrix.columnCount - 1) - matrix.rowCount) * factorial(matrix.rowCount)));
    CreateCoordsBS(matrix, coordBS);
    for (auto& ptr : coordBS) {
        for (auto& item : ptr)
            std::cout << item.second << " ";
        std::cout << "\n";

    }
//    Matrix basicSolutions = Matrix(countBS, matrix.columnCount);
}