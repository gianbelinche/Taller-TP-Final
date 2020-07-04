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


class ServerEventListener {
 private:
  MessageDispatcher& dispatcher;

 public:
  ServerEventListener(MessageDispatcher& msgDispatcher);

  ~ServerEventListener();

  void playerExpGain(int id, int gain);

  void playerLeveledUp(int id);

  void entityMoved(int id, uint32_t direction);  // Ver  si conviene mergearlos en uno solo

  void playerDealtDamage(int id, int damage);

  void playerTookDamage(int id, int damage);

  void monsterMoved(int id);

  void playerDied(int id);

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
