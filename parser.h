#pragma once
#include <iostream>
#include <string>

#include "type.h"

void AllCaps(std::string& s){
    for(size_t i = 0; i < s.size(); ++i){
        if(s[i] >= 'a' && s[i] <= 'z'){
            s[i] = s[i] - 'a' + 'A';
        }
    }
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

COMMAND Parser(const std::string& inputString){
    std::string cmd = inputString;
    AllCaps(cmd);
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
    if(IsNumber(inputString)) return NUMBER;
    return UNDEFINED;

}