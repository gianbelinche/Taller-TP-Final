#include "../headers/Merchant.h"

Merchant::Merchant(int id, int x, int y, ServerEventListener& eventListener)
    : NPC(id, x, y, eventListener) {}

Merchant::~Merchant() {}
