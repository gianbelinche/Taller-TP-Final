#include "../headers/ServerEventHandler.h"

#include <iostream>

#include "../headers/MeditationState.h"
#include "../headers/PlayerNet.h"
#include "../headers/PlayerState.h"
#include "../headers/Item.h"
#include "../headers/Inventory.h"

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

void ServerEventHandler::handle(EntityClick &ev) {
  int id = ev.getUser();
  int destintyId = ev.getDestinyEntityID();

  PlayerNet* player = world.getPlayer(ev.getUser());
  if (player == nullptr) {
    std::cerr << "Jugador no encontrado: " << ev.getUser() << std::endl;
    return;
  }

  if (world.isNpc(destintyId)) {
    player->selectNpc(destintyId);
  } else {
    handleUserAttack(ev);
  }
}

void ServerEventHandler::handle(InventoryClick &ev) {}

void ServerEventHandler::handle(MessageSent &ev) {

}

void ServerEventHandler::handle(PlayerConnection &ev) {
  uint32_t id = ev.getUser();
  PlayerNet* player = world.getPlayer(id);
  if (player == nullptr) {
    std::cerr << "No se encontro el usuario\n";
    return;
  }
  std::vector<uint32_t> playerSendable = player->getSendable();
  listener.entitySpawn(playerSendable);
  
  world.sendState(player->getId());
  listener.playerConnected(id);
  listener.goldUpdate(id, player->getGold());
  listener.lifeUpdate(id, player->getHp(), player->getMaxHp());
  listener.manaUpdate(id, player->getMana(), player->getMaxMana());
  listener.levelUpdate(id, player->getLevel());
  listener.expUpdate(id, player->getExp(), player->getMaxExp());
  // PRUEBA
  world.spawnUnParDeMobs();
}

bool ServerEventHandler::npcHandleVerification(int playerId) {
  PlayerNet* player = world.getPlayer(playerId);
  if (player == nullptr) {
    std::cerr << "No se encontro el usuario\n";
    return false;
  }
  if (player->getSelectedNpc() < 0) { // Nada seleccionado
    return false;
  }
  if (world.getNpc(player->getSelectedNpc()) == nullptr) {
    std::cerr << "Fatal: NPC no encontrado\n"; // Caso muy raro
    return false;
  }
  return true;
}


void ServerEventHandler::handleMeditation(int playerId) {
  PlayerNet* player = world.getPlayer(playerId);
  if (player == nullptr) {
    std::cerr << "No se encontro el usuario\n";
    return;
  }
  player->changeState(&PlayerState::meditating);
}

void ServerEventHandler::handleResurrect(int playerId, NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  NPC* npc = world.getNpc(player->getSelectedNpc());
  npc->resurrect(player);
}

void ServerEventHandler::handleHeal(int playerId, NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  NPC* npc = world.getNpc(player->getSelectedNpc());
  npc->heal(player);
}

void ServerEventHandler::handleItemDeposit(int playerId, int slotChoice, NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  if (slotChoice < 1 || slotChoice > player->getInventorySize()) {
    listener.playerSendMessageToChat(player->getId(), "Ingrese un numero correcto de slot");
    return;
  }
  Inventory& inventory = player->getInventory();
  Item* item = inventory.getItem(slotChoice);
  if (item == nullptr) {
    return;
  }
  npc->depositItem(item, playerId);
  inventory.removeItemAt(slotChoice);
}

void ServerEventHandler::handleGoldDeposit(int playerId, int amount, NPC* npc) {
  npc->goldDeposit(world.getPlayer(playerId), amount);
}

void ServerEventHandler::handleItemSubstraction(int playerId, int itemChoice, NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  Inventory& inventory = player->getInventory();

  if (inventory.isFull()) {
    return;
  }

  Item* item = npc->substractItem(itemChoice, playerId);
  if (item == nullptr) {
    listener.playerSendMessageToChat(player->getId(), "Id de item no reconocido");
  }
  inventory.addItem(item);
  // Logica de mandarle al server el item que se agrego y en que slot
}

void ServerEventHandler::handleGoldSubstraction(int playerId, int amount, NPC* npc) {
  npc->goldExtraction(world.getPlayer(playerId), amount);
}

void ServerEventHandler::handleListItems(int playerId, NPC* npc) {
  npc->listItems(world.getPlayer(playerId));
}

void ServerEventHandler::handlePurchase(int playerId, int itemChoice, NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  Item* item = npc->buyItem(player, itemChoice);
  if (item == nullptr) {
    return;
  }
  player->getInventory().addItem(item);
  // AVISARLE AL CLIENTE QUE HAY ALGO NUEVO EN EL INVENTARIO
}

void ServerEventHandler::handleSell(int playerId, NPC* npc, int slotChoice) {
  PlayerNet* player = world.getPlayer(playerId);
  Inventory& inventory = player->getInventory();
  if (slotChoice == -1) {
    slotChoice = player->getSelectedSlot();
  }
  Item* item = inventory.getItem(slotChoice);
  inventory.removeItemAt(slotChoice);
  int profit = npc->sellItem(item);
  player->addGold(profit);
  // AVISARLE AL CLIENTE QUE HAY ALGO MENOS EN EL INVENTARIO
}

void ServerEventHandler::handleTake(int playerId) {}

void ServerEventHandler::handleDrop(int playerId, int slotChoice=-1) {}

void ServerEventHandler::handlePlayerMsg(int playerId, int otherPlayerId=-1) {
  //listener.playerSendMessageToChat()
}

