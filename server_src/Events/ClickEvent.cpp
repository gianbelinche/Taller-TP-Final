#include "ClickEvent.h"


ClickEvent::ClickEvent(int originUser, int destinyEntity) : 
                       Event(originUser), destinyId(destinyEntity) {}

ClickEvent::~ClickEvent() {}

int ClickEvent::getOriginUserID() {
  return originUserId;
}

int ClickEvent::getDestinyEntityID() {
  return destinyId;
}
