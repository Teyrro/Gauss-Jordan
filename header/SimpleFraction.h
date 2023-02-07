//
// Created by vorop on 03.02.2023.
//

#ifndef UNTITLED1_SIMPLEFRACTION_H
#define UNTITLED1_SIMPLEFRACTION_H

#include "iostream"
#include "string"


class SimpleFraction {
private:
    [[nodiscard]] SimpleFraction GetSimpleFractSumSubtr(SimpleFraction const & a,bool isSum) const;
    [[nodiscard]] SimpleFraction GetSimpleFractMultDiv(SimpleFraction const & a, bool isMult) const;
    [[nodiscard]] SimpleFraction GetSimpleFractMultDiv(int const & a) const;
    long long GCD(long long a, long long b);
public:
    long long numerator;
    long long denominator;
    SimpleFraction() : numerator(0), denominator(1){}
    SimpleFraction(long long num, long long denom) : numerator(num), denominator(denom) {
//        if (denom == 0 and num == 0) {
//            denominator = 1;
//        }
        if (denom == 0) throw "denominator can't be able zero";

        long long div(1);
        do {
            div = GCD(numerator, denominator);
            numerator /= div;
            denominator /= div;
        } while (div  != 1);

        if (denominator < 0) {
            denominator *= -1;
            numerator *= -1;
        }
    }
    void Print() const {
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
        return GetSimpleFractMultDiv(a);
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

    bool operator<(SimpleFraction const & a) const {
        long long commonNum1 = + a.denominator * numerator;
        long long commonNum2 = a.numerator * denominator;
        return abs(commonNum1) < abs(commonNum2);
    }
};

std::ostream& operator<<(std::ostream& out,  SimpleFraction const& fract);


#endif //UNTITLED1_SIMPLEFRACTION_H
