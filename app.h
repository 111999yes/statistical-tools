#pragma once

#include "execute.h"

void StartApp(Data& data){
    Output::Introduction();
    Output::Prompt("Do you want to load file? (Enter[y/n]) : ");
    while(true){
        std::string s;
        bool isCancle = false;
        Input::GetLine(s);
        AllCaps(s);
        RemoveSpace(s);
        try{
            if(s == "Y" || s == "YES"){
                std::string fileName;
                Output::Prompt("Please enter the file name(Enter !" + std::string(PURPLE) + "CANCLE" + std::string(RESET) + " to cancle) : ");
                while(true){
                    Input::GetLine(fileName);
                    if(IsCancle(fileName)){
                        isCancle = true;
                        break;
                    }
                    try{
                        WriteIn(fileName, data, true);
                        Output::Success(std::string("File loaded successfully") + Output::NEWLINE);
                        break;
                    }
                    catch(const std::runtime_error& e){
                        Output::Error(std::string(e.what()) + std::string(", please retry(Enter !") + std::string(PURPLE) + std::string("CANCLE") + std::string(RESET) + std::string(" to cnacle) : "));
                    }
                }
                if(!isCancle) break;
            }
            if(s == "N" || s == "NO" || isCancle){
                SetUpVariable(data);
                break;
            }
            else{
                throw std::invalid_argument("Invalid command");
            }
        }
        catch(const std::exception& e){
            Output::Error(std::string(e.what()) + std::string(", please retry : "));
        }
    }
}

void EndApp(Data& data){
    Output::Prompt("Do you want to save the data? (Enter [y/n]) : ");
    while(true){
        try{
            std::string s;
            Input::GetLine(s);
            AllCaps(s);
            RemoveSpace(s);
            if(s == "Y" || s == "YES"){
                data.CalStatis();
                Output::Prompt("Please enter the file name(Enter !" + std::string(PURPLE) + "CANCLE" + std::string(RESET) + " to cancle) : ");
                std::string fileName;
                while(true){
                    try{
                        Input::GetLine(fileName);
                        if(IsCancle(fileName)){
                            Output::Prompt(std::string("Write out is cancled") + Output::NEWLINE);
                            break;
                        }
                        WriteOut(fileName, data);
                        Output::Success(std::string("File save successfully") + Output::NEWLINE);
                        Output::Prompt(std::string("Bye!") + Output::NEWLINE);
                        break;
                    }
                    catch(const std::runtime_error& e){
                        Output::Error(std::string(e.what()) + std::string(", please retry : "));
                    }
                }
            }
            else if(s == "N" || s == "NO"){
                Output::Prompt(std::string("Bye!") + Output::NEWLINE);
            }
            else{
                throw std::invalid_argument("Invalid command");
            }
            break;
        }
        catch(const std::exception& e){
            Output::Error(std::string(e.what()) + std::string(", please retry : "));
        }
    }
}

void RunApp(Data& data, History& history){
    std::string input;
    while(true){
        Output::Input();
        Input::GetLine(input);
        CommandResult result = Parser(input);
        Execute(result, data, history);
        
        if(result.cmd == COMMAND::EXIT) break;
    }
}
