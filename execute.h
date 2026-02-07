#pragma once

#include "data.h"
#include "type.h"
#include "parser.h"
#include "file.h"

void Execute(const COMMAND& cmd, const std::string& input, Data& data){
    try{
        switch(cmd){
            case COMMAND::HELP:
                PrintHelp(0);
                break;
            case COMMAND::EXIT:
                std::cout << GREEN << "Exit successfully!" << RESET << std::endl;
                break;
            case COMMAND::CLEAR:
                data.clear();
                std::cout << GREEN << "Clear successfully" << RESET << std::endl;
                SetUpVariable(data);
                break;
            case COMMAND::PRINT_ALL_DATA:
                data.CalStatis();
                data.PrintRawData();
                data.PrintStaData();
                break;
            case COMMAND::PRINT_RAW_DATA:
                data.CalStatis();
                data.PrintRawData();
                break;
            case COMMAND::PRINT_STA_DATA:
                data.CalStatis();
                data.PrintStaData();
                break;
            case COMMAND::PRINT_LINE:
                data.CalStatis();
                data.PrintLine();
                break;
            case COMMAND::PRINT_R2:
                data.CalStatis();
                data.PrintR2();
                break;
            case COMMAND::PRINT_RSS:
                data.CalStatis();
                data.PrintRSS();
                break;
            case COMMAND::PRINT_RMSE:
                data.CalStatis();
                data.PrintRMSE();
                break;
            case COMMAND::ONE_NUMBER:
                {
                    std::pair<std::string, std::string> seperated = SeperateString(input);
                    if(data.GetNumOfVar() != 1) throw std::invalid_argument("Number of variable mismatch");
                    data.AddData(seperated, cmd);
                    std::cout << GREEN << "Adding " << CYAN << std::stoi(seperated.first) << GREEN << " into data successfully"  << RESET << std::endl;
                }
                break;
            case COMMAND::TWO_NUMBER:
                {
                    std::pair<std::string, std::string> seperated = SeperateString(input);
                    if(data.GetNumOfVar() != 2) throw std::invalid_argument("Number of variable mismatch");
                    data.AddData(seperated, cmd);
                    std::cout << GREEN << "Adding {" << CYAN << std::stoi(seperated.first) << GREEN << ", " << CYAN << std::stoi(seperated.second) << GREEN << "} into data successfully"  << RESET << std::endl;
                }
                break;
            case COMMAND::WRITEIN:
                {
                    std::string fileName;
                    std::cout << "Please enter the file name(Enter !" << PURPLE << "CANCLE" << RESET << " to cancle) : ";
                    std::cin >> fileName;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::string temp = fileName;
                    AllCaps(temp);
                    RemoveSpace(temp);
                    if(temp == "!CANCLE"){
                        std::cout << RED << "File loading cancled\n" << RESET;
                        break;
                    }
                    WriteIn(fileName, data, false);
                    std::cout  << GREEN << "File loaded successfully\n" << RESET;
                }
                break;
            case COMMAND::WRITEOUT:
                {
                    std::string fileName;
                    std::cout << "Please enter the file name : ";
                    std::cin >> fileName;
                    data.CalStatis();
                    WriteOut(fileName, data);
                    std::cout  << GREEN << "File save successfully\n" << RESET;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            case COMMAND::UNDEFINED:
                std::cout << RED << "Invalid command, please try again!(Enter !help for help)" << RESET << std::endl;
                break;
            default:
                break;
        }
    }
    catch(const std::invalid_argument& e){
        std::cerr << RED << "Some problems happen : " << e.what() << RESET << std::endl;
    }
    catch(const std::runtime_error& e){
        std::cerr << RED << "Some problems happen : " << e.what() << RESET << std::endl;
    }
    catch(const std::logic_error& e){
        std::cerr << RED << "Some problems happen : " << e.what() << RESET << std::endl;
    }
}

