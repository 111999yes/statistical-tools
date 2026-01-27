#pragma once

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BLUE "\033[38;5;19m"

enum MODE{
    POINT_SLOPE_FORM,
    SLOPE_INTERCEPT_FORM
};

enum COMMAND{
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
    NUMBER,
    UNDEFINED
};
