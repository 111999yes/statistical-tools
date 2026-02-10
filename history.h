#pragma once
#include <iostream>
#include <vector>

#include "parser.h"

class History{
public:
    void AddHistory(const std::string& record){
        history.push_back(record);
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