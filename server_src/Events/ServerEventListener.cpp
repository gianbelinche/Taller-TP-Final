#include "../headers/ServerEventListener.h"

ServerEventListener::ServerEventListener(MessageDispatcher& msgDispatcher)
    : dispatcher(msgDispatcher) {}
ServerEventListener::~ServerEventListener() {}

void ServerEventListener::playerExpGain(int id, int gain) {}

void ServerEventListener::playerLeveledUp(int id) {}

void ServerEventListener::entityMoved(int id, uint32_t direction) {
  std::vector<uint32_t> event;
  event.push_back(PLAYER_MOVEMENT);
  event.push_back(id);
  event.push_back(direction);
  dispatcher.broadcastMessage(event);
}

void ServerEventListener::playerDealtDamage(int id, int damage) {}

void ServerEventListener::playerTookDamage(int id, int damage) {}

void ServerEventListener::playerDied(int id) {}

void ServerEventListener::entityDisappear(int id) {}

void ServerEventListener::playerConnected(int id) {
  dispatcher.playerConnected(id);
}

void ServerEventListener::goldUpdate(uint32_t id, uint32_t amount) {
  std::vector<uint32_t> event = {STAT_CHANGE, GOLD_UPDATE, amount};
  dispatcher.sendMessage(id, event);
}

void ServerEventListener::lifeUpdate(uint32_t id, uint32_t hp, uint32_t maxHp) {
  std::vector<uint32_t> event = {STAT_CHANGE, LIFE_UPDATE, hp, maxHp};
  dispatcher.sendMessage(id, event);
}

void ServerEventListener::manaUpdate(uint32_t id, uint32_t mana,
                                     uint32_t maxMana) {
  std::vector<uint32_t> event = {STAT_CHANGE, MANA_UPDATE, mana, maxMana};
  dispatcher.sendMessage(id, event);
}

void ServerEventListener::levelUpdate(uint32_t id, uint32_t level) {
  std::vector<uint32_t> event = {STAT_CHANGE, LEVEL_UPDATE, level};
  dispatcher.sendMessage(id, event);
}

void ServerEventListener::expUpdate(uint32_t id, uint32_t exp,
                                    uint32_t maxExp) {
  std::vector<uint32_t> event = {STAT_CHANGE, EXP_UPDATE, exp, maxExp};
  dispatcher.sendMessage(id, event);
}
