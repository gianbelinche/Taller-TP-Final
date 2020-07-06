#include "../headers/MessageSent.h"

MessageSent::MessageSent(uint32_t originId, std::string& sentMsg)
    : Event(originId), msg(sentMsg) {}

MessageSent::~MessageSent() {}

std::string& MessageSent::getMsg() {
  return msg;
}
