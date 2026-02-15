#pragma once

#include "execute.h"

void StartApp(Data& data){
    Output::Introduction();
    Output::Prompt("Do you want to load file? (Enter[y/n]) : ");
    while(true){
        std::string s;
        bool isCancle = false;
        std::getline(std::cin, s);
        AllCaps(s);
        RemoveSpace(s);
        try{
            if(s == "Y" || s == "YES"){
                while(true){
                    std::string fileName;
                    Output::Prompt("Please enter the file name(Enter !" + std::string(PURPLE) + "CANCLE" + std::string(RESET) + " to cancle) : ");
                    std::getline(std::cin, fileName);
                    std::string temp = fileName;
                    AllCaps(temp);
                    RemoveSpace(temp);
                    if(temp == "!CANCLE"){
                        isCancle = true;
                        break;
                    }
                    try{
                        WriteIn(fileName, data, true);
                        Output::Success(std::string("File loaded successfully") + Output::NEWLINE);
                        break;
                    }
                    catch(const std::runtime_error& e){
                        Output::Error(std::string(e.what()) + Output::NEWLINE);
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
            std::getline(std::cin, s);
            AllCaps(s);
            RemoveSpace(s);
            if(s == "Y" || s == "YES"){
                data.CalStatis();
                std::string fileName;
                Output::Prompt("Please enter the file name : ");
                std::getline(std::cin, fileName);
                try{
                    WriteOut(fileName, data);
                    Output::Success(std::string("File save successfully") + Output::NEWLINE);
                    break;
                }
                catch(const std::runtime_error& e){
                    Output::Error(std::string(e.what()) + std::string(", please retry : "));
                }
            }
            else if(s == "N" || s == "NO"){
                Output::Prompt(std::string("Bye!") + Output::NEWLINE);
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

void RunApp(Data& data, History& history){
    std::string input;
    while(true){
        Output::Input();
        std::getline(std::cin, input);

        CommandResult result = Parser(input);
        Execute(result, data, history);
        
        if(result.cmd == COMMAND::EXIT) break;
    }
}
