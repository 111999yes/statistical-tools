#pragma once
#include <iostream>
#include <vector>

#include "parser.h"

class History{
public:
    void AddHistory(const std::string& input, const COMMAND& cmd, const std::string& successInput){
        std::string inputCmd = GetCommandString(cmd);
        if(cmd == COMMAND::ONE_NUMBER){
            std::pair<std::string, std::string> seperated = SeperateString(input);
            inputCmd += seperated.first;
        }
        else if(cmd == COMMAND::TWO_NUMBER){
            std::pair<std::string, std::string> seperated = SeperateString(input);
            inputCmd += "{";
            inputCmd += seperated.first;
            inputCmd += ", ";
            inputCmd += seperated.second;
            inputCmd += "}";
        }
        else if(cmd == COMMAND::REMOVE){
            inputCmd += successInput;
        }
        else if(cmd == COMMAND::WRITEIN){
            inputCmd += successInput;
        }
        else if(cmd == COMMAND::WRITEOUT){
            inputCmd += successInput;
        }
        history.push_back(inputCmd);
    }

    friend std::ostream& operator<<(std::ostream& os, const History& h){
        for(size_t i = 0; i < h.history.size(); ++i){
            os << (i + 1) << ".  " << h.history[i] << ((i == h.history.size() - 1) ? "" : "\n");
        }
        return os;
    }

private:
    std::vector<std::string> history;
};