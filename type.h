#pragma once

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
    UNDEFINED
};

std::string GetCommandString(const COMMAND& cmd){
    switch(cmd){
        case COMMAND::HELP:
            return "Help";
        case COMMAND::EXIT:
            return "Exit";
        case COMMAND::CLEAR:
            return "Clear";
        case COMMAND::PRINT_ALL_DATA:
            return "Print All Data";
        case COMMAND::PRINT_RAW_DATA:
            return "Print Raw Data";
        case COMMAND::PRINT_STA_DATA:
            return "Print Sts Data";
        case COMMAND::PRINT_LINE:
            return "Print Line";
        case COMMAND::PRINT_R2:
            return "Print R2";
        case COMMAND::PRINT_RSS:
            return "Print RSS";
        case COMMAND::PRINT_RMSE:
            return "Print RMSE";
        case COMMAND::WRITEIN:
            return "Write In";
        case COMMAND::WRITEOUT:
            return "Write Out";
        case COMMAND::ONE_NUMBER:
            return "Add a number : ";
        case COMMAND::TWO_NUMBER:
            return "Add two numbers : ";
        case COMMAND::UNDEFINED:
            return "Undefined Command";
        case COMMAND::REMOVE:
            return "Remove";
        default:
            return "Undefined";
    }
}
