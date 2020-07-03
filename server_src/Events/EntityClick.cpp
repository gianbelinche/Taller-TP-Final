#include "../headers/EntityClick.h"

EntityClick::EntityClick(int originUser, int destinyEntity)
    : Event(originUser), destinyId(destinyEntity) {}

EntityClick::~EntityClick() {}

int EntityClick::getDestinyEntityID() { return destinyId; }
