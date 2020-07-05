#ifndef CLASS_CHAT_MESSAGE_PARSER
#define CLASS_CHAT_MESSAGE_PARSER

#include <vector>

class ChatMessageParser{
public:
    int parse(std::vector<uint32_t> command);
};

#endif
