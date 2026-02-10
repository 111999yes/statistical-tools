#pragma once

#include "data.h"
#include "type.h"
#include "parser.h"
#include "file.h"
#include "history.h"

void Execute(const CommandResult& cmdResult, Data& data, History& history){
    try{
        std::string record = GetCommandString(cmdResult.cmd);
        switch(cmdResult.cmd){
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
                    std::pair<std::string, std::string> seperated = {cmdResult.args[0], cmdResult.args[1]};
                    if(data.GetNumOfVar() != 1) throw std::invalid_argument("Number of variable mismatch");
                    data.AddData(seperated, cmdResult.cmd);
                    record += cmdResult.args[0];
                    std::cout << GREEN << "Adding " << CYAN << std::stod(seperated.first) << GREEN << " into data successfully"  << RESET << std::endl;
                }
                break;
            case COMMAND::TWO_NUMBER:
                {
                    std::pair<std::string, std::string> seperated = {cmdResult.args[0], cmdResult.args[1]};
                    if(data.GetNumOfVar() != 2) throw std::invalid_argument("Number of variable mismatch");
                    data.AddData(seperated, cmdResult.cmd);
                    record += "{";
                    record += cmdResult.args[0];
                    record += ", ";
                    record += cmdResult.args[1];
                    record += "}";
                    std::cout << GREEN << "Adding {" << CYAN << std::stod(seperated.first) << GREEN << ", " << CYAN << std::stod(seperated.second) << GREEN << "} into data successfully"  << RESET << std::endl;
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
                    record += fileName;
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
                    record += fileName;
                    std::cout  << GREEN << "File save successfully\n" << RESET;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            case COMMAND::REMOVE:
                {
                    std::string inputIndex;
                    data.PrintColRwaData();
                    std::cout << "Please enter the index of the data you want to remove(Enter !" << PURPLE << "CANCLE" << RESET << " to cancle) : ";
                    while(true){
                        std::getline(std::cin, inputIndex);
                        std::string temp = inputIndex;
                        AllCaps(temp);
                        RemoveSpace(temp);
                        if(temp == "!CANCLE"){
                            std::cout << RED << "Data Removing cancled\n" << RESET;
                            break;
                        }
                        RemoveSpace(inputIndex);
                        int index;
                        auto[ptr, ec] = std::from_chars(inputIndex.data(), inputIndex.data() + inputIndex.size(), index);
                        if(ec != std::errc() || ptr != inputIndex.data() + inputIndex.size()){
                            std::cout << RED << "Invalid integer\nPlease reenter : " << RESET;
                            continue;
                        }
                        try{
                            index -= 1;
                            std::pair<double, double> removedData = data.GetData(index);
                            data.RemoveData(index);
                            if(std::isnan(removedData.second)){
                                record += DoubleToString(removedData.first);
                            }
                            else{
                                record += "{";
                                record += DoubleToString(removedData.first);
                                record += ", ";
                                record += DoubleToString(removedData.second);
                                record += "}";
                            }
                            record += " (index : ";
                            record += std::to_string(index + 1);
                            record += ")";
                            break;
                        }
                        catch(const std::invalid_argument& e){
                            std::cout  << RED << e.what() << "\nPlease reenter : " << RESET;
                        }
                    }
                    break;
                }
            case COMMAND::HISTORY:
                std::cout << history << std::endl;
                break;
            case COMMAND::UNDEFINED:
                std::cout << RED << "Invalid command, please try again!(Enter !help for help)" << RESET << std::endl;
                break;
            default:
                break;
        }
        history.AddHistory(record);
    }
    catch(const std::invalid_argument& e){
        std::cerr << RED << "Error executing " << GetCommandString(cmdResult.cmd) << " : " << e.what() << std::endl;
    }
    catch(const std::runtime_error& e){
        std::cerr << RED << "Error executing " << GetCommandString(cmdResult.cmd) << " : " << e.what() << std::endl;
    }
    catch(const std::logic_error& e){
        std::cerr << RED << "Error executing " << GetCommandString(cmdResult.cmd) << " : " << e.what() << std::endl;
    }
}

