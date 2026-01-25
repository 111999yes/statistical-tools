#pragma once
#include <iostream>
#include <vector>
#include <cmath>

#include "Line.h"

double Average(const std::vector<double>& v){
    if(v.empty()) throw std::invalid_argument("Vector is empty");
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
    if(vx.size() != vy.size()) throw std::invalid_argument("Vector size mismatch");
    double Xavg = Average(vx);
    double Yavg = Average(vy);
    double deltaSum = 0.0;
    for(int i = 0; i < vx.size(); ++i) deltaSum += (vx[i] - Xavg) * (vy[i] - Yavg);
    return deltaSum / (double)vx.size();
}

double CorrelationCoefficient(const std::vector<double>& vx, const std::vector<double>& vy){
    if(std::abs(Variance(vx)) < 1e-8) 
        throw std::runtime_error("Variance of x is zero");
    if(std::abs(Variance(vy)) < 1e-8)
        throw std::runtime_error("Variance of y is zero");
    if(vx.size() < 2 || vy.size() < 2)
        throw std::runtime_error("Need at least two point");
    return Covariance(vx, vy) / sqrt(Variance(vx) * Variance(vy));
}

Line RegressionLine(const std::vector<double>& vx, const std::vector<double>& vy){
    std::pair<double, double> avgPoint = {Average(vx), Average(vy)};
    if(std::abs(Variance(vx)) < 1e-8) 
        throw std::runtime_error("Variance of x is zero");
    if(vx.size() < 2 || vy.size() < 2)
        throw std::runtime_error("Need at least two point");
    double slope = Covariance(vx, vy) / Variance(vx);
    Line regressionLine(slope, avgPoint);
    return regressionLine;
}
