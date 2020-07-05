#include "../headers/ServerEventListener.h"

ServerEventListener::ServerEventListener(MessageDispatcher& msgDispatcher)
    : dispatcher(msgDispatcher) {}
ServerEventListener::~ServerEventListener() {}

void ServerEventListener::playerExpGain(int id, int gain) {
  std::vector<uint32_t> event;
  event.push_back(PRINT_MSG);
  event.push_back(MSG_EXP);
  event.push_back(id);
  event.push_back(gain);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::playerLeveledUp(int id) {
  std::vector<uint32_t> event;
  event.push_back(PRINT_MSG);
  event.push_back(MSG_LEVEL_UP);
  event.push_back(id);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::entityMoved(int id, uint32_t direction) {
  std::vector<uint32_t> event;
  event.push_back(PLAYER_MOVEMENT);
  event.push_back(id);
  event.push_back(direction);
  dispatcher.broadcastMessage(event);
}

void ServerEventListener::playerDealtDamage(int id, int damage) {
  std::vector<uint32_t> event;
  event.push_back(PRINT_MSG);
  event.push_back(MSG_DAMAGE_DEALT);
  event.push_back(id);
  event.push_back(damage);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::playerTookDamage(int id, int damage) {
  std::vector<uint32_t> event;
  event.push_back(PRINT_MSG);
  event.push_back(MSG_DAMAGE_TOOK);
  event.push_back(id);
  event.push_back(damage);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::playerHealed(int id, int life){
  std::vector<uint32_t> event;
  event.push_back(PRINT_MSG);
  event.push_back(MSG_HEALING);
  event.push_back(id);
  event.push_back(life);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::entityEvadedAttack(int id,int entity_id){
  std::vector<uint32_t> event;
  event.push_back(PRINT_MSG);
  event.push_back(MSG_ENTITY_EVASION);
  event.push_back(entity_id);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::playerEvadedAttack(int id){
  std::vector<uint32_t> event;
  event.push_back(PRINT_MSG);
  event.push_back(MSG_PLAYER_EVASION);
  event.push_back(id);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::playerSendMessageToChat(int id,std::string message){
  std::vector<uint32_t> event;
  event.push_back(PRINT_MSG);
  event.push_back(MSG_SEND_MSG);
  for (int i = 0; i < message.size(); i++){
    event.push_back(message[i]);
  }
  dispatcher.sendMessage(id,event);
}


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
