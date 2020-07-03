#include "Event.h"

#include <cstdint>

class InventoryClick : public Event {
private:
  uint32_t slot;
public:
  InventoryClick(uint32_t originId, uint32_t slot);

  ~InventoryClick();
};
