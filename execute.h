#pragma once

#include "data.h"
#include "type.h"
#include "parser.h"

void Execute(const COMMAND& cmd, const std::string& input, Data& data){
    try{
        switch(cmd){
            case HELP:
                PrintHelp(0);
                break;
            case EXIT:
                std::cout << GREEN << "Exit successfully!" << RESET << std::endl;
                break;
            case CLEAR:
                data.clear();
                std::cout << GREEN << "Clear successfully" << RESET << std::endl;
                SetUpVariable(data);
                break;
            case PRINT_ALL_DATA:
                data.CalStatis();
                data.PrintRawData();
                data.PrintStaData();
                break;
            case PRINT_RAW_DATA:
                data.CalStatis();
                data.PrintRawData();
                break;
            case PRINT_STA_DATA:
                data.CalStatis();
                data.PrintStaData();
                break;
            case PRINT_LINE:
                data.CalStatis();
                data.PrintLine();
                break;
            case PRINT_R2:
                data.CalStatis();
                data.PrintR2();
                break;
            case PRINT_RSS:
                data.CalStatis();
                data.PrintRSS();
                break;
            case PRINT_RMSE:
                data.CalStatis();
                data.PrintRMSE();
                break;
            case ONE_NUMBER:
                if(data.GetNumOfVar() != 1) throw std::invalid_argument("Number of variable mismatch");
                data.AddData(SeperateString(input), cmd);
                std::cout << GREEN << "Adding " << CYAN << SeperateString(input).first << GREEN << " into data successfully"  << RESET << std::endl;
                break;
            case TWO_NUMBER:
                if(data.GetNumOfVar() != 2) throw std::invalid_argument("Number of variable mismatch");
                data.AddData(SeperateString(input), cmd);
                std::cout << GREEN << "Adding {" << CYAN << SeperateString(input).first << GREEN << ", " << CYAN << SeperateString(input).second << GREEN << "} into data successfully"  << RESET << std::endl;
                break;
            case UNDEFINED:
                std::cout << RED << "Invalid command, please try again!(Enter !help for help)" << RESET << std::endl;
                break;
            default:
                break;
        }
    }
    catch(const std::invalid_argument& e){
        std::cerr << RED << "Some problem happen : " << e.what() << RESET << std::endl;
    }
    catch(const std::runtime_error& e){
        std::cerr << RED << "Some problem happen : " << e.what() << RESET << std::endl;
    }
    catch(const std::logic_error& e){
        std::cerr << RED << "Some problem happen : " << e.what() << RESET << std::endl;
    }
}