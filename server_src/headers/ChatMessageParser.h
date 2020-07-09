#ifndef CLASS_CHAT_MESSAGE_PARSER
#define CLASS_CHAT_MESSAGE_PARSER

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

enum messages {
  NO_COMMAND=-1,
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
  PLAYER_MSG,
  EQUIPAR,
  ORO,
  NO_ORO
};

namespace ChatMessageParser {
int parse(std::string& str_command);

std::pair<std::string, std::string> getUserAndMessage(std::string& str_command);

std::vector<std::string> parseTokens(std::string& message);

std::string makeMsgFromTokens(std::vector<std::string> tokens);

bool isANumber(std::string s);

int parseGold(std::string& str_command);
} // namespace ChatMessageParser



#endif
