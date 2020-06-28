#include "MessageDispatcher.h"

MessageDispatcher::MessageDispatcher() {}

MessageDispatcher::~MessageDispatcher() {}

void MessageDispatcher::playerExpGain(int id, int gain) {}

void MessageDispatcher::playerLeveledUp(int id) {}

void MessageDispatcher::playerMoved(int id, char direction) {}

void MessageDispatcher::playerDealtDamage(int id, int damage) {}

void MessageDispatcher::playerTookDamage(int id, int damage) {}

void MessageDispatcher::monsterMoved(int id) {}

void MessageDispatcher::playerDied(int id) {}

void MessageDispatcher::entityDisappear(int id) {}
