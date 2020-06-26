#include <iostream>

#include "PlayerNet.h"
#include "ServerEventHandler.h"

ServerEventHandler::ServerEventHandler(GameState &state) : world(state) {}

ServerEventHandler::~ServerEventHandler() {}


void ServerEventHandler::handle(UserMoved &ev) {
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


void ServerEventHandler::handleUserAttack(ClickEvent &ev) {
  PlayerNet* player = world.getPlayer(ev.getUser());
  if (player == nullptr) {
    std::cerr << "Jugador no encontrado: " << ev.getUser() << std::endl;
    return;
  }

  Entity* entity = world.getEntity(ev.getDestinyEntityID());
  if (entity == nullptr) {
    std::cerr << "Entidad de destino no encontrada" << ev.getDestinyEntityID() 
              << std::endl;
    return;
  }
  if (!entity->isAlive()) {return;}

  int damageDealt = player->attack(entity);
  // Hay que mandar el daño causado fijandose si es mayor a cero, cero o 
  // negativo
}
