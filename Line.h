#pragma once
#include <iostream>
#include <utility>
#include <cmath>

#include "type.h"

class Line{
public:
    
    Line() {}
    Line(double _m, std::pair<double, double> _avgPoint) : slope(_m), avgPoint(_avgPoint) {}
    Line(const Line& l) : slope(l.slope), avgPoint(l.avgPoint) {}

    void printLine(std::ostream& os, MODE mode) const {
        if(mode == POINT_SLOPE_FORM) os << *this;
        else{
            const double eps = 1e-8;
            double intercept = (avgPoint.first * slope - avgPoint.second);
            os << "y = ";
            os << slope << "x ";
            if(std::abs(intercept) > eps){
                os << ((intercept > 0) ? "+ ":"- ") << std::abs(intercept);
            }
        }
    }

    double Estimate(const double x) const {
        return avgPoint.second + slope * (x - avgPoint.first);
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