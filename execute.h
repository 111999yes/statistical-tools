#pragma once

#include "commandHelper.h"

void Execute(const CommandResult& cmdResult, Data& data, History& history){
    try{
        std::string record = GetCommandString(cmdResult.cmd);
        switch(cmdResult.cmd){
            case COMMAND::HELP:
                COMMAND_HELPER::HandleHelp();
                break;
            case COMMAND::EXIT:
                COMMAND_HELPER::HandleExit();
                break;
            case COMMAND::CLEAR:
                COMMAND_HELPER::HandleClear(data);
                break;
            case COMMAND::PRINT_ALL_DATA:
                COMMAND_HELPER::HandlePrint_AllData(data);
                break;
            case COMMAND::PRINT_RAW_DATA:
                COMMAND_HELPER::HandlePrint_RawData(data);
                break;
            case COMMAND::PRINT_STA_DATA:
                COMMAND_HELPER::HandlePrint_StaData(data);
                break;
            case COMMAND::PRINT_LINE:
                COMMAND_HELPER::HandlePrint_Line(data);
                break;
            case COMMAND::PRINT_R2:
                COMMAND_HELPER::HandlePrint_R2(data);
                break;
            case COMMAND::PRINT_RSS:
                COMMAND_HELPER::HandlePrint_RSS(data);
                break;
            case COMMAND::PRINT_RMSE:
                COMMAND_HELPER::HandlePrint_RMSE(data);
                break;
            case COMMAND::ONE_NUMBER:
                COMMAND_HELPER::HandleAdd_OneNumber(data, record, cmdResult);
                break;
            case COMMAND::TWO_NUMBER:
                COMMAND_HELPER::HandleAdd_TwoNumber(data, record, cmdResult);
                break;
            case COMMAND::WRITEIN:
                COMMAND_HELPER::HandleWriteIn(data, record);
                break;
            case COMMAND::WRITEOUT:
                COMMAND_HELPER::HandleWriteOut(data, record);
                break;
            case COMMAND::REMOVE:
                COMMAND_HELPER::HandleRemove(data, record);
                break;
            case COMMAND::HISTORY:
                COMMAND_HELPER::HandleHistory(history);
                break;
            case COMMAND::UNDEFINED:
                throw std::invalid_argument("Invalid command, please try again!(Enter !" + std::string(PURPLE) + "help" + std::string(RED) + " for help)");
                break;
            default:
                break;
        }
        history.AddHistory(record);
    }
    //TODO
    catch(const std::invalid_argument& e){
        std::cerr << RED << "Error executing (" << BLUE << GetCommandString(cmdResult.cmd) << RED << ") : " << e.what() << RESET << std::endl;
    }
    catch(const std::runtime_error& e){
        std::cerr << RED << "Error executing (" << BLUE << GetCommandString(cmdResult.cmd) << RED << ") : " << e.what() << RESET << std::endl;
    }
    catch(const std::logic_error& e){
        std::cerr << RED << "Error executing (" << BLUE << GetCommandString(cmdResult.cmd) << RED << ") : " << e.what() << RESET << std::endl;
    }
}
