#ifndef SERVEREVENTLISTENER_H
#define SERVEREVENTLISTENER_H

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "MessageDispatcher.h"

#define PLAYER_MOVEMENT 0
#define NPC_SPAWN 1
#define PLAYER_SPAWN 2
#define DROP_SPAWN 3
#define DELETE_ENTITY 4
#define PLAYER_STATE_CHANGE 5
#define EQUIP_ITEM 6
#define PRINT_MSG 7
#define INVENTORY_COMMAND 8
#define STAT_CHANGE 9
#define LOGIN_I 10

#define GOLD_UPDATE 0
#define LIFE_UPDATE 1
#define MANA_UPDATE 2
#define LEVEL_UPDATE 3
#define EXP_UPDATE 4

#define MSG_DAMAGE_DEALT 0
#define MSG_DAMAGE_TOOK 1
#define MSG_HEALING 2
#define MSG_ENTITY_EVASION 3
#define MSG_PLAYER_EVASION 4
#define MSG_SEND_MSG 5
#define MSG_EXP 6
#define MSG_LEVEL_UP 7

#define ADD_ITEM 0
#define REMOVE_ITEM 1
#define EQUIP_ITEM 2

class ServerEventListener {
 private:
  MessageDispatcher& dispatcher;

 public:
  ServerEventListener(MessageDispatcher& msgDispatcher);

  ~ServerEventListener();

  void playerSendMessageToChat(int id,std::string message);

  void entityMoved(int id, uint32_t direction);  // Ver  si conviene mergearlos en uno solo

  void playerExpGain(int id, int gain);

  void playerLeveledUp(int id);

  void playerDealtDamage(int id, int damage);

  void playerTookDamage(int id, int damage);

  void playerHealed(int id, int life);

  void entityEvadedAttack(int id,int entity_id);

  void playerEvadedAttack(int id);

  void monsterMoved(int id);

  void playerDied(int id);

  void inventoryAddItem(int id,int item);

  void inventoryRemoveItem(int id,int slot);

  void inventoryEquipItem(int id,int slot);

  // Jugadores que se desconectan o mobs que mueren
  void entityDisappear(int id);

  void playerConnected(int id);

  void goldUpdate(uint32_t id, uint32_t amount);

  void lifeUpdate(uint32_t id, uint32_t hp, uint32_t maxHp);

  void manaUpdate(uint32_t id, uint32_t mana, uint32_t maxMana);

  void levelUpdate(uint32_t id, uint32_t level);

  void expUpdate(uint32_t id, uint32_t exp, uint32_t maxExp);
};

#endif // SERVEREVENTLISTENER_H
