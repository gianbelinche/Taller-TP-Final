#include "ServerEventHandler.h"

#include <iostream>

#include "Entities/PlayerNet.h"

ServerEventHandler::ServerEventHandler(GameState& state) : world(state) {}

ServerEventHandler::~ServerEventHandler() {}

void ServerEventHandler::handle(UserMoved& ev) {
  PlayerNet* player = world.getPlayer(ev.getUser());
  if (player == nullptr) {  // Caso medio raro
    std::cerr << "Jugador no encontrado: " << ev.getUser() << std::endl;
    return;
  }

  char direction = ev.getDirection();
  int velocity = player->getVelocity();
  int x = player->getX();
  int y = player->getY();

  switch (direction) {
  case 'w':
    y -= velocity;
    break;
  case 'a':
    x -= velocity;
    break;
  case 's':
    y += velocity;
    break;
  case 'd':
    x += velocity;
    break;
  default:
    break;
  }
  
  if (!world.isValidPosition(x, y)) {
    return;
  }
  player->move(x, y);
  world.playerMoved(ev.getUser(), direction);
}

void ServerEventHandler::handleUserAttack(ClickEvent& ev) {
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
  if (!world.playerCanAttack(player, entity)) {
    std::cout << "No lo dejo atacar\n";
    return;
  }

  int damageDealt = player->attack(entity);
  world.playerDealtDamage(player->getId(), damageDealt);

  int expGain = entity->getHitExp(player->getLevel(), damageDealt);
  if (!entity->isAlive()) {
    expGain += entity->getDeathExp(player->getLevel());
  }
  std::cout << "La experiencia ganada es de: " << expGain << "\n";
  player->receiveExp(expGain);  
}
