#pragma once

#include "execute.h"

void StartApp(Data& data){
    init();
    std::cout << "Do you want to load file? (Enter[y/n]) \n";
    while(true){
        std::cout << ">";
        std::string s;
        bool isCancle = false;
        std::cin >> s;
        AllCaps(s);
        RemoveSpace(s);
        if(s == "Y" || s == "YES"){
            while(true){
                std::string fileName;
                std::cout << "Please enter the file name(Enter !" << PURPLE << "CANCLE" << RESET << " to cancle) : ";
                std::cin >> fileName;
                std::string temp = fileName;
                AllCaps(temp);
                RemoveSpace(temp);
                if(temp == "!CANCLE"){
                    isCancle = true;
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                try{
                    WriteIn(fileName, data, true);
                    std::cout  << GREEN << "File loaded successfully\n" << RESET;
                    break;
                }
                catch(const std::runtime_error& e){
                    std::cout << RED << "Problem happens : " << e.what() << "\n" << RESET;
                }
            }
            if(!isCancle) break;
        }
        if(s == "N" || s == "NO" || isCancle){
            SetUpVariable(data);
            break;
        }
        else{
            std::cout  << RED << ">Invalid command, please retry\n" << RESET;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void EndApp(Data& data){
    std::cout << "Do you want to save the data? (Enter [y/n]) \n";
    while(true){
        std::cout << ">";
        std::string s;
        std::cin >> s;
        AllCaps(s);
        RemoveSpace(s);
        if(s == "Y" || s == "YES"){
            data.CalStatis();
            std::string fileName;
            std::cout << "Please enter the file name : ";
            std::cin >> fileName;
            try{
                WriteOut(fileName, data);
                std::cout  << GREEN << "File save successfully\n" << RESET;
            }
            catch(const std::runtime_error& e){
                std::cout << RED << "Problem happens : " << e.what() << "\n" << RESET;
            }
            break;
        }
        else if(s == "N" || s == "NO"){
            std::cout << BLUE << "Bye!\n" << RESET;
            break;
        }
        else{
            std::cout  << RED << ">Invalid command, please retry\n" << RESET;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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