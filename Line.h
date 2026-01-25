#pragma once
#include <iostream>
#include <utility>
#include <cmath>

enum MODE{POINT_SLOPE_FORM, SLOPE_INTERCEPT_FORM};

class Line{
public:
    
    Line(double _m, std::pair<double, double> _avgPoint) : slope(_m), avgPoint(_avgPoint) {}

    void printLine(std::ostream& os, MODE mode) const {
        if(mode == POINT_SLOPE_FORM) os << *this;
        else{
            Line result(slope, {0, avgPoint.second - slope * avgPoint.first});
            os << result;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Line& l){
        const double eps = 1e-8;
        double x0 = l.avgPoint.first;
        double y0 = l.avgPoint.second;
        double m = l.slope;
        os << "y";
        if(std::abs(y0) > eps){
            os << ((y0 > 0) ? " - " : " + ") << std::abs(y0);
        }

        os << " = ";

        if(std::abs(m - 1.0) < eps) {}
        else if(std::abs(m + 1.0) < eps) {os << "-";}
        else {os << m;}

        os << "(x";
        if(std::abs(x0) > eps){
            os << ((x0 > 0) ? " - " : " + ") << std::abs(x0);
        }
        os << ")";

        return os;
    }

private:
    double slope;
    std::pair<double, double> avgPoint;
};