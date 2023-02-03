//
// Created by vorop on 03.02.2023.
//

#ifndef UNTITLED1_SIMPLEFRACTION_H
#define UNTITLED1_SIMPLEFRACTION_H

#include "iostream"
#include "string"


class SimpleFraction {
private:
    SimpleFraction GetSimpleFractSumSubtr(SimpleFraction const & a,bool isSum) const;
    SimpleFraction GetSimpleFractMultDiv(SimpleFraction const & a, bool isMult) const;
    SimpleFraction GetSimpleFractMultDiv(int const & a, bool isMult) const;
public:
    int numerator, denominator;
    SimpleFraction() : numerator(0), denominator(1){}
    SimpleFraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denom < 1) throw ;
    }
    void Print(){
     std::cout << (double) numerator / denominator;
    }

    SimpleFraction operator +(SimpleFraction const & a) const {
        return GetSimpleFractSumSubtr(a, true);
    }

    SimpleFraction operator -(SimpleFraction const & a) const {
        return GetSimpleFractSumSubtr(a, false);
    }

    SimpleFraction operator *(SimpleFraction const & a) const {
        return GetSimpleFractMultDiv(a, true);
    }

    SimpleFraction operator*(int const & a) const {
        return GetSimpleFractMultDiv(a, true);
    }

    SimpleFraction operator /(SimpleFraction const & a) const {
        return GetSimpleFractMultDiv(a, false);
    }

    bool operator!=(SimpleFraction const & a) const {
        return a.numerator != numerator or a.denominator != denominator;
    }

    bool operator==(SimpleFraction const & a) const {
        return a.numerator == numerator and a.denominator == denominator;
    }
};

std::ostream& operator<<(std::ostream& out,  SimpleFraction const& fract);


#endif //UNTITLED1_SIMPLEFRACTION_H
