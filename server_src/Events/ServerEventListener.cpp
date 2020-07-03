#include "../headers/ServerEventListener.h"

ServerEventListener::ServerEventListener(MessageDispatcher& msgDispatcher)
    : dispatcher(msgDispatcher) {}
  ServerEventListener::~ServerEventListener() {}

  void ServerEventListener::playerExpGain(int id, int gain) {}

  void ServerEventListener::playerLeveledUp(int id) {}

  void ServerEventListener::playerMoved(int id, uint32_t direction) {
    std::vector<uint32_t> event;
    event[0] = PLAYER_MOVEMENT;
    event[1] = id;
    event[2] = direction;
    dispatcher.broadcastMessage(event);
  }

  void ServerEventListener::playerDealtDamage(int id, int damage) {}

  void ServerEventListener::playerTookDamage(int id, int damage) {}

  void ServerEventListener::monsterMoved(int id) {}

  void ServerEventListener::playerDied(int id) {}

  void ServerEventListener::entityDisappear(int id) {}
