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
    UNDEFINED
};
