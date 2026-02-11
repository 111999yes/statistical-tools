#pragma once

#include "execute.h"

void StartApp(Data& data){
    init();
    std::cout << Output::Prompt("Do you want to load file? (Enter[y/n]) : ");
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
                    std::cout << Output::Prompt("Please enter the file name(Enter !" + std::string(PURPLE) + "CANCLE" + std::string(RESET) + " to cancle) : ");
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
                        std::cout << Output::Success("File loaded successfully") << "\n";
                        break;
                    }
                    catch(const std::runtime_error& e){
                        std::cout << Output::Error(e.what()) << "\n";
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
            std::cout << Output::Error(e.what()) << ", please retry : ";
        }
    }
}

void EndApp(Data& data){
    std::cout << Output::Prompt("Do you want to save the data? (Enter [y/n]) : ");
    while(true){
        try{
            std::string s;
            std::getline(std::cin, s);
            AllCaps(s);
            RemoveSpace(s);
            if(s == "Y" || s == "YES"){
                data.CalStatis();
                std::string fileName;
                std::cout << Output::Prompt("Please enter the file name : ");
                std::getline(std::cin, fileName);
                try{
                    WriteOut(fileName, data);
                    std::cout << Output::Success("File save successfully") << "\n";
                    break;
                }
                catch(const std::runtime_error& e){
                    std::cout << Output::Error(e.what()) << ", please retry : ";
                }
            }
            else if(s == "N" || s == "NO"){
                std::cout << Output::Prompt("Bye!") << "\n";
                break;
            }
            else{
                throw std::invalid_argument("Invalid command");
            }
        }
        catch(const std::exception& e){
            std::cout << Output::Error(e.what()) << ", please retry : ";
        }
    }
}

void RunApp(Data& data, History& history){
    std::string input;
    while(true){
        std::cout << ">";
        std::getline(std::cin, input);

        CommandResult result = Parser(input);
        Execute(result, data, history);
        
        if(result.cmd == COMMAND::EXIT) break;
    }
}

void init(){
    std::cout << ORANGE << "=============================INTRODUCTION=============================\n\n" << RESET;
    PrintHelp(1);
    std::cout << ORANGE << "\n======================================================================\n" << RESET;
}