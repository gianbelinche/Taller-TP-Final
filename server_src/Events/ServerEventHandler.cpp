#include "../headers/ServerEventHandler.h"

#include <iostream>

#include "../headers/PlayerNet.h"

ServerEventHandler::ServerEventHandler(GameState& state,
                                       ServerEventListener& eventListener)
    : world(state),
      listener(eventListener) {}

ServerEventHandler::~ServerEventHandler() {}

void ServerEventHandler::handle(UserMoved& ev) {
  PlayerNet* player = world.getPlayer(ev.getUser());
  if (player == nullptr) {  // Caso medio raro
    std::cerr << "Jugador no encontrado: " << ev.getUser() << std::endl;
    return;
  }

  uint32_t direction = ev.getDirection();

  if (ev.getDirection() == STOP) {
    listener.entityMoved(ev.getUser(), direction);
    return;
  }

  int velocity = player->getVelocity();
  int x = player->getX();
  int y = player->getY();

  switch (direction) {
    case UP:
      y -= velocity;
      break;
    case LEFT:
      x -= velocity;
      break;
    case DOWN:
      y += velocity;
      break;
    case RIGHT:
      x += velocity;
      break;
    default:
      break;
  }


  if (!world.isValidPosition(x, y)) {
    return;
  }
  player->move(x, y);
  listener.entityMoved(ev.getUser(), direction);
}

void ServerEventHandler::handleUserAttack(EntityClick& ev) {
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
  listener.playerDealtDamage(player->getId(), damageDealt);

  int expGain = entity->getHitExp(player->getLevel(), damageDealt);
  if (!entity->isAlive()) {
    expGain += entity->getDeathExp(player->getLevel());
  }
  std::cout << "La experiencia ganada es de: " << expGain << "\n";
  player->receiveExp(expGain);
}

void ServerEventHandler::handle(EntityClick &ev) {}

void ServerEventHandler::handle(InventoryClick &ev) {}

void ServerEventHandler::handle(MessageSent &ev) {}

void ServerEventHandler::handle(PlayerConnection &ev) {
  listener.playerConnected(ev.getUser());
  // Mandarle el estado del mundo
}

