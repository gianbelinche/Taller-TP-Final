#include "IsAlive.h"

IsAlive Condition::isAlive{};

IsAlive::IsAlive() {}

IsAlive::~IsAlive() {}

bool IsAlive::evaluate(PlayerNet* player) { return player->isAlive(); }
