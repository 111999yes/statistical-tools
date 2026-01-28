#pragma once
#include <fstream>
#include <sstream>


#include "data.h"

void WriteOut(std::string& rawFileName, std::string& staFileName, Data& data){
    std::ofstream RawFile;
    RawFile.open(rawFileName, std::ios::app);
    if(RawFile.fail()){
        throw std::runtime_error("Can not open file");
    }
    RawFile << data.WriteOutRawData().str();
    RawFile.close();
    
    std::ofstream StaFile;
    StaFile.open(staFileName, std::ios::app);
    if(StaFile.fail()){
        throw std::runtime_error("Can not open file");
    }
    StaFile << data.WriteOutStaData().str();
    StaFile.close();
}

std::stringstream Data::WriteOutRawData() const {
    stringstream ss;
    if(numberOfVariable == 2){
        ss << "Raw Data :\n";
        if(oriDataX.size() != oriDataY.size()) throw std::invalid_argument("Vector size mismatch");
        for(size_t i = 0; i < oriDataX.size(); ++i) ss << "    " << (i + 1) <<". {" << oriDataX[i] << ", " << oriDataY[i] << "}\n";
    }
    else if(numberOfVariable == 1){
        ss << "Raw Data :\n";
        for(size_t i = 0; i < oriDataX.size(); ++i) ss << "    " << (i + 1) << ". " << oriDataX[i] << "\n";
    }
    else throw std::logic_error("numberOfVariable not set");
    return ss;
}

std::stringstream Data::WriteOutStaData(){
    stringstream ss;
    CalStatis();
    if(numberOfVariable == 1){
        ss << "Statistics Data:\n";
        ss << "    Minimum : " << statis.minimum[0] << "\n";
        ss << "    Maximum : " << statis.maximum[0] << "\n";
        ss << "    Range : " << statis.range[0] << "\n";
        ss << "    Median : " << statis.median[0] << "\n";
        ss << "    Average : " << statis.Avg[0] << "\n";
        ss << "    Variance : " << statis.Var[0] << "\n";
        ss << "    Standard Deviation : " << statis.SD[0];
    }
    else{
        ss << "Statistics Data:\n";
        ss << "    Minimum : {" << statis.minimum[0] << ", " << statis.minimum[1] << "}\n";
        ss << "    Maximum : {" << statis.maximum[0] << ", " << statis.maximum[1] << "}\n";
        ss << "    Range : {" << statis.range[0] << ", " << statis.range[1]  << "}\n";
        ss << "    Median : {" << statis.median[0] << ", " << statis.median[1] << "}\n";
        ss << "    Average : {" << statis.Avg[0] << ", " << statis.Avg[1] << "}\n";
        ss << "    Variance : {" << statis.Var[0] << ", " << statis.Var[1] << "}\n";
        ss << "    Standard Deviation : {" << statis.SD[0] << ", " << statis.SD[1] << "}\n";
        ss << "    Covariance : " << statis.coVar << "\n";
        ss << "    Correlation Coefficient : " << statis.relCoef << "\n";
        ss << "    RSS : " << statis.RSS << "\n";
        ss << "    RMSE : " << statis.RMSE << "\n";
        ss << "    R^2 : " << statis.RSquare << "\n";
        ss << "    Regression Line : " << statis.reLine;
        ss << " => ";
        statis.reLine.printLine(ss, SLOPE_INTERCEPT_FORM);
        ss << "\n";
    }
    return ss;
}
