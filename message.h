#pragma once
#include <iostream>
#include <sstream>

#include "type.h"

class Output{
public:
    static std::string Info(const std::string& s){
        std::stringstream ss;
        return ss.str();
    }

    static std::string Success(const std::string& s){
        std::stringstream ss;
        ss << GREEN << "[Success] " << RESET << s;
        return ss.str();
    }

    static std::string Error(const std::string& s){
        std::stringstream ss;
        ss << RED << "[Error] " << RESET << s;
        return ss.str();
    }

    static std::string Prompt(const std::string& s){
        std::stringstream ss;
        ss << YELLOW << "[Prompt] " << RESET << s;
        return ss.str();
    }
};