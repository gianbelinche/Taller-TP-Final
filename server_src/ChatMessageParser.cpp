#include "ChatMessageParser.h"
#include <string>

#define NO_COMMAND -1
enum messages{
    MEDITAR,
    RESUCITAR,
    CURAR,
    DEPOSITAR,
    RETIRAR,
    LISTAR,
    COMPRAR,
    VENDER,
    TOMAR,
    TIRAR,
    PLAYER_MSG
};

int ChatMessageParser::parse(std::vector<uint32_t> command){
    std::string str_command = "";
    for (int i = 2;i < command.size();i++){
        str_command += command[i];
    }
    if (str_command[0] == "@"){
        return PLAYER_MSG;
    } else if (str_command[0] == "/"){
        if (str_command.find("meditar") != std::string::npos){
            return MEDITAR;
        }
        if (str_command.find("resucitar") != std::string::npos){
            return RESUCITAR;
        }
        if (str_command.find("curar") != std::string::npos){
            return CURAR;
        }
        if (str_command.find("depositar") != std::string::npos){
            return DEPOSITAR;
        }
        if (str_command.find("retirar") != std::string::npos){
            return RETIRAR;
        }
        if (str_command.find("listar") != std::string::npos){
            return LISTAR;
        }
        if (str_command.find("comprar") != std::string::npos){
            return COMPRAR;
        }
        if (str_command.find("vender") != std::string::npos){
            return VENDER;
        }
        if (str_command.find("tomar") != std::string::npos){
            return TOMAR;
        }
        if (str_command.find("tirar") != std::string::npos){
            return TIRAR;
        }
        return NO_COMMAND;
    }
    return NO_COMMAND;

}