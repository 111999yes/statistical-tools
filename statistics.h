#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class Line{
public:
    Line(double _m, double _b) : slope(_m), yIntercept(_b) {}

    friend std::ostream& operator<<(std::ostream& os, const Line& l){
        os << "y = ";
        os << l.slope << "x + ";
        os << l.yIntercept; 
        return os;
    }

private:
    double slope;
    double yIntercept;
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

double CorrelationCoefficient(const std::vector<double>& vx, const std::vector<double>& vy){
    double Xavg = Average(vx);
    double Yavg = Average(vy);
    double deltaSum = 0.0;
    for(int i = 0; i < vx.size(); ++i) deltaSum += (vx[i] - Xavg) * (vy[i] - Yavg);
    return deltaSum / sqrt(Variance(vx) * Variance(vy));
}