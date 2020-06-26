

#include "Event.h"

Event::Event(int id) : originUserId(id) {}

Event::~Event() {}

int Event::getUser() { return originUserId; }
