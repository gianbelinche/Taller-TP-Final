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
#define NPC_ATTACK 11
#define POTION_TAKEN 12

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
#define INV_EQUIP_ITEM 2

#define REVIVED 0
#define DEAD 1

class ServerEventListener {
 private:
  MessageDispatcher& dispatcher;

 public:
  ServerEventListener(MessageDispatcher& msgDispatcher);

  ~ServerEventListener();

  void playerConnected(int id);

  void entitySpawn(std::vector<uint32_t>& entInfo);

  void monsterMoved(int id); //No estoy seguro de que es esto

  void entityMoved(int id, uint32_t direction);  // Ver  si conviene mergearlos en uno solo 

  void npcSpawn(int npc_id,int npc_type,int posx,int posy);
  
  void dropSpawn(int object_id,int object_type, int posx, int posy); //3

  // Jugadores que se desconectan o mobs que mueren
  void entityDisappear(int entity_id); //4

  void playerDied(int id); //5

  void playerRevived(int id); //5

  void playerEquipedItem(int id,int eq_type,int object); //6

  void playerSendMessageToChat(int id,std::string message); //7

  void playerExpGain(int id, int gain); //7

  void playerLeveledUp(int id); //7

  void playerDealtDamage(int id, int damage); //7

  void playerTookDamage(int id, int damage); //7

  void playerHealed(int id, int life); //7

  void entityEvadedAttack(int id,int entity_id); //7

  void playerEvadedAttack(int id); //7



  void inventoryAddItem(int id,int item); //8

  void inventoryRemoveItem(int id,int slot); //8

  void inventoryEquipItem(int id,int slot); //8
  

  void goldUpdate(uint32_t id, uint32_t amount); //9

  void lifeUpdate(uint32_t id, uint32_t hp, uint32_t maxHp); //9

  void manaUpdate(uint32_t id, uint32_t mana, uint32_t maxMana); //9

  void levelUpdate(uint32_t id, uint32_t level); //9

  void expUpdate(uint32_t id, uint32_t exp, uint32_t maxExp); //9

  void npcAttack(int id,int equipped_item); //11

  void potionTaken(int id); //12

  void updateUserWorldState(int id, std::vector<uint32_t> entInfo);
};

#endif // SERVEREVENTLISTENER_H
