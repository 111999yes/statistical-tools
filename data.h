#pragma once
#include <cassert>

#include "statisticsData.h"


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
        statis.range[0] = Range(oriDataX);
        statis.range[1] = Range(oriDataY);
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
            os << "[ ";
            for(size_t i = 0; i < d.oriDataX.size(); ++i) os << d.oriDataX[i] << ", ";
            if(d.oriDataX.size() != 0) os << "\b\b";
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

void SetUpVariable(Data& data){
    int num;
    while(true){
        std::cout << "Enter the number of variables :";
        if(std::cin >> num && (num == 1 || num == 2)){
            data.clear();
            data.InputData(num);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "Invalid input number, please retry";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}