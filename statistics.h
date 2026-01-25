#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Line.h"

double Minimum(const std::vector<double>& v){
    if(v.empty()) throw std::invalid_argument("The vector is empty");
    double minimum = v[0];
    for(int i = 0; i < v.size(); ++i){
        minimum = std::min(minimum, v[i]);
    }
    return minimum;
}

double Maximum(const std::vector<double>& v){
    if(v.empty()) throw std::invalid_argument("The vector is empty");
    double maximum = v[0];
    for(int i = 0; i < v.size(); ++i){
        maximum = std::max(maximum, v[i]);
    }
    return maximum;
}

double Range(const std::vector<double>& v){
    return Maximum(v) - Minimum(v);
}

double Median(std::vector<double> v){
    if(v.empty()) throw std::invalid_argument("The vector is empty");
    std::sort(v.begin(), v.end());
    int size = v.size();
    if(size % 2 == 1) return v[size / 2];
    return (v[size / 2 - 1] + v[size / 2]) / 2.0;

}

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

double Residual(double x, double y, const Line& line){
    return y - line.Estimate(x);
}

double ResidualSumSquares(const std::vector<double>& vx, const std::vector<double>& vy){
    Line reLine = RegressionLine(vx, vy);
    return ResidualSumSquares(vx, vy, reLine);
}

double ResidualSumSquares(const std::vector<double>& vx, const std::vector<double>& vy, const Line& reLine){
    if(vx.empty() || vy.empty()) throw std::invalid_argument("Vector is empty");
    if(vx.size() != vy.size()) throw std::invalid_argument("Vector size mismatch");
    double RSS = 0.0;
    for(int i = 0; i < vx.size(); ++i){
        double error = Residual(vx[i], vy[i], reLine);
        RSS += error * error;
    }
    return RSS;
}