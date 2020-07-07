#include "../headers/ChatMessageParser.h"

#include <sstream>
#include <iostream>

int ChatMessageParser::parse(std::string& str_command) {
  if (str_command.length() == 0){
    return NO_COMMAND;
  }
  if (str_command[0] == '@') {
    return PLAYER_MSG;
  } else if (str_command[0] == '/') {
    /*
    if (str_command.find("meditar") != std::string::npos) {
      return MEDITAR;
    }
    if (str_command.find("resucitar") != std::string::npos) {
      return RESUCITAR;
    }
    if (str_command.find("curar") != std::string::npos) {
      return CURAR;
    }
    if (str_command.find("depositar") != std::string::npos) {
      return DEPOSITAR;
    }
    if (str_command.find("retirar") != std::string::npos) {
      return RETIRAR;
    }
    if (str_command.find("listar") != std::string::npos) {
      return LISTAR;
    }
    if (str_command.find("comprar") != std::string::npos) {
      return COMPRAR;
    }
    if (str_command.find("vender") != std::string::npos) {
      return VENDER;
    }
    if (str_command.find("tomar") != std::string::npos) {
      return TOMAR;
    }
    if (str_command.find("tirar") != std::string::npos) {
      return TIRAR;
    }*/
    if (str_command.substr(1) == "meditar"){
      return MEDITAR;
    }
    if (str_command.substr(1) == "resucitar") {
      return RESUCITAR;
    }
    if (str_command.substr(1) == "curar") {
      return CURAR;
    }
    if (str_command.substr(1) == "equipar") {
      return EQUIPAR;
    }
    if (str_command.substr(1,str_command.find(" ") - 1) == "depositar") {
      return DEPOSITAR;
    }
    if (str_command.substr(1,str_command.find(" ") - 1) == "retirar") {
      return RETIRAR;
    }
    if (str_command.substr(1) == "listar") {
      return LISTAR;
    }
    if (str_command.substr(1,str_command.find(" ") - 1) == "comprar") {
      return COMPRAR;
    }
    if (str_command.substr(1,str_command.find(" ") - 1) =="vender") {
      return VENDER;
    }
    if (str_command.substr(1) == "tomar") {
      return TOMAR;
    }
    if (str_command.substr(1) == "tirar") {
      return TIRAR;
    }  
    return NO_COMMAND;
  }
  return NO_COMMAND;
}

std::pair<std::string, std::string> ChatMessageParser::getUserAndMessage(
    std::string& str_command) {
  std::string user = str_command.substr(0, str_command.find(" "));
  std::string message = str_command.substr(str_command.find(" ") + 1);
  std::pair<std::string, std::string> data(user, message);
  return data;
}

std::vector<std::string> ChatMessageParser::parseTokens(std::string& message) {
  std::vector<std::string> tokens;
  std::stringstream ss(message);
  std::string temp;
  while (ss >> temp) {
    tokens.push_back(temp);
  }
  return tokens;
}

std::string ChatMessageParser::makeMsgFromTokens(std::vector<std::string> tokens) {
  std::string joinedStr;
  for (auto &elem: tokens) {
    joinedStr.append(elem + " ");
  }
  return joinedStr;
}

bool ChatMessageParser::isANumber(std::string s) {
  return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}
