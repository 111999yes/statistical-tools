#pragma once
#include <iostream>
#include <vector>

#include "parser.h"

class History{
public:
    void AddHistory(const CommandResult& cmdResult, const std::string& successInput){
        std::string inputCmd = GetCommandString(cmdResult.cmd);
        if(cmdResult.cmd == COMMAND::ONE_NUMBER){
            inputCmd += cmdResult.args[0];
        }
        else if(cmdResult.cmd == COMMAND::TWO_NUMBER){
            inputCmd += "{";
            inputCmd += cmdResult.args[0];
            inputCmd += ", ";
            inputCmd += cmdResult.args[1];
            inputCmd += "}";
        }
        else if(cmdResult.cmd == COMMAND::REMOVE){
            inputCmd += successInput;
        }
        else if(cmdResult.cmd == COMMAND::WRITEIN){
            inputCmd += successInput;
        }
        else if(cmdResult.cmd == COMMAND::WRITEOUT){
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