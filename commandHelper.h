#pragma once

#include "data.h"
#include "type.h"
#include "parser.h"
#include "file.h"
#include "history.h"
#include "message.h"

const std::string SEPERATELINE = "======================================================================";
inline void PrintSeperateLine(){
    std::cout << ORANGE << "\n" << SEPERATELINE << "\n\n" << RESET;
}

namespace COMMAND_HELPER{

    void HandleHelp(){
        PrintHelp(0);
    }

    void HandleExit(){
        std::cout << Output::Success("Exit successfully!") << "\n";
    }

    void HandleClear(Data& data){
        data.clear();
        std::cout << Output::Success("Clear successfully") << "\n";
        SetUpVariable(data);
    }

    void HandlePrint_AllData(Data& data){
        data.CalStatis();
        PrintSeperateLine();
        data.PrintRawData();
        data.PrintStaData();
        PrintSeperateLine();
    }

    void HandlePrint_RawData(Data& data){
        data.CalStatis();
        PrintSeperateLine();
        data.PrintRawData();
        PrintSeperateLine();
    }

    void HandlePrint_StaData(Data& data){
        data.CalStatis();
        PrintSeperateLine();
        data.PrintStaData();
        PrintSeperateLine();
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
        std::cout << Output::Success("Adding " + std::string(CYAN) + DoubleToString(std::stod(seperated.first)) + std::string(RESET) + " into data successfully") << "\n";
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
        std::cout << Output::Success("Adding {" + std::string(CYAN) + DoubleToString(std::stod(seperated.first)) + std::string(RESET) + ", " + std::string(CYAN) + DoubleToString(std::stod(seperated.second)) + std::string(RESET) + "} into data successfully") << "\n";
    }

    void HandleWriteIn(Data& data, std::string& record){
        std::string fileName;
        std::cout << Output::Prompt("Please enter the file name(Enter !" + std::string(PURPLE) + "CANCLE" + std::string(RESET) + " to cancle) : ");
        std::cin >> fileName;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string temp = fileName;
        AllCaps(temp);
        RemoveSpace(temp);
        if(temp == "!CANCLE"){
            std::cout << Output::Prompt("File loading cancled") << "\n";
            return;
        }
        WriteIn(fileName, data, false);
        record += " : ";
        record += fileName;
        std::cout << Output::Success("File \"" + fileName + "\" loaded successfully") << "\n";
    }

    void HandleWriteOut(Data& data, std::string& record){
        std::string fileName;
        std::cout << Output::Prompt("Please enter the file name : ");
        std::cin >> fileName;
        data.CalStatis();
        WriteOut(fileName, data);
        record += " : ";
        record += fileName;
        std::cout << Output::Success("File \"" + fileName + "\" save successfully") << "\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void HandleRemove(Data& data, std::string& record){
        std::string inputIndex;
        data.PrintColRwaData();
        std::cout << Output::Prompt("Please enter the index of the data you want to remove(Enter !" + std::string(PURPLE) + "CANCLE" + std::string(RESET) + " to cancle) : ");
        while(true){
            std::getline(std::cin, inputIndex);
            std::string temp = inputIndex;
            AllCaps(temp);
            RemoveSpace(temp);
            if(temp == "!CANCLE"){
                std::cout << Output::Prompt("Data Removing cancled") << "\n";
                break;
            }
            RemoveSpace(inputIndex);
            try{
                int index;
                auto[ptr, ec] = std::from_chars(inputIndex.data(), inputIndex.data() + inputIndex.size(), index);
                if(ec != std::errc() || ptr != inputIndex.data() + inputIndex.size()){
                    throw std::invalid_argument("Invalid integer");
                }
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
                std::cout << Output::Error(std::string(e.what()) + ", please retr" + "(Enter !" + std::string(PURPLE) + "CANCLE" + std::string(RESET) + " to cancle) : ");
            }
        }
    }

    void HandleHistory(const History& history){
        PrintSeperateLine();
        std::cout << history << std::endl;
        PrintSeperateLine();
    }
}