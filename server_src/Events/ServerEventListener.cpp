#include "../headers/ServerEventListener.h"

ServerEventListener::ServerEventListener(MessageDispatcher& msgDispatcher)
    : dispatcher(msgDispatcher) {}
ServerEventListener::~ServerEventListener() {}

void ServerEventListener::npcAttack(int id,int equipped_item){
  std::vector<uint32_t> event;
  event.push_back(NPC_ATTACK);
  event.push_back(equipped_item);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::potionTaken(int id){
  std::vector<uint32_t> event;
  event.push_back(POTION_TAKEN);
  dispatcher.sendMessage(id,event);
}

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

void ServerEventListener::inventoryAddItem(int id,int item){
  std::vector<uint32_t> event;
  event.push_back(INVENTORY_COMMAND);
  event.push_back(ADD_ITEM);
  event.push_back(item);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::inventoryRemoveItem(int id,int slot){
  std::vector<uint32_t> event;
  event.push_back(INVENTORY_COMMAND);
  event.push_back(REMOVE_ITEM);
  event.push_back(slot);
  dispatcher.sendMessage(id,event);
}

void ServerEventListener::inventoryEquipItem(int id,int slot){
  std::vector<uint32_t> event;
  event.push_back(INVENTORY_COMMAND);
  event.push_back(INV_EQUIP_ITEM);
  event.push_back(slot);
  dispatcher.sendMessage(id,event);
}


void ServerEventListener::playerDied(int id) {
  std::vector<uint32_t> event;
  event.push_back(PLAYER_STATE_CHANGE);
  event.push_back(DEAD);
  event.push_back(id);
  dispatcher.broadcastMessage(event);
}

void ServerEventListener::playerRevived(int id) {
  std::vector<uint32_t> event;
  event.push_back(PLAYER_STATE_CHANGE);
  event.push_back(REVIVED);
  event.push_back(id);
  dispatcher.broadcastMessage(event);
}

void ServerEventListener::playerEquipedItem(int id,int eq_type,int object){
  std::vector<uint32_t> event;
  event.push_back(EQUIP_ITEM);
  event.push_back(id);
  event.push_back(eq_type);
  event.push_back(object);
  dispatcher.broadcastMessage(event);
}

void ServerEventListener::dropSpawn(int object_id,
                                   int object_type, int posx, int posy){
  std::vector<uint32_t> event;  
  event.push_back(DROP_SPAWN);
  event.push_back(object_id);
  event.push_back(object_type);
  event.push_back(posx);
  event.push_back(posy);
  dispatcher.broadcastMessage(event);

}

void ServerEventListener::npcSpawn(int npc_id,int npc_type,int posx,int posy){
  std::vector<uint32_t> event;  
  event.push_back(NPC_SPAWN);
  event.push_back(npc_id);
  event.push_back(npc_type);
  event.push_back(posx);
  event.push_back(posy);
  dispatcher.broadcastMessage(event);
}

void ServerEventListener::entityDisappear(int id,int entity_id) {
  std::vector<uint32_t> event;
  event.push_back(DELETE_ENTITY);
  event.push_back(entity_id);
  dispatcher.broadcastMessage(event);
}

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
