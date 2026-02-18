#pragma once
#include <iostream>
#include <vector>

#include "parser.h"

class History{
public:
    void AddHistory(const std::string& record){
        history.push_back(record);
    }

    bool Empty() const {
        return history.empty();
    }

    friend std::ostream& operator<<(std::ostream& os, const History& h){
        os << YELLOW << "History :" << RESET << "\n";
        if(h.Empty()){
            os << RED << "\n    No command yet" << RESET;
        }
        else{
            for(size_t i = 0; i < h.history.size(); ++i){
                os  << "    " << (i + 1) << ".  " << h.history[i] << ((i == h.history.size() - 1) ? "" : "\n");
            }
        }
        return os;
    }

private:
    std::vector<std::string> history;
};