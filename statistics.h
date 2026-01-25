#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

class Line{
public:
    
    Line(double _m, std::pair<double, double> _avgPoint) : slope(_m), avgPoint(_avgPoint) {}

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

double Average(const std::vector<double>& v){
    double sum = 0.0;
    for(int i = 0; i < v.size(); ++i) sum += v[i];
    return sum / (double)v.size();
}

double Variance(const std::vector<double>& v){
    double deltaSum = 0.0;
    double avg = Average(v);
    for(int i = 0; i < v.size(); ++i) deltaSum += (v[i] - avg) * (v[i] - avg);
    return deltaSum / (double)v.size();
}

double StandardDeviation(const std::vector<double>& v){
    return sqrt(Variance(v));
}

double Covariance(const std::vector<double>& vx, const std::vector<double>& vy){
    double Xavg = Average(vx);
    double Yavg = Average(vy);
    double deltaSum = 0.0;
    for(int i = 0; i < vx.size(); ++i) deltaSum += (vx[i] - Xavg) * (vy[i] - Yavg);
    return deltaSum;
}

double CorrelationCoefficient(const std::vector<double>& vx, const std::vector<double>& vy){
    return Covariance(vx, vy) / sqrt(Variance(vx) * Variance(vy));
}

Line RegressionLine(const std::vector<double>& vx, const std::vector<double>& vy){
    std::pair<double, double> avgPoint = {Average(vx), Average(vy)};
    double slope = Covariance(vx, vy) / Variance(vx);
    Line regressionLine(slope, avgPoint);
    return regressionLine;
}
