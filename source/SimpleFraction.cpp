//
// Created by vorop on 03.02.2023.
//

#include "../header/SimpleFraction.h"

SimpleFraction SimpleFraction::GetSimpleFractSumSubtr(SimpleFraction const & a,bool isSum) const{
    int minus = isSum ? 1 : -1;
    int commonDenom, commonNum(0);
    if (denominator != a.denominator) {
        commonDenom = denominator * a.denominator;
        commonNum += numerator * a.denominator;
        commonNum += minus * a.numerator * denominator;
    }
    else {
        commonDenom = denominator;
        commonNum = numerator + minus * a.numerator;
    }
    return {commonNum, commonDenom};
}

SimpleFraction SimpleFraction::GetSimpleFractMultDiv(SimpleFraction const & a, bool isMult) const{
    int commonDenom, commonNum;
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

SimpleFraction SimpleFraction::GetSimpleFractMultDiv(int const & a, bool isMult) const{
    int commonDenom, commonNum;
    commonNum = numerator * a;
    commonDenom = denominator;
    return {commonNum, commonDenom};
}

std::ostream& operator<<(std::ostream& out,  SimpleFraction const& fract){
    out << fract.numerator << "/" << fract.denominator;
    return out;
}