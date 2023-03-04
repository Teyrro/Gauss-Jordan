//
// Created by vorop on 03.02.2023.
//

#include <iomanip>
#include "SimpleFraction.h"

SimpleFraction SimpleFraction::GetSimpleFractSumSubtr(SimpleFraction const & a,bool isSum) const{
    int minus = isSum ? 1 : -1;
    long long commonDenom, commonNum(0);
    if (denominator != a.denominator) {
        commonDenom = denominator * a.denominator;
        commonNum += numerator * a.denominator;
        commonNum += minus * a.numerator * denominator;
    }
    else {
        commonDenom = denominator;
        commonNum = numerator + minus * a.numerator;
    }

    if (commonDenom < 0) {
        commonDenom *= -1;
        commonNum *= -1;
    }

    return {commonNum, commonDenom};
}

long long SimpleFraction::GCD(long long a, long long b){
    if (a == 1 and a == -b) return -b;
    if (a != 0)
        if (a < b) {
            std::swap(a, b);
        }

    while (a % b != 0) {
        a = a % b;
        std::swap(a, b);
    }

    return b;
}


SimpleFraction SimpleFraction::GetSimpleFractMultDiv(SimpleFraction const & a, bool isMult) const{
    long long commonDenom, commonNum;
    if (isMult){
        commonDenom = denominator * a.denominator;
        commonNum = numerator * a.numerator;
    }
    else {
        commonDenom = denominator * a.numerator;
        commonNum = numerator * a.denominator;
    }

    if (commonDenom < 0) {
        commonDenom *= -1;
        commonNum *= -1;
    }

    return {commonNum, commonDenom};
}

SimpleFraction SimpleFraction::GetSimpleFractMultDiv(int const & a) const{
    long long commonDenom, commonNum;
    commonNum = numerator * a;
    commonDenom = denominator;

    if (commonDenom < 0) {
        commonDenom *= -1;
        commonNum *= -1;
    }

    return {commonNum, commonDenom};
}

std::ostream& operator<<(std::ostream& out,  SimpleFraction const& fract){
    std::string outData;
    std::stringstream transform;
    if (fract.denominator != 1) {
        transform << fract.numerator << "/" << fract.denominator;
        transform >> outData;
        out << outData;
    }
    else {
        out << fract.numerator;
    }
    return out;
}