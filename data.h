#pragma once
#include <cassert>
#include <sstream>

#include "statisticsData.h"
#include "type.h"


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

    int GetNumOfVar() const {
        return numberOfVariable;
    }

    std::stringstream WriteOutRawData() const ;
    std::stringstream WriteOutStaData();

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

    void PrintRawData() const {
        std::cout << *this << std::endl;
    }

    void PrintLine() const {
        if(numberOfVariable != 2) throw std::invalid_argument("Can't do that with one variable");
        std::cout << statis.reLine << std::endl;
    }

    void PrintR2() const {
        if(numberOfVariable != 2) throw std::invalid_argument("Can't do that with one variable");
        std::cout << statis.RSquare << std::endl;
    }

    void PrintRSS() const {
        if(numberOfVariable != 2) throw std::invalid_argument("Can't do that with one variable");
        std::cout << statis.RSS << std::endl;
    }

    void PrintRMSE() const {
        if(numberOfVariable != 2) throw std::invalid_argument("Can't do that with one variable");
        std::cout << statis.RMSE << std::endl;
    }

    void AddData(const std::pair<std::string, std::string>& input, const COMMAND& cmd){
        if((cmd == ONE_NUMBER && numberOfVariable != 1) || (cmd == TWO_NUMBER && numberOfVariable != 2))
            throw std::invalid_argument("Number of variable mismatch");
        if(cmd == ONE_NUMBER){
            double x = std::stod(input.first);
            std::stringstream ss;
            ss << x;
            ss >> *this;
        }
        else if(cmd == TWO_NUMBER){
            double x = std::stod(input.first);
            double y = std::stod(input.second);
            std::stringstream ss;
            ss << x << " " << y;
            ss >> *this;
        }
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
            os << YELLOW << "Raw Data :\n" << RESET;
            assert(d.oriDataX.size() == d.oriDataY.size());
            os << "    [ ";
            for(size_t i = 0; i < d.oriDataX.size(); ++i) os << "{" << d.oriDataX[i] << ", " << d.oriDataY[i] << "} ";
            os << "]";
        }
        else if(d.numberOfVariable == 1){
            os << YELLOW << "Raw Data :\n" << RESET;
            os << "    [ ";
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
        std::cout << GREEN << "Enter the number of variables : " << RESET;
        if(std::cin >> num && (num == 1 || num == 2)){
            data.clear();
            data.InputData(num);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout  << RED << ">Invalid input number, please retry\n" << RESET;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}