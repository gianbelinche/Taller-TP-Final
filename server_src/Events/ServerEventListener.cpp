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
