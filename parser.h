#pragma once
#include <iostream>
#include <string>
#include <charconv>

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
        if(s[i] != ' ' && s[i] != '\t'){
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

void RemoveFrontSpace(std::string& s){
    size_t pos = s.find_first_not_of(" \t\n\r");
    if(pos == std::string::npos){
        s.clear();
    }else{
        s.erase(0, pos);
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
    RemoveFrontSpace(first);
    return {first, second};
}

void RemoveFrontNonNumber(std::string& s){
    size_t pos = s.find_first_of(".0123456789");
    if(pos == std::string::npos){
        s.clear();
    }
    else{
        s.erase(0, pos);
    }
}

std::string DoubleToString(double x){
    std::ostringstream oss;
    oss << x;
    return oss.str();
}

CommandResult Parser(const std::string& inputString){
    std::string cmd = inputString;
    CommandResult result;
    AllCaps(cmd);
    RemoveSpace(cmd);
    std::pair<std::string, std::string> seperated = SeperateString(inputString);
    if(cmd == "!HELP") result.cmd = COMMAND::HELP;
    else if(cmd == "!EXIT") result.cmd = COMMAND::EXIT;
    else if(cmd == "!CLEAR") result.cmd = COMMAND::CLEAR;
    else if(cmd == "!PRINTALLDATA") result.cmd = COMMAND::PRINT_ALL_DATA;
    else if(cmd == "!PRINTRAWDATA") result.cmd = COMMAND::PRINT_RAW_DATA;
    else if(cmd == "!PRINTSTADATA") result.cmd = COMMAND::PRINT_STA_DATA;
    else if(cmd == "!PRINTLINE") result.cmd = COMMAND::PRINT_LINE;
    else if(cmd == "!PRINTR2") result.cmd = COMMAND::PRINT_R2;
    else if(cmd == "!PRINTRSS") result.cmd = COMMAND::PRINT_RSS;
    else if(cmd == "!PRINTRMSE") result.cmd = COMMAND::PRINT_RMSE;
    else if(cmd == "!WRITEIN") result.cmd = COMMAND::WRITEIN;
    else if(cmd == "!WRITEOUT") result.cmd = COMMAND::WRITEOUT;
    else if(cmd == "!REMOVE") result.cmd = COMMAND::REMOVE;
    else if(cmd == "!HISTORY") result.cmd = COMMAND::HISTORY;
    else if(IsNumber(seperated.first) && IsNumber(seperated.second) && !seperated.second.empty()){
        result.cmd = COMMAND::TWO_NUMBER;
        result.args.push_back(seperated.first);
        result.args.push_back(seperated.second);
    }
    else if(IsNumber(seperated.first) && seperated.second.empty()){
        result.cmd = COMMAND::ONE_NUMBER;
        result.args.push_back(seperated.first);
        result.args.push_back(seperated.second);
    }
    else {
        result.cmd = COMMAND::UNDEFINED;
    }
    return result;
}

void PrintHelp(bool isFirstTime){
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
    if(!isFirstTime) std::cout << CYAN << "======================================================================\n" << RESET;
}