#ifndef CLICKEVENT_H
#define CLICKEVENT_H

#include "Event.h"

class ClickEvent : public Event {
private:
  int destinyId;
public:
  ClickEvent(int originUser, int destinyEntity);

  ~ClickEvent();

  int getDestinyEntityID();
};

#endif // CLICKEVENT_H
