#include "../headers/ServerEventHandler.h"

#include <iostream>

#include "../headers/ChatMessageParser.h"
#include "../headers/ImmobilizedState.h"
#include "../headers/Inventory.h"
#include "../headers/Item.h"
#include "../headers/MeditationState.h"
#include "../headers/PlayerNet.h"
#include "../headers/PlayerState.h"

#define POTION 18

ServerEventHandler::ServerEventHandler(GameState& state,
                                       ServerEventListener& eventListener,
                                       Configuration& configuration)
    : world(state), listener(eventListener), config(configuration) {}

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

  bool positionIsValid = true;

  for (size_t i = 0; i < 25; i += 6) {
    for (size_t j = 0; j < 45; j += 6) {
      positionIsValid = positionIsValid && world.isValidPosition(x + i, y + j);
    }
  }

  if (positionIsValid && player->canMove()) {
    player->move(x, y);
    listener.entityMoved(ev.getUser(), direction);
  }
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
    return;
  }
  
  int damageDealt = player->attack(entity);
  if (damageDealt > 0){
    listener.playerDealtDamage(player->getId(), damageDealt);
  } else if(damageDealt < 0) { // Se esquivo el ataque
    listener.entityEvadedAttack(player->getId(), entity->getId());
  }

  int expGain = entity->getHitExp(player->getLevel(), damageDealt);
  if (!entity->isAlive()) {
    expGain += entity->getDeathExp(player->getLevel());
  }
  player->receiveExp(expGain);
}

void ServerEventHandler::handle(EntityClick& ev) {
  int id = ev.getUser();
  int destinyId = ev.getDestinyEntityID();

  PlayerNet* player = world.getPlayer(id);
  if (player == nullptr) {
    std::cerr << "Jugador no encontrado: " << id << std::endl;
    return;
  }

  if (world.isNpc(destinyId)) {
    player->selectNpc(destinyId);
  } else if (world.isEntitiy(destinyId)) {
    handleUserAttack(ev);
  } else if (world.isDroppedItem(destinyId)) {
    if (player->getSelectedItem() == destinyId) {
      handleTake(id);
    } else {
      player->selectItem(destinyId);
    }
  }
}

void ServerEventHandler::handle(InventoryClick& ev) {
  PlayerNet* player = world.getPlayer(ev.getUser());
  if (player == nullptr) {
    std::cerr << "Jugador no encontrado: " << ev.getUser() << std::endl;
    return;
  }
  if (player->getSelectedSlot() == (int)ev.getSlot()) {
    handleEquip(player->getId());
    return;
  }
  player->selectSlot(ev.getSlot());
}

void ServerEventHandler::handle(PlayerConnection& ev) {
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
  for (int i = 0; i < player->getInventory().getSize() -
                          player->getInventory().getSpaceLeft();
       i++) {
    listener.inventoryAddItem(id,
                              player->getInventory().getItem(i)->getItemType());
  }
}

void ServerEventHandler::handle(MessageSent& ev) {
  std::string& msg = ev.getMsg();
  PlayerNet* player = world.getPlayer(ev.getUser());
  if (player == nullptr) {
    std::cerr << "No se encontro el usuario\n";
    return;
  }
  int id = player->getId();

  std::vector<std::string> msgTokens = ChatMessageParser::parseTokens(msg);
  int messageCode = NO_COMMAND;
  if (msgTokens.size() > 0) {
    messageCode = ChatMessageParser::parse(msgTokens[0]);
  }

  if (messageCode == NO_COMMAND) {
    listener.playerSendMessageToChat(id,"Comando incorrecto");
    return;
  } else if (messageCode == MEDITAR) {
    handleMeditation(id);
    return;
  } else if (messageCode == PLAYER_MSG) {
    int destinyPlayerId = world.getIdByUsername(msgTokens[0].substr(1));
    std::vector<std::string> realMsg(msgTokens.cbegin() + 1, msgTokens.cend());
    std::string joinedMsg = ChatMessageParser::makeMsgFromTokens(realMsg);
    handlePlayerMsg(id, joinedMsg, destinyPlayerId);
    return;
  } else if (messageCode == TOMAR) {
    handleTake(id);
    return;
  } else if (messageCode == TIRAR) {
    handleDrop(id);
    return;
  } else if (messageCode == RESUCITAR) {
    handleResurrect(id);
    return;
  } else if (messageCode == EQUIPAR) {
    handleEquip(id);
    return;
  }

  // Si llego aca es porque es un mensaje dirigido a algun NPC
  if (!npcHandleVerification(id)) {
    return;
  }
  NPC* npc = world.getNpc(player->getSelectedNpc());

  if (messageCode == CURAR) {
    handleHeal(id, npc);
    return;
  } else if (messageCode == DEPOSITAR) {
    // if (msgTokens.size())
    
    if (msgTokens.size() < 2) {
      listener.playerSendMessageToChat(id, "Ingrese correctamente el comando");
      return;  // FALTA MANEJAR EL DEPOSITO DE ORO
    }
    if (ChatMessageParser::parseGold(msgTokens[1]) == ORO){
      if (msgTokens.size() < 3 || !ChatMessageParser::isANumber(msgTokens[2])){
        listener.playerSendMessageToChat(id,"Ingrese correctamente el comando");
        return;
      }
      handleGoldDeposit(id,std::stoi(msgTokens[2]),npc);
    } else {
      if (!ChatMessageParser::isANumber(msgTokens[1])){
        listener.playerSendMessageToChat(id,"Ingrese el numero de slot");
        return;
      }
      handleItemDeposit(id, std::stoi(msgTokens[1]), npc);
    }
    return;
  } else if (messageCode == RETIRAR) {
    if (msgTokens.size() < 2) {
      listener.playerSendMessageToChat(
          id, "Ingrese el comando correctamente");
      return;  // FALTA MANEJAR LA EXTRACCION DE ORO
    }
    if (ChatMessageParser::parseGold(msgTokens[1]) == ORO){
      if (msgTokens.size() < 3 || !ChatMessageParser::isANumber(msgTokens[2])){
        listener.playerSendMessageToChat(id,"Ingrese correctamente el comando");
        return;
      }
      handleGoldSubstraction(id,std::stoi(msgTokens[2]),npc);
    } else {
      if (!ChatMessageParser::isANumber(msgTokens[1])){
        listener.playerSendMessageToChat(
          id, "Ingrese el numero de item correctamente");
        return;
      }
      handleItemSubstraction(id, std::stoi(msgTokens[1]), npc);
    }  
    return;
  } else if (messageCode == COMPRAR) {
    if (msgTokens.size() < 2 || !ChatMessageParser::isANumber(msgTokens[1])) {
      listener.playerSendMessageToChat(
          id, "Ingrese el numero de item correctamente");
      return;
    }
    handlePurchase(id, std::stoi(msgTokens[1]), npc);
    return;
  } else if (messageCode == VENDER) {
    if (msgTokens.size() < 2 || !ChatMessageParser::isANumber(msgTokens[1])) {
      listener.playerSendMessageToChat(
          id, "Ingrese el numero de slot correctamente");
      return;
    }
    handleSell(id, npc, std::stoi(msgTokens[1]));
    return;
  } else if (messageCode == LISTAR) {
    handleListItems(id, npc);
  }
}

bool ServerEventHandler::npcHandleVerification(int playerId) {
  PlayerNet* player = world.getPlayer(playerId);
  if (player == nullptr) {
    std::cerr << "No se encontro el usuario\n";
    return false;
  }
  if (player->getSelectedNpc() < 0) {  // Nada seleccionado
    return false;
  }
  if (world.getNpc(player->getSelectedNpc()) == nullptr) {
    std::cerr << "Fatal: NPC no encontrado\n";  // Caso muy raro
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
  if (player->isAlive()) {
    listener.playerMeditating(player->getId());
    player->changeState(&PlayerState::meditating);
    listener.playerSendMessageToChat(player->getId(),"Meditando...");
  }

}

void ServerEventHandler::handleResurrect(int playerId) {
  PlayerNet* player = world.getPlayer(playerId);
  if (player->isAlive()) { return; }
  listener.playerSendMessageToChat(player->getId(),"Resucitando...");
  int selectedNPC = player->getSelectedNpc();
  if (selectedNPC == -1 ||
      world.getNpc(selectedNPC)->getNpcType() != PRIEST_TYPE) {
    NPC* closestPriest = world.getNearestPriest(player);
    float distance = world.entitiesDistance(player, closestPriest);

    float secondsToWait =
        (config.getConfigValue("resurrectWaitTimeFactor") * distance) / 1000;
    int updatesToWait = (secondsToWait * config.getFPS()) /
                       config.getConfigValue("framesBetweenUpdate");

    player->changeState(&PlayerState::immobilized);
    player->setImmobilizedTime(updatesToWait);
  } else {
    NPC* npc = world.getNpc(selectedNPC);
    npc->resurrect(player);
  }
}

void ServerEventHandler::handleHeal(int playerId, NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  npc->heal(player);
}

void ServerEventHandler::handleItemDeposit(int playerId, int slotChoice,
                                           NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);

  Inventory& inventory = player->getInventory();
  if (slotChoice < 0 || slotChoice >= inventory.getSize() - inventory.getSpaceLeft()) {
    listener.playerSendMessageToChat(player->getId(),
                                     "Ingrese un numero correcto de slot");
    return;
  }
  Item* item = inventory.getItem(slotChoice);
  if (item == nullptr) {
    return;
  }
  npc->depositItem(item, playerId);
  handleRemoveInventoryItem(playerId,slotChoice);
}

void ServerEventHandler::handleGoldDeposit(int playerId, int amount, NPC* npc) {
  npc->goldDeposit(world.getPlayer(playerId), amount);
  listener.goldUpdate(playerId,world.getPlayer(playerId)->getGold());
}

void ServerEventHandler::handleItemSubstraction(int playerId, int itemChoice,
                                                NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  Inventory& inventory = player->getInventory();

  if (inventory.isFull()) {
    listener.playerSendMessageToChat(player->getId(),
                                     "El inventario esta lleno");
    return;
  }

  Item* item = npc->substractItem(itemChoice, playerId);
  if (item == nullptr) {
    listener.playerSendMessageToChat(player->getId(),
                                     "Id de item no reconocido");
  } else {
    player->addItemToInventory(item);
  }
  
}

void ServerEventHandler::handleGoldSubstraction(int playerId, int amount,
                                                NPC* npc) {
  npc->goldExtraction(world.getPlayer(playerId), amount);
  listener.goldUpdate(playerId,world.getPlayer(playerId)->getGold());
}

void ServerEventHandler::handleListItems(int playerId, NPC* npc) {
  npc->listItems(world.getPlayer(playerId));
}

void ServerEventHandler::handlePurchase(int playerId, int itemChoice,
                                        NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  Inventory& inv = player->getInventory();
  if (inv.isFull()) {
    listener.playerSendMessageToChat(playerId, "El inventario esta lleno");
    return;
  }
  Item* item = npc->buyItem(player, itemChoice);
  if (item == nullptr) {
    return;
  }
  player->addItemToInventory(item);
}

void ServerEventHandler::handleSell(int playerId, NPC* npc, int slotChoice) {
  PlayerNet* player = world.getPlayer(playerId);
  Inventory& inventory = player->getInventory();
  if (slotChoice <= -1) {
    slotChoice = player->getSelectedSlot();
    if (slotChoice == -1) {
      listener.playerSendMessageToChat(player->getId(),
                                       "Seleccione un slot correcto");
      return;
    }
  }
  if (slotChoice >= inventory.getSize() - inventory.getSpaceLeft()) {
    listener.playerSendMessageToChat(player->getId(),
                                     "Seleccione un slot no vacio");
    return;
  }
  Item* item = inventory.getItem(slotChoice);
  int profit = npc->sellItem(item);
  player->addGold(profit);
  listener.goldUpdate(player->getId(), player->getGold());
  handleRemoveInventoryItem(playerId, slotChoice);
}

void ServerEventHandler::handleTake(int playerId) {
  PlayerNet* player = world.getPlayer(playerId);
  if (player == nullptr) {
    std::cerr << "No se encontro el usuario\n";
    return;
  }
  Inventory& inv = player->getInventory();
  if (inv.isFull()) {
    return;
  }
  Item* item = world.getCloseItem(player->getX(), player->getY());
  if (item == nullptr) {
    return;
  }
  
  int mustBeErased = item->beTaken(player);
  if (mustBeErased == 0) { // Se debe eliminar el item del mundo
    // TODO: Creo que el oro va a generar leaks, no se libera en ningun lado
    world.rmItem(item->getId());
    listener.entityDisappear(item->getId());
  }
}

void ServerEventHandler::handleDrop(int playerId, int slotChoice) {
  PlayerNet* player = world.getPlayer(playerId);
  if (player == nullptr) {
    std::cerr << "No se encontro el usuario\n";
    return;
  }
  int slot = player->getSelectedSlot();
  player->dropItem(slot, player->getX(), player->getY());
  player->removeItemFromInventory(slot);
}

void ServerEventHandler::handlePlayerMsg(int playerId, std::string msg,
                                         int otherPlayerId) {
  std::string playerUsername = world.getUsernameById(playerId);
  listener.playerSendMessageToChat(otherPlayerId, playerUsername + ": " + msg);
}

void ServerEventHandler::handleEquip(int playerId) {
  PlayerNet* player = world.getPlayer(playerId);
  if (player == nullptr) {
    std::cerr << "No se encontro el usuario\n";
    return;
  }
  int slot = player->getSelectedSlot();
  if (slot < 0) {
    return;
  }
  Inventory& inventory = player->getInventory();
  Item* item = inventory.getItem(slot);
  if (item == nullptr) { return; } // Se clickeo un slot vacio
  int itemStatus = item->beEquiped(player);
  if (itemStatus < 0) {  // El objeto se elimina del inventario
    handleRemoveInventoryItem(playerId, slot);
    return;
  }
  listener.inventoryEquipItem(player->getId(), item->getItemType());
  if (item->getEquippedPosition() != -1) {
    listener.playerEquipedItem(player->getId(), item->getEquippedPosition(),
                               item->getItemType());
  }
}

void ServerEventHandler::handleRemoveInventoryItem(int playerId, int slot) {
  PlayerNet* player = world.getPlayer(playerId);
  player->removeItemFromInventory(slot);
}
