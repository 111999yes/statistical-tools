#pragma once

#include "statistics.h"
#include "type.h"

class StaData{
friend class Data;
public:

    StaData() : numOfVar(0) {
        std::fill_n(minimum, 2, 0.0);
        std::fill_n(maximum, 2, 0.0);
        std::fill_n(range, 2, 0.0);
        std::fill_n(median, 2, 0.0);
        std::fill_n(Avg, 2, 0.0);
        std::fill_n(Var, 2, 0.0);
        std::fill_n(SD, 2, 0.0);
        coVar = 0.0;
        relCoef = 0.0;
        RSS = 0.0;
        RMSE = 0.0;
        RSquare = 0.0;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const StaData& sta){
        if(sta.numOfVar == 1){
            os << YELLOW << "Statistics Data:\n" << RESET;
            os << "    Minimum : " << sta.minimum[0] << "\n";
            os << "    Maximum : " << sta.maximum[0] << "\n";
            os << "    Range : " << sta.range[0] << "\n";
            os << "    Median : " << sta.median[0] << "\n";
            os << "    Average : " << sta.Avg[0] << "\n";
            os << "    Variance : " << sta.Var[0] << "\n";
            os << "    Standard Deviation : " << sta.SD[0];
        }
        else{
            os << YELLOW << "Statistics Data:\n" << RESET;
            os << "    Minimum : {" << sta.minimum[0] << ", " << sta.minimum[1] << "}\n";
            os << "    Maximum : {" << sta.maximum[0] << ", " << sta.maximum[1] << "}\n";
            os << "    Range : {" << sta.range[0] << ", " << sta.range[1]  << "}\n";
            os << "    Median : {" << sta.median[0] << ", " << sta.median[1] << "}\n";
            os << "    Average : {" << sta.Avg[0] << ", " << sta.Avg[1] << "}\n";
            os << "    Variance : {" << sta.Var[0] << ", " << sta.Var[1] << "}\n";
            os << "    Standard Deviation : {" << sta.SD[0] << ", " << sta.SD[1] << "}\n";
            os << "    Covariance : " << sta.coVar << "\n";
            os << "    Correlation Coefficient : " << sta.relCoef << "\n";
            os << "    RSS : " << sta.RSS << "\n";
            os << "    RMSE : " << sta.RMSE << "\n";
            os << "    R^2 : " << sta.RSquare << "\n";
            os << "    Regression Line : " << sta.reLine;
            os << " => ";
            sta.reLine.printLine(os, MODE::SLOPE_INTERCEPT_FORM);
        }
        return os;
    }

private:
    int numOfVar;
/*==========================*/
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
};