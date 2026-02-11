#pragma once

#include "data.h"
#include "type.h"
#include "parser.h"
#include "file.h"
#include "history.h"

namespace COMMAND_HELPER{

    void HandleHelp(){
        PrintHelp(0);
    }

    void HandleExit(){
        std::cout << GREEN << "Exit successfully!" << RESET << std::endl;
    }

    void HandleClear(Data& data){
        data.clear();
        std::cout << GREEN << "Clear successfully" << RESET << std::endl;
        SetUpVariable(data);
    }

    void HandlePrint_AllData(Data& data){
        data.CalStatis();
        std::cout << ORANGE << "\n======================================================================\n\n" << RESET;
        data.PrintRawData();
        data.PrintStaData();
        std::cout << ORANGE << "\n======================================================================\n\n" << RESET;
    }

    void HandlePrint_RawData(Data& data){
        data.CalStatis();
        std::cout << ORANGE << "\n======================================================================\n\n" << RESET;
        data.PrintRawData();
        std::cout << ORANGE << "\n======================================================================\n\n" << RESET;
    }

    void HandlePrint_StaData(Data& data){
        data.CalStatis();
        std::cout << ORANGE << "\n======================================================================\n\n" << RESET;
        data.PrintStaData();
        std::cout << ORANGE << "\n======================================================================\n\n" << RESET;
    }

    void HandlePrint_Line(Data& data){
        data.CalStatis();
        data.PrintLine();
    }

    void HandlePrint_R2(Data& data){
        data.CalStatis();
        data.PrintR2();
    }

    void HandlePrint_RSS(Data& data){
        data.CalStatis();
        data.PrintRSS();
    }

    void HandlePrint_RMSE(Data& data){
        data.CalStatis();
        data.PrintRMSE();
    }

    void HandleAdd_OneNumber(Data& data, std::string& record, const CommandResult& cmdResult){
        std::pair<std::string, std::string> seperated = {cmdResult.args[0], cmdResult.args[1]};
        if(data.GetNumOfVar() != 1) throw std::invalid_argument("Number of variable mismatch");
        data.AddData(seperated, cmdResult.cmd);
        record += " : ";
        record += cmdResult.args[0];
        std::cout << GREEN << "Adding " << CYAN << std::stod(seperated.first) << GREEN << " into data successfully"  << RESET << std::endl;
    }

    void HandleAdd_TwoNumber(Data& data, std::string& record, const CommandResult& cmdResult){
        std::pair<std::string, std::string> seperated = {cmdResult.args[0], cmdResult.args[1]};
        if(data.GetNumOfVar() != 2) throw std::invalid_argument("Number of variable mismatch");
        data.AddData(seperated, cmdResult.cmd);
        record += " : ";
        record += "{";
        record += cmdResult.args[0];
        record += ", ";
        record += cmdResult.args[1];
        record += "}";
        std::cout << GREEN << "Adding {" << CYAN << std::stod(seperated.first) << GREEN << ", " << CYAN << std::stod(seperated.second) << GREEN << "} into data successfully"  << RESET << std::endl;
    }

    void HandleWriteIn(Data& data, std::string& record){
        std::string fileName;
        std::cout << "Please enter the file name(Enter !" << PURPLE << "CANCLE" << RESET << " to cancle) : ";
        std::cin >> fileName;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string temp = fileName;
        AllCaps(temp);
        RemoveSpace(temp);
        if(temp == "!CANCLE"){
            std::cout << RED << "File loading cancled\n" << RESET;
            return;
        }
        WriteIn(fileName, data, false);
        record += " : ";
        record += fileName;
        std::cout  << GREEN << "File loaded successfully\n" << RESET;
    }

    void HandleWriteOut(Data& data, std::string& record){
        std::string fileName;
        std::cout << "Please enter the file name : ";
        std::cin >> fileName;
        data.CalStatis();
        WriteOut(fileName, data);
        record += " : ";
        record += fileName;
        std::cout  << GREEN << "File save successfully\n" << RESET;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void HandleRemove(Data& data, std::string& record){
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
                record += " : ";
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
    }

    void HandleHistory(const History& history){
        std::cout << ORANGE << "\n======================================================================\n\n" << RESET;
        std::cout << history << std::endl;
        std::cout << ORANGE << "\n======================================================================\n\n" << RESET;

    }
}