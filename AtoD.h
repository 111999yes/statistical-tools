#pragma once
#include <iostream>

double AtoD(const std::string& s){
    double result = 0.0;
    int idx = 0;
    while(s[idx] != '.' && idx < s.size()){
        result = result * 10 + (s[idx] - '0');
        ++idx;
    }
    int denominator = 10;
    while(idx < s.size()){
        if(s[idx] == '.'){
            ++idx;
            continue;
        }
        result += (double)(s[idx] - '0') / denominator;
        denominator *= 10;
        ++idx;
    }
    return result;
}