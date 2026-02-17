#pragma once

#include "data.h"
#include "type.h"
#include "parser.h"
#include "file.h"
#include "history.h"
#include "message.h"

void SetUpVariable(Data& data);

namespace COMMAND_HELPER{

    void HandleHelp(){
        Output::PrintHelp(0);
    }

    void HandleExit(){
        Output::Success(std::string("Exit successfully!") + Output::NEWLINE);
    }

    void HandleClear(Data& data){
        data.clear();
        Output::Success(std::string("Clear successfully") + Output::NEWLINE);
        SetUpVariable(data);
    }

    void HandlePrint_AllData(Data& data){
        data.CalStatis();
        Output::SeperateLine();
        Output::RawData(data);
        Output::NewLine();
        Output::NewLine();
        Output::StaData(data);
        Output::NewLine();
        Output::SeperateLine();
    }

    void HandlePrint_RawData(Data& data){
        data.CalStatis();
        Output::SeperateLine();
        Output::RawData(data);
        Output::NewLine();
        Output::SeperateLine();
    }

    void HandlePrint_StaData(Data& data){
        data.CalStatis();
        Output::SeperateLine();
        Output::StaData(data);
        Output::NewLine();
        Output::SeperateLine();
    }

    void HandlePrint_Line(Data& data){
        data.CalStatis();
        Output::Line(data);
        Output::NewLine();
    }

    void HandlePrint_R2(Data& data){
        data.CalStatis();
        Output::R2(data);
        Output::NewLine();
    }

    void HandlePrint_RSS(Data& data){
        data.CalStatis();
        Output::RSS(data);
        Output::NewLine();
    }

    void HandlePrint_RMSE(Data& data){
        data.CalStatis();
        Output::RMSE(data);
        Output::NewLine();
    }

    void HandleAdd_OneNumber(Data& data, std::string& record, const CommandResult& cmdResult){
        std::pair<std::string, std::string> seperated = {cmdResult.args[0], cmdResult.args[1]};
        if(data.GetNumOfVar() != 1) throw std::invalid_argument("Number of variable mismatch");
        data.AddData(seperated, cmdResult.cmd);
        record += " : ";
        record += cmdResult.args[0];
        Output::Success(std::string("Adding ") + std::string(CYAN) + DoubleToString(std::stod(seperated.first)) + std::string(RESET) + std::string(" into data successfully") + Output::NEWLINE);
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
        Output::Success(std::string("Adding {") + std::string(CYAN) + DoubleToString(std::stod(seperated.first)) + std::string(RESET) + std::string(", ") + std::string(CYAN) + DoubleToString(std::stod(seperated.second)) + std::string(RESET) + std::string("} into data successfully") + Output::NEWLINE);
    }

    void HandleWriteIn(Data& data, std::string& record){
        std::string fileName;
        Output::Prompt(std::string("Please enter the file name(Enter !") + std::string(PURPLE) + std::string("CANCLE") + std::string(RESET) + std::string(" to cancle) : "));
        while(true){
            try{
                Input::GetLine(fileName);
                if(IsCancle(fileName)){
                    Output::Prompt(std::string("Write in is cancled") + Output::NEWLINE);
                    record += std::string(" : ");
                    record += std::string(RED);
                    record += std::string("cancled");
                    record += std::string(RESET);
                    return;
                }
                WriteIn(fileName, data, false);
                record += " : ";
                record += fileName;
                Output::Success(std::string("File \"") + fileName + std::string("\" loaded successfully") + Output::NEWLINE);
                break;
            }
            catch(const std::runtime_error& e){
                Output::Error(std::string(e.what()) + std::string(", please retry(Enter !") + std::string(PURPLE) + std::string("CANCLE") + std::string(RESET) + std::string(" to cnacle) : "));
            }
        }
    }

    void HandleWriteOut(Data& data, std::string& record){
        std::string fileName;
        Output::Prompt(std::string("Please enter the file name : "));
        while(true){
            try{
                Input::GetLine(fileName);
                if(IsCancle(fileName)){
                    Output::Prompt(std::string("Write out is cancled") + Output::NEWLINE);
                    record += std::string(" : ");
                    record += std::string(RED);
                    record += std::string("cancled");
                    record += std::string(RESET);
                    return;
                }
                data.CalStatis();
                WriteOut(fileName, data);
                record += " : ";
                record += fileName;
                Output::Success(std::string("File \"") + fileName + std::string("\" save successfully") + Output::NEWLINE);
                break;
            }
            catch(const std::runtime_error& e){
                Output::Error(std::string(e.what()) + std::string(", please retry(Enter !") + std::string(PURPLE) + std::string("CANCLE") + std::string(RESET) + std::string(" to cnacle) : "));
            }
        }
    }

    void HandleRemove(Data& data, std::string& record){
        std::string inputIndex;
        if(data.Empty()) throw std::invalid_argument("No data to remove");
        Output::ColRawData(data);
        Output::Prompt(std::string("Please enter the index of the data you want to remove(Enter !") + std::string(PURPLE) + std::string("CANCLE") + std::string(RESET) + std::string(" to cancle) : "));
        while(true){
            Input::GetLine(inputIndex);
            if(IsCancle(inputIndex)){
                Output::Prompt(std::string("Data removing cancled") + Output::NEWLINE);
                    record += std::string(" : ");
                    record += std::string(RED);
                    record += std::string("cancled");
                    record += std::string(RESET);
                break;
            }
            RemoveSpace(inputIndex);
            try{
                int index;
                auto[ptr, ec] = std::from_chars(inputIndex.data(), inputIndex.data() + inputIndex.size(), index);
                if(ec != std::errc() || ptr != inputIndex.data() + inputIndex.size()){
                    throw std::invalid_argument("Invalid integer");
                }
                std::pair<double, double> removedData = data.GetData(index - 1);
                data.RemoveData(index - 1);
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
                record += std::to_string(index);
                record += ")";
                break;
            }
            catch(const std::invalid_argument& e){
                Output::Error(std::string(e.what()) + std::string(", please retry (Enter !") + std::string(PURPLE) + std::string("CANCLE") + std::string(RESET) + std::string(" to cancle) : "));
            }
        }
    }

    void HandleHistory(const History& history){
        Output::SeperateLine();
        Output::History(history);
        Output::NewLine();
        Output::SeperateLine();
    }
}

void SetUpVariable(Data& data){
    std::string input;
    int num;
    Output::Prompt("Please enter the number of variables : ");
    while(true){
        try{
            if(!Input::GetLine(input)){
                throw std::invalid_argument("Input stream error");
            }
            
            Trim(input);
            if(input.empty()) throw std::invalid_argument("Empty input");

            num = GetInt(input);

            data.clear();
            data.SetNumberOfVariable(num);

            Output::Success(std::string("Set up successfully") + Output::NEWLINE);
            break;
        }
        catch(const std::exception& e){
            Output::Error(std::string(e.what()) + std::string(", please retry : "));
        }
    }
}