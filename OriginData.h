#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>

#include "statistics.h"
#include "Line.h"

class OriginData{
public:
    OriginData() : numberOfVariable(0) {}
    OriginData(int _number) : numberOfVariable(_number) {}

    void InputData(int _numberVar){
        if(_numberVar > 2 || _numberVar < 1) throw std::invalid_argument("Number of variable must be 1 or 2");
        else numberOfVariable = _numberVar;
    }

    void clear(){
        oriDataX.clear();
        oriDataY.clear();
    }

    size_t Size() const {
        return oriDataY.size();
    }

    OriginData& operator=(const OriginData& d){
        if(this == &d) return *this;
        numberOfVariable = d.numberOfVariable;
        this->oriDataX.clear();
        this->oriDataY.clear();
        for(int i = 0; i < d.oriDataY.size(); ++i){
            this->oriDataY.push_back(d.oriDataY[i]);
        }
        for(int i = 0; i < d.oriDataX.size(); ++i){
            this->oriDataX.push_back(d.oriDataX[i]);
        }
        return *this;
    }

    friend std::istream& operator>>(std::istream& is, OriginData& d){
        if(d.numberOfVariable == 1){
            double val;
            if(is >> val)
                d.oriDataY.push_back(val);
        }
        else if(d.numberOfVariable == 2){
            double valX, valY;
            if(is >> valX >> valY){
                d.oriDataX.push_back(valX);
                d.oriDataY.push_back(valY);
            }
        }
        else is.setstate(std::ios::failbit);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const OriginData& d){
        if(d.numberOfVariable == 2){
            assert(d.oriDataX.size() == d.oriDataY.size());
            os << "[ ";
            for(size_t i = 0; i < d.oriDataX.size(); ++i) os << "{" << d.oriDataX[i] << ", " << d.oriDataY[i] << "} ";
            os << " ]";
        }
        else if(d.numberOfVariable == 1){
            os << "[";
            for(size_t i = 0; i < d.oriDataY.size(); ++i) os << " " << d.oriDataY[i];
            os << " ]";
        }
        else throw std::logic_error("numberOfVariable not set");
        return os;
    }

private:
    int numberOfVariable;
    std::vector<double> oriDataX;
    std::vector<double> oriDataY;

};