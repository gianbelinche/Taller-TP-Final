#include "../headers/ChatMessageParser.h"

#include <iostream>
#include <sstream>

int ChatMessageParser::parse(std::string& str_command) {
  if (str_command.length() == 0) {
    return NO_COMMAND;
  }
  if (str_command[0] == '@') {
    return PLAYER_MSG;
  } else if (str_command[0] == '/') {
    if (str_command.substr(1) == "meditar") {
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
    if (str_command.substr(1, str_command.find(" ") - 1) == "depositar") {
      return DEPOSITAR;
    }
    if (str_command.substr(1, str_command.find(" ") - 1) == "retirar") {
      return RETIRAR;
    }
    if (str_command.substr(1) == "listar") {
      return LISTAR;
    }
    if (str_command.substr(1, str_command.find(" ") - 1) == "comprar") {
      return COMPRAR;
    }
    if (str_command.substr(1, str_command.find(" ") - 1) == "vender") {
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

std::string ChatMessageParser::makeMsgFromTokens(
    std::vector<std::string>& tokens) {
  std::string joinedStr;
  for (auto& elem : tokens) {
    joinedStr.append(elem + " ");
  }
  return joinedStr;
}

bool ChatMessageParser::isANumber(std::string& s) {
  return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
}

int ChatMessageParser::parseGold(std::string& str_command) {
  if (str_command.substr(0, str_command.find(" ")) == "oro") {
    return ORO;
  }
  return NO_ORO;
}

bool ChatMessageParser::isUserCommand(int messageCode) {
  return (messageCode == MEDITAR || messageCode == PLAYER_MSG ||
          messageCode == TOMAR || messageCode == TIRAR ||
          messageCode == RESUCITAR || messageCode == EQUIPAR);
}