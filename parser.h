#pragma once
#include <iostream>
#include <string>

#include "type.h"
#include "data.h"

void AllCaps(std::string& s){
    for(size_t i = 0; i < s.size(); ++i){
        if(s[i] >= 'a' && s[i] <= 'z'){
            s[i] = s[i] - 'a' + 'A';
        }
    }
}

void RemoveSpace(std::string& s){
    std::string result;
    for(size_t i = 0; i < s.size(); ++i){
        if(s[i] != ' '){
            result += s[i];
        }
    }
    s = result;
}

bool IsNumber(const std::string& s){
    try{
        size_t idx;
        std::stod(s, &idx);
        return s.size() == idx;
    }
    catch(...){
        return false;
    }
}

std::pair<std::string, std::string> SeperateString(const std::string& s){
    bool hasNumAppear = false;
    bool hasSpaAppear = false;
    std::string first;
    std::string second;
    for(size_t i = 0; i < s.size(); ++i){
        if(!hasNumAppear && (s[i] >= '0' && s[i] <= '9')){
            hasNumAppear = true;
        }
        else if(hasNumAppear && s[i] == ' '){
            hasSpaAppear = true;
        }
        else if(hasSpaAppear){
            second += s[i];
        }
        if(!hasSpaAppear){
            first += s[i];
        }
    }
    return {first, second};
}

COMMAND Parser(const std::string& inputString){
    std::string cmd = inputString;
    AllCaps(cmd);
    RemoveSpace(cmd);
    if(cmd == "!HELP") return HELP;
    if(cmd == "!EXIT") return EXIT;
    if(cmd == "!CLEAR") return CLEAR;
    if(cmd == "!PRINTALLDATA") return PRINT_ALL_DATA;
    if(cmd == "!PRINTRAWDATA") return PRINT_RAW_DATA;
    if(cmd == "!PRINTSTADATA") return PRINT_STA_DATA;
    if(cmd == "!PRINTLINE") return PRINT_LINE;
    if(cmd == "!PRINTR2") return PRINT_R2;
    if(cmd == "!PRINTRSS") return PRINT_RSS;
    if(cmd == "!PRINTRMSE") return PRINT_RMSE;
    std::pair<std::string, std::string> seperated = SeperateString(inputString);
    if(IsNumber(seperated.first) && IsNumber(seperated.second) && !seperated.second.empty()) return TWO_NUMBER;
    if(IsNumber(seperated.first) && seperated.second.empty()) return ONE_NUMBER;
    return UNDEFINED;

}

void PrintHelp(bool isFirstTime){
    if(!isFirstTime) std::cout << CYAN << "=================================HELP=================================\n" << RESET;
    if(!isFirstTime) std::cout << "\n";
    std::cout << YELLOW << "Commands:\n" << RESET;
    std::cout << "  !" << CYAN << "HELP           " << RESET << ": Show this help message\n";
    std::cout << "  !" << RED << "EXIT           " << RESET << ": Exit current input loop\n";
    std::cout << "  !" << GREEN << "CLEAR          " << RESET << ": Clear all data and reset variable count\n";
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
}

void StringToDouble(const std::string& input, const Data& data){
    std::string number = input;
    int numOfVar = data.GetNumOfVar();
    if(numOfVar == 1){

    }
    else if(numOfVar == 2){

    }
    else throw std::runtime_error("Number of variable must be 1 or 2");
}