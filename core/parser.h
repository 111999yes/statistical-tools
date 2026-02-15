#pragma once
#include <iostream>
#include <string>
#include <charconv>

#include "type.h"
#include "data.h"

inline void AllCaps(std::string& s){
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
}

inline void RemoveSpace(std::string& s){
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c){return std::isspace(c); }), s.end());
}

inline void RemoveFrontSpace(std::string& s){
    size_t pos = s.find_first_not_of(" \t\n\r");
    if(pos == std::string::npos) s.clear();
    else s.erase(0, pos);
    
}

inline void RemoveFrontNonNumber(std::string& s){
    size_t pos = s.find_first_of(".0123456789");
    if(pos == std::string::npos) s.clear();
    else s.erase(0, pos);
    
}

inline bool IsNumber(const std::string& s){
    if(s.empty()) return false;
    char* endPtr = nullptr;
    std::strtod(s.c_str(), &endPtr);
    return endPtr == s.c_str() + s.size();
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
