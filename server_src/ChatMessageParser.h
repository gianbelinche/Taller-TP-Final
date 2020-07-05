#ifndef CLASS_CHAT_MESSAGE_PARSER
#define CLASS_CHAT_MESSAGE_PARSER

#include <vector>
#include <utility>
#include <string>
#include <cstdint>

class ChatMessageParser{
public:
    int parse(std::vector<uint32_t> command);

    std::pair<std::string,std::string> 
    getUserAndMessage(std::vector<uint32_t> command);
};

#endif
