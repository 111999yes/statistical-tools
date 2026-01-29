#pragma once
#include <fstream>
#include <sstream>
#include <limits>


#include "data.h"
#include "parser.h"

bool CheckOverWrite();

void WriteOut(const std::string& fileName, const Data& data){
    std::ofstream StaFile;
    StaFile.open(fileName, std::ios::app);
    if(StaFile.fail()){
        throw std::runtime_error("Can not open file");
    }
    StaFile << data.WriteOutRawData().str();
    
    StaFile << "\n===================================\n\n";

    StaFile << data.WriteOutStaData().str();
    StaFile.close();
}

void WriteIn(const std::string& fileName, Data& data, bool isStart){
    std::ifstream oriDataFile;
    oriDataFile.open(fileName, std::ios::in);
    if(oriDataFile.fail()){
        throw std::runtime_error("Can not open file");
    }

    int numOfVar;
    if(!(oriDataFile >> numOfVar) || (numOfVar != 1 && numOfVar != 2)){
        throw std::runtime_error("Invalid file format");
    }

    bool isOverwrite = isStart ? true:CheckOverWrite();
    

    if(isOverwrite){
        data.clear();
        data.SetNumberOfVariable(numOfVar);
    }
    else{
        if(data.GetNumOfVar() != numOfVar)
            throw std::runtime_error("Number of variable mismatch");
    }

    oriDataFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string input;
    int line = 2;
    while(std::getline(oriDataFile, input)){
        if(input.empty()) continue;
        std::pair<std::string, std::string> seperated = SeperateString(input);
        try{
            if(data.GetNumOfVar() == 1){
                data.AddData(seperated, ONE_NUMBER);
            }
            else if(data.GetNumOfVar() == 2){
                data.AddData(seperated, TWO_NUMBER);
            }
        }
        catch(const std::invalid_argument& e){
            std::cout << "Wrong input at line " << line << "\n "<< "Problem : " << e.what() << "\n";
        }
        line++;
    }
    
}

void StartApp(Data& data){
    init();
    std::cout << "Do you want to use file input? (Enter[y/n]) \n";
    while(true){
        std::cout << ">";
        std::string s;
        std::cin >> s;
        AllCaps(s);
        RemoveSpace(s);
        if(s == "Y" || s == "YES"){
            std::string fileName;
            std::cout << "Please enter the file name : ";
            std::cin >> fileName;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            WriteIn(fileName, data, true);
            std::cout  << GREEN << "File write in successfully\n" << RESET;
            break;
        }
        else if(s == "N" || s == "NO"){
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
            WriteOut(fileName, data);
            std::cout  << GREEN << "File save successfully\n" << RESET;
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

bool CheckOverWrite(){
    std::cout << "Do you want ot overwrite current data? (Enter[y/n])\n";
    std::string s;
    while(true){
        getline(std::cin, s);
        AllCaps(s);
        RemoveSpace(s);
        if(s == "Y" || s == "YES"){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        }
        else if(s == "N" || s == "NO"){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        else{
            std::cout  << RED << ">Invalid command, please retry\n" << RESET;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
}

std::stringstream Data::WriteOutRawData() const {
    stringstream ss;
    if(numberOfVariable == 2){
        ss << "Raw Data :\n";
        if(oriDataX.size() != oriDataY.size()) throw std::invalid_argument("Vector size mismatch");
        for(size_t i = 0; i < oriDataX.size(); ++i) ss << "    " << (i + 1) <<". {" << oriDataX[i] << ", " << oriDataY[i] << "}\n";
    }
    else if(numberOfVariable == 1){
        ss << "Raw Data :\n";
        for(size_t i = 0; i < oriDataX.size(); ++i) ss << "    " << (i + 1) << ". " << oriDataX[i] << "\n";
    }
    else throw std::logic_error("numberOfVariable not set");
    return ss;
}

std::stringstream Data::WriteOutStaData() const {
    stringstream ss;
    if(numberOfVariable == 1){
        ss << "Statistics Data:\n";
        ss << "    Minimum : " << statis.minimum[0] << "\n";
        ss << "    Maximum : " << statis.maximum[0] << "\n";
        ss << "    Range : " << statis.range[0] << "\n";
        ss << "    Median : " << statis.median[0] << "\n";
        ss << "    Average : " << statis.Avg[0] << "\n";
        ss << "    Variance : " << statis.Var[0] << "\n";
        ss << "    Standard Deviation : " << statis.SD[0];
        ss << "\n";
    }
    else{
        ss << "Statistics Data:\n";
        ss << "    Minimum : {" << statis.minimum[0] << ", " << statis.minimum[1] << "}\n";
        ss << "    Maximum : {" << statis.maximum[0] << ", " << statis.maximum[1] << "}\n";
        ss << "    Range : {" << statis.range[0] << ", " << statis.range[1]  << "}\n";
        ss << "    Median : {" << statis.median[0] << ", " << statis.median[1] << "}\n";
        ss << "    Average : {" << statis.Avg[0] << ", " << statis.Avg[1] << "}\n";
        ss << "    Variance : {" << statis.Var[0] << ", " << statis.Var[1] << "}\n";
        ss << "    Standard Deviation : {" << statis.SD[0] << ", " << statis.SD[1] << "}\n";
        ss << "    Covariance : " << statis.coVar << "\n";
        ss << "    Correlation Coefficient : " << statis.relCoef << "\n";
        ss << "    RSS : " << statis.RSS << "\n";
        ss << "    RMSE : " << statis.RMSE << "\n";
        ss << "    R^2 : " << statis.RSquare << "\n";
        ss << "    Regression Line : " << statis.reLine;
        ss << " => ";
        statis.reLine.printLine(ss, SLOPE_INTERCEPT_FORM);
        ss << "\n";
    }
    return ss;
}
