#pragma once
#include <iostream>
#include <vector>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m" 
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define PURPLE  "\033[38;5;19m"
#define ORANGE  "\033[38;5;208m"
#define PINK    "\033[38;5;218m"

enum class MODE{
    POINT_SLOPE_FORM,
    SLOPE_INTERCEPT_FORM
};

enum class COMMAND{
    HELP,
    EXIT,
    CLEAR,
    PRINT_ALL_DATA,
    PRINT_RAW_DATA,
    PRINT_STA_DATA,
    PRINT_LINE,
    PRINT_R2,
    PRINT_RSS,
    PRINT_RMSE,
    WRITEIN,
    WRITEOUT,
    ONE_NUMBER,
    TWO_NUMBER,
    REMOVE,
    HISTORY,
    UNDEFINED
};

std::string GetCommandString(const COMMAND& cmd){
    std::string result;
    switch(cmd){
        case COMMAND::HELP:
            result = std::string(GREEN) + "Help" + std::string(RESET);
            break;
        case COMMAND::EXIT:
            result = std::string(RED) + "Exit" + std::string(RESET);
            break;
        case COMMAND::CLEAR:
            result = std::string(BLUE) + "Clear" + std::string(RESET);
            break;
        case COMMAND::WRITEIN:
            result = std::string(BLUE) + "Write In File" + std::string(RESET);
            break;
        case COMMAND::WRITEOUT:
            result = std::string(BLUE) + "Write Out File" + std::string(RESET);
            break;
        case COMMAND::REMOVE:
            result = std::string(BLUE) + "Remove data" + std::string(RESET);
            break;
        case COMMAND::HISTORY:
            result = std::string(BLUE) + "Call command history" + std::string(RESET);
            break;
        case COMMAND::PRINT_ALL_DATA:
            result = std::string(MAGENTA) + "Print All Data" + std::string(RESET);
            break;
        case COMMAND::PRINT_RAW_DATA:
            result = std::string(MAGENTA) + "Print Raw Data" + std::string(RESET);
            break;
        case COMMAND::PRINT_STA_DATA:
            result = std::string(MAGENTA) + "Print Sts Data" + std::string(RESET);
            break;
        case COMMAND::PRINT_LINE:
            result = std::string(MAGENTA) + "Print Line" + std::string(RESET);
            break;
        case COMMAND::PRINT_R2:
            result = std::string(MAGENTA) + "Print R2" + std::string(RESET);
            break;
        case COMMAND::PRINT_RSS:
            result = std::string(MAGENTA) + "Print RSS" + std::string(RESET);
            break;
        case COMMAND::PRINT_RMSE:
            result = std::string(MAGENTA) + "Print RMSE" + std::string(RESET);
            break;
        case COMMAND::ONE_NUMBER:
            result = std::string(CYAN) + "Add a number" + std::string(RESET);
            break;
        case COMMAND::TWO_NUMBER:
            result = std::string(CYAN) + "Add two numbers" + std::string(RESET);
            break;
        case COMMAND::UNDEFINED:
            result = std::string(RED) + "Undefined" + std::string(RESET);
            break;
        default:
            result = std::string(RED) + "Undefined" + std::string(RESET);
            break;
    }
    return result;
}

struct CommandResult{

    COMMAND cmd;
    std::vector<std::string> args;

};
