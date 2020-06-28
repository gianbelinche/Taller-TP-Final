#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <unordered_map>

#include "ProtectedStrQueue.h"

class MessageDispatcher {
 private:
  std::unordered_map<int, ProtectedStrQueue> playerQueues;
 public:
  MessageDispatcher();

  ~MessageDispatcher();

  void playerExpGain(int id, int gain);

  void playerLeveledUp(int id);

  void playerMoved(int id, char direction);  // Ver  si conviene mergearlos en uno solo

  void playerDealtDamage(int id, int damage);

  void playerTookDamage(int id, int damage);

  void monsterMoved(int id);

  void playerDied(int id);

  // Jugadores que se desconectan o mobs que mueren
  void entityDisappear(int id);
};

#endif // MESSAGEDISPATCHER_H
