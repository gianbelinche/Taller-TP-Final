#ifndef INVENTORYCLICK_H
#define INVENTORYCLICK_H

#include "Event.h"

#include <cstdint>

class InventoryClick : public Event {
private:
  uint32_t slot;
public:
  InventoryClick(uint32_t originId, uint32_t slot);

  ~InventoryClick();

  uint32_t getSlot();
};

#endif // INVENTORYCLICK_H
