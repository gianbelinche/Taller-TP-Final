
#include <cstdint>
#include <unordered_map>
#include <vector>

#include "MessageDispatcher.h"

#define PLAYER_MOVEMENT 0
#define NPS_SPAWN 1
#define PLAYER_SPAWN 2
#define DROP_SPAWN 3
#define DELETE_ENTITY 4
#define PLAYER_STATE_CHANGE 5
#define EQUIP_ITEM 6
#define PRINT_MSG 7
#define INVENTORY_COMMAND 8
#define STAT_CHANGE 9
#define LOGIN 10

class ServerEventListener {
 private:
  MessageDispatcher& dispatcher;

 public:
  ServerEventListener(MessageDispatcher& msgDispatcher);

  ~ServerEventListener();

  void playerExpGain(int id, int gain);

  void playerLeveledUp(int id);

  void playerMoved(int id, uint32_t direction);  // Ver  si conviene mergearlos en uno solo

  void playerDealtDamage(int id, int damage);

  void playerTookDamage(int id, int damage);

  void monsterMoved(int id);

  void playerDied(int id);

  // Jugadores que se desconectan o mobs que mueren
  void entityDisappear(int id);
};
