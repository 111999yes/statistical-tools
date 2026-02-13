#pragma once
#include <iostream>
#include <sstream>

#include "type.h"
#include "history.h"
#include "data.h"

class Output{
public:

    static constexpr const char* NEWLINE = "\n";
    static constexpr const char* SEPERATELINE = "======================================================================";

    inline static void SeperateLine(){
        std::cout << ORANGE << "\n" << SEPERATELINE << "\n\n" << RESET;
    }

    static void Input(){
        std::stringstream ss;
        ss << ">";
        std::cout << ss.str();
    }

    static void Info(const std::string& s){
        std::stringstream ss;
        ss << CYAN << "[Info] " << RESET << s;
        std::cout << ss.str();
    }

    static void Success(const std::string& s){
        std::stringstream ss;
        ss << GREEN << "[Success] " << RESET << s;
        std::cout << ss.str();
    }

    static void Error(const std::string& s){
        std::stringstream ss;
        ss << RED << "[Error] " << RESET << s;
        std::cerr << ss.str();
    }

    static void Prompt(const std::string& s){
        std::stringstream ss;
        ss << YELLOW << "[Prompt] " << RESET << s;
        std::cout << ss.str();
    }

    static void History(const History& history){
        std::cout << history;
    }

    static void StaData(const Data& data){
        std::cout << data.GetStaData();
    }

    static void RawData(const Data& data){
        std::cout << data;
    }

    static void Line(const Data& data){
        std::stringstream ss;
        ss << "Regression line : " << data.GetLine();
        Info(ss.str());
    }

    static void R2(const Data& data){
        std::stringstream ss;
        ss << "R^2 = "<< data.GetR2();
        Info(ss.str());
    }

    static void RSS(const Data& data){
        std::stringstream ss;
        ss << "RSS = " << data.GetRSS();
        Info(ss.str());
    }

    static void RMSE(const Data& data){
        std::stringstream ss;
        ss << "RMSE = "<< data.GetRMSE();
        Info(ss.str());
    }

    static void ColRawData(const Data& data){
        std::stringstream ss = data.GetColRwaData();
        std::cout << ss.str();
    }

    static void NewLine(){
        std::cout << NEWLINE;
    }

    static void Introduction(){
        std::cout << ORANGE << "=============================INTRODUCTION=============================\n\n" << RESET;
        PrintHelp(1);
        std::cout << ORANGE << "\n" << SEPERATELINE << "\n" << RESET;
    }

    static void PrintHelp(bool isFirstTime){
        if(!isFirstTime) std::cout << CYAN << "=================================HELP=================================\n" << RESET;
        if(!isFirstTime) std::cout << "\n";
        std::cout << YELLOW << "Commands:\n" << RESET;
        std::cout << "  !" << GREEN << "HELP           " << RESET << ": Show this help message\n";
        std::cout << "  !" << RED << "EXIT           " << RESET << ": Exit current input loop\n";
        std::cout << "  !" << BLUE << "CLEAR          " << RESET << ": Clear all data and reset variable count\n";
        std::cout << "  !" << BLUE << "WRITEIN        " << RESET << ": Read data from " << CYAN << "\"##Raw Data\"" << RESET << " region in the file\n";
        std::cout << "  !" << BLUE << "WRITEOUT       " << RESET << ": Write data into the file\n";
        std::cout << "  !" << BLUE << "REMOVE         " << RESET << ": Remove a data entry by index\n";
        std::cout << "  !" << BLUE << "HISTORY        " << RESET << ": Print the command history\n";
        std::cout << "  !" << MAGENTA << "PRINTALLDATA   " << RESET << ": Print raw and statistical data\n";
        std::cout << "  !" << MAGENTA << "PRINTRAWDATA   " << RESET << ": Print only raw input data\n";
        std::cout << "  !" << MAGENTA << "PRINTSTADATA   " << RESET << ": Print only calculated statistics\n";
        std::cout << "  !" << MAGENTA << "PRINTLINE      " << RESET << ": Print the regression line\n";
        std::cout << "  !" << MAGENTA << "PRINTR2        " << RESET << ": Print coefficient of determination (R^2)\n";
        std::cout << "  !" << MAGENTA << "PRINTRSS       " << RESET << ": Print residual sum of squares (RSS)\n";
        std::cout << "  !" << MAGENTA << "PRINTRMSE      " << RESET << ": Print root mean square error (RMSE)\n";
        std::cout << "\n";
        std::cout << YELLOW << "Number input:\n" << RESET;
        std::cout << "  Enter numbers directly to add them to the dataset.\n";
        std::cout << "  For single-variable data, enter one number at a time.\n";
        std::cout << "  For two-variable data, enter X and Y separated by a space.\n";
        std::cout << "\n";
        std::cout << YELLOW << "Notes:\n" << RESET;
        std::cout << "  - Variable number is fixed at the start. Use !CLEAR to reset.\n";
        std::cout << "  - Commands are case-insensitive.\n";
        std::cout << "  - Numbers can include signs (+/-) and decimal points.\n";
        if(!isFirstTime) std::cout << CYAN << SEPERATELINE << "\n" << RESET;
    }
};