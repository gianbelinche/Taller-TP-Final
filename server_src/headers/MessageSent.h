#include "Event.h"

#include <cstdint>
#include <string>

class MessageSent : public Event {
private:
  std::string& msg;
public:
  MessageSent(uint32_t originId, std::string& sentMsg);

  ~MessageSent();
};
