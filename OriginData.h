#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>

#include "statistics.h"
#include "Line.h"

class StaData{
friend class Data;
public:
    
    friend std::ostream& operator<<(std::ostream& os, const StaData& sta){
        if(sta.numOfVar == 1){
            os << "Minimum : " << sta.minimum[0] << "\n";
            os << "Maximum : " << sta.maximum[0] << "\n";
            os << "Range : " << sta.range[0] << "\n";
            os << "Median : " << sta.median[0] << "\n";
            os << "Average : " << sta.Avg[0] << "\n";
            os << "Variance : " << sta.Var[0] << "\n";
            os << "Standard Deviation : " << sta.SD[0] << "\n";
        }
        else{
            os << "Minimum : {" << sta.minimum[0] << ", " << sta.minimum[1] << "}\n";
            os << "Maximum : {" << sta.maximum[0] << ", " << sta.maximum[1] << "}\n";
            os << "Range : {" << sta.range[0] << ", " << sta.range[1]  << "}\n";
            os << "Median : {" << sta.median[0] << ", " << sta.median[1] << "}\n";
            os << "Average : {" << sta.Avg[0] << ", " << sta.Avg[1] << "}\n";
            os << "Variance : {" << sta.Var[0] << ", " << sta.Var[1] << "}\n";
            os << "Standard Deviation : {" << sta.SD[0] << ", " << sta.SD[1] << "}\n";
            os << "Covariance" << sta.coVar << "\n";
            os << "Correlation Coefficient" << sta.relCoef << "\n";
            os << "RSS" << sta.RSS << "\n";
            os << "RMSE" << sta.RMSE << "\n";
            os << "R^2" << sta.RSquare << "\n";
            os << "Regression Line" << sta.reLine;
        }
        return os;
    }

private:
    double minimum[2];
    double maximum[2];
    double range[2];
    double median[2];
    double Avg[2];
    double Var[2];
    double SD[2];
/*==========================*/
    double coVar;
    double relCoef;
    double RSS;
    double RMSE;
    double RSquare;
    Line reLine;
/*==========================*/
    int numOfVar;
};

class Data{
public:
    Data() : numberOfVariable(0) {}
    Data(int _number){
        InputData(_number);
    }

    void InputData(int _numberVar){
        if(_numberVar > 2 || _numberVar < 1) throw std::invalid_argument("Number of variable must be 1 or 2");
        else{
            numberOfVariable = _numberVar;
            statis.numOfVar = _numberVar;
        }
    }

    void clear(){
        oriDataX.clear();
        oriDataY.clear();
    }

    size_t Size() const {
        return oriDataX.size();
    }

    void CalStatis(){
        statis.minimum[0] = Minimum(oriDataX);
        statis.minimum[1] = Minimum(oriDataY);
        statis.maximum[0] = Maximum(oriDataX);
        statis.maximum[1] = Maximum(oriDataY);
        statis.range[0] = statis.maximum[0] = statis.minimum[0];
        statis.range[1] = statis.maximum[1] = statis.minimum[1];
        statis.median[0] = Median(oriDataX);
        statis.median[1] = Median(oriDataY);
        statis.Avg[0] = Average(oriDataX);
        statis.Avg[1] = Average(oriDataY);
        statis.Var[0] = Variance(oriDataX);
        statis.Var[1] = Variance(oriDataY);
        statis.SD[0] = sqrt(statis.Var[0]);
        statis.SD[1] = sqrt(statis.Var[1]);
    /*===========================================================*/
        statis.coVar = Covariance(oriDataX, oriDataY);
        statis.relCoef = CorrelationCoefficient(oriDataX, oriDataY);
        statis.RSS = ResidualSumSquares(oriDataX, oriDataY);
        statis.RMSE = RootMeanSquareError(oriDataX, oriDataY);
        statis.RSquare = CoefficientOfDetermination_RSquare(oriDataX, oriDataY);
        statis.reLine = RegressionLine(oriDataX, oriDataY);
    }

    void PrintStaData() const {
        std::cout << statis << std::endl;
    }

    friend std::istream& operator>>(std::istream& is, Data& d){
        if(d.numberOfVariable == 1){
            double val;
            if(is >> val){
                d.oriDataX.push_back(val);
                d.oriDataY.push_back(d.oriDataX.size());
            }
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

    friend std::ostream& operator<<(std::ostream& os, const Data& d){
        if(d.numberOfVariable == 2){
            assert(d.oriDataX.size() == d.oriDataY.size());
            os << "[ ";
            for(size_t i = 0; i < d.oriDataX.size(); ++i) os << "{" << d.oriDataX[i] << ", " << d.oriDataY[i] << "} ";
            os << " ]";
        }
        else if(d.numberOfVariable == 1){
            os << "[";
            for(size_t i = 0; i < d.oriDataX.size(); ++i) os << " " << d.oriDataX[i];
            os << " ]";
        }
        else throw std::logic_error("numberOfVariable not set");
        return os;
    }

private:
    int numberOfVariable;
    std::vector<double> oriDataX;
    std::vector<double> oriDataY;
    StaData statis;

};