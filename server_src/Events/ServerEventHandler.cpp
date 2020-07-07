#include "../headers/ServerEventHandler.h"

#include <iostream>

#include "../headers/ChatMessageParser.h"
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
  listener.npcAttack(player->getId(),player->getEquippedItem());
}

void ServerEventHandler::handle(EntityClick &ev) {
  int id = ev.getUser();
  int destintyId = ev.getDestinyEntityID();

  PlayerNet* player = world.getPlayer(id);
  if (player == nullptr) {
    std::cerr << "Jugador no encontrado: " << id << std::endl;
    return;
  }

  if (world.isNpc(destintyId)) {
    player->selectNpc(destintyId);
  } else {
    handleUserAttack(ev);
  }
}

void ServerEventHandler::handle(InventoryClick &ev) {
  PlayerNet* player = world.getPlayer(ev.getUser());
  if (player == nullptr) {
    std::cerr << "Jugador no encontrado: " << ev.getUser() << std::endl;
    return;
  }
  player->selectSlot(ev.getSlot());
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

void ServerEventHandler::handle(MessageSent &ev) {
  std::string& msg = ev.getMsg();
  PlayerNet* player = world.getPlayer(ev.getUser());
  if (player == nullptr) {
    std::cerr << "No se encontro el usuario\n";
    return;
  }
  int id = player->getId();

  std::vector<std::string> msgTokens = ChatMessageParser::parseTokens(msg);
  int messageCode = NO_COMMAND;
  if (msgTokens.size() > 0){
    messageCode = ChatMessageParser::parse(msgTokens[0]);
  }

  if (messageCode == NO_COMMAND) {
    // O MANDAR EL MENSAJE AL CHAT GLOBAL
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
    return;
  } else if (messageCode == TIRAR) {
    return;
  } else if (messageCode == RESUCITAR) {
    handleResurrect(id);
    return;
  } else if (messageCode == EQUIPAR) {
    handleEquip(id);
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
    //if (msgTokens.size())
    if (msgTokens.size() < 2 || !ChatMessageParser::isANumber(msgTokens[1])) {
      listener.playerSendMessageToChat(id, "Ingrese el numero de slot");
      return; // FALTA MANEJAR EL DEPOSITO DE ORO
    }
    handleItemDeposit(id, std::stoi(msgTokens[1]) ,npc);
    return;
  } else if (messageCode == RETIRAR) {
    if (msgTokens.size() < 2 || !ChatMessageParser::isANumber(msgTokens[1])) {
      listener.playerSendMessageToChat(id, "Ingrese el numero de item correctamente");
      return; // FALTA MANEJAR LA EXTRACCION DE ORO
    }
    handleItemSubstraction(id, std::stoi(msgTokens[1]), npc);
    return;
  } else if (messageCode == COMPRAR) {
    if (msgTokens.size() < 2 || !ChatMessageParser::isANumber(msgTokens[1])) {
      listener.playerSendMessageToChat(id, "Ingrese el numero de item correctamente");
      return;
    }
    handlePurchase(id, std::stoi(msgTokens[1]), npc);
    return;
  } else if (messageCode == VENDER) {
    if (msgTokens.size() < 2 || !ChatMessageParser::isANumber(msgTokens[1])) {
      listener.playerSendMessageToChat(id, "Ingrese el numero de slot correctamente");
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

void ServerEventHandler::handleResurrect(int playerId) {
  PlayerNet* player = world.getPlayer(playerId);
  NPC* npc = world.getNpc(player->getSelectedNpc());
  npc->resurrect(player);
}

void ServerEventHandler::handleHeal(int playerId, NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  npc->heal(player);
}

void ServerEventHandler::handleItemDeposit(int playerId, int slotChoice, NPC* npc) {
  PlayerNet* player = world.getPlayer(playerId);
  if (slotChoice < 0 || slotChoice >= player->getInventorySize()) {
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
  } else if (inventory.isFull()) {
    listener.playerSendMessageToChat(player->getId(), "El inventario esta lleno");
    return;
  }
  listener.inventoryAddItem(playerId, item->getItemType());
}

void ServerEventHandler::handleGoldSubstraction(int playerId, int amount, NPC* npc) {
  npc->goldExtraction(world.getPlayer(playerId), amount);
}

void ServerEventHandler::handleListItems(int playerId, NPC* npc) {
  npc->listItems(world.getPlayer(playerId));
}

void ServerEventHandler::handlePurchase(int playerId, int itemChoice, NPC* npc) {
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
  player->getInventory().addItem(item);
  listener.inventoryAddItem(playerId, item->getItemType());
}

void ServerEventHandler::handleSell(int playerId, NPC* npc, int slotChoice) {
  PlayerNet* player = world.getPlayer(playerId);
  Inventory& inventory = player->getInventory();
  if (slotChoice <= -1) {
    slotChoice = player->getSelectedSlot();
    if (slotChoice == -1) {
      listener.playerSendMessageToChat(player->getId(),"Seleccione un slot correcto");
      return;
    }
  }
  if (slotChoice >= inventory.getSize() - inventory.getSpaceLeft()){
    listener.playerSendMessageToChat(player->getId(),"Seleccione un slot no vacio");
    return;
  }
  Item* item = inventory.getItem(slotChoice);
  inventory.removeItemAt(slotChoice);
  int profit = npc->sellItem(item);
  player->addGold(profit);
  listener.goldUpdate(player->getId(),player->getGold());
  listener.inventoryRemoveItem(playerId, slotChoice);
}

void ServerEventHandler::handleTake(int playerId) {}

void ServerEventHandler::handleDrop(int playerId, int slotChoice) {}

void ServerEventHandler::handlePlayerMsg(int playerId, std::string msg, int otherPlayerId) {
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
  int itemStatus = item->beEquiped(player);
  if (itemStatus < 0) { // El objeto se elimina del inventario
    listener.inventoryRemoveItem(player->getId(), slot);
    inventory.removeItemAt(slot);
    return;
  }
  listener.inventoryEquipItem(player->getId(), slot);
}

