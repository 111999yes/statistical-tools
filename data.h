#pragma once
#include <sstream>
#include <limits>

#include "statisticsData.h"
#include "type.h"


class Data{
public:
    Data() : numberOfVariable(0) {}
    Data(int _number){
        SetNumberOfVariable(_number);
    }

    void SetNumberOfVariable(int _numberVar){
        if(_numberVar != 2 && _numberVar != 1) throw std::invalid_argument("Number of variable must be 1 or 2");
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
    std::stringstream WriteOutStaData() const ;
    std::stringstream WriteOutMacData() const ;

    void CalStatis(){
        if(oriDataX.empty())
            throw std::logic_error("No data to calculate");
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

    const StaData& GetStaData() const {
        return statis;
    }

    const Data& GetRawData() const {
        return *this;
    }

    const Line& GetLine() const {
        if(numberOfVariable != 2) throw std::invalid_argument("Can't do that with one variable");
        return statis.reLine;
    }

    const double& GetR2() const {
        if(numberOfVariable != 2) throw std::invalid_argument("Can't do that with one variable");
        return statis.RSquare;
    }

    const double& GetRSS() const {
        if(numberOfVariable != 2) throw std::invalid_argument("Can't do that with one variable");
        return statis.RSS;
    }

    const double& GetRMSE() const {
        if(numberOfVariable != 2) throw std::invalid_argument("Can't do that with one variable");
        return statis.RMSE;
    }

    std::stringstream GetColRwaData() const {
        std::stringstream ss;
        if(numberOfVariable == 1){
            for(size_t i = 0; i < oriDataX.size(); ++i){
                ss << "    " << (i + 1) << ". " << oriDataX[i] << "\n";
            }
        }
        else if(numberOfVariable == 2){
            if(oriDataX.size() != oriDataY.size())
                throw std::runtime_error("Vector size mismatch");
            for(size_t i = 0; i < oriDataX.size(); ++i){
                ss << "    " << (i + 1) << ". {" << oriDataX[i] << ", " << oriDataY[i] << "}" << "\n";
            }
        }
        else{
            throw std::logic_error("Invalid number of variables");
        }
        return ss;
    }

    std::pair<double, double> GetData(const int index) const {
        std::pair<double, double> result;
        if(numberOfVariable == 1){
            if(index < 0 || static_cast<size_t>(index) >= oriDataX.size())
                throw std::invalid_argument("Index out of range");
            result = {oriDataX[index], std::numeric_limits<double>::quiet_NaN()};
        }
        else if(numberOfVariable == 2){
            if(index < 0 || index >= oriDataX.size() || static_cast<size_t>(index) >= oriDataY.size())
                throw std::invalid_argument("Index out of range");
            result = {oriDataX[index], oriDataY[index]};
        }
        else{
            throw std::logic_error("Invalid number of variables");
        }
        return result;
    }

    void AddData(const std::pair<std::string, std::string>& input, const COMMAND& cmd){
        if((cmd == COMMAND::ONE_NUMBER && numberOfVariable != 1) || (cmd == COMMAND::TWO_NUMBER && numberOfVariable != 2))
            throw std::invalid_argument("Number of variable mismatch");
        if(cmd == COMMAND::ONE_NUMBER){
            double x = std::stod(input.first);
            std::stringstream ss;
            ss << x;
            ss >> *this;
        }
        else if(cmd == COMMAND::TWO_NUMBER){
            double x = std::stod(input.first);
            double y = std::stod(input.second);
            std::stringstream ss;
            ss << x << " " << y;
            ss >> *this;
        }
    }

    void RemoveData(const int index){
        if(numberOfVariable == 1){
            if(index < 0 || static_cast<size_t>(index) >= oriDataX.size())
                throw std::invalid_argument("Index out of range");

            oriDataX.erase(oriDataX.begin() + index);
            oriDataY.erase(oriDataY.begin() + index);
        }
        else if(numberOfVariable == 2){
            if(index < 0 || index >= oriDataX.size() || static_cast<size_t>(index) >= oriDataY.size())
                throw std::invalid_argument("Index out of range");

            oriDataX.erase(oriDataX.begin() + index);
            oriDataY.erase(oriDataY.begin() + index);
        }
        else{
            throw std::logic_error("Invalid number of variables");
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
            if(d.oriDataX.size() != d.oriDataY.size()) throw std::invalid_argument("Vector size mismatch");
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
        else throw std::logic_error("Invalid number of variables");
        return os;
    }

private:
    int numberOfVariable;
    std::vector<double> oriDataX;
    std::vector<double> oriDataY;
    StaData statis;

};