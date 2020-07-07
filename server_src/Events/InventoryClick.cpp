#include "../headers/InventoryClick.h"

InventoryClick::InventoryClick(uint32_t originId, uint32_t slot)
    : Event(originId), slot(slot) {}

InventoryClick::~InventoryClick() {}

uint32_t InventoryClick::getSlot() {
    return slot;
}

