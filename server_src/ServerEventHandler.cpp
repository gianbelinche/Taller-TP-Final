#include <iostream>

#include "PlayerNet.h"
#include "ServerEventHandler.h"

ServerEventHandler::ServerEventHandler(GameState &state) : world(state) {}

ServerEventHandler::~ServerEventHandler() {}


void ServerEventHandler::handle(UserMoved ev) {
  PlayerNet* player = world.getPlayer(ev.getUser());
  if (player == nullptr) { // Caso medio raro
    std::cerr << "Jugador no encontrado: " << ev.getUser() << std::endl;
    return;
  }
  if (!world.isValidPosition(ev.getX(), ev.getY())) {
    return;
  }
  player->move(ev.getX(), ev.getY());
  world.playerMoved(ev.getUser());
}