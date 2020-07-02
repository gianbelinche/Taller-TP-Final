#include "ServerProtocol.h"

#include <msgpack.hpp>
#include <utility>

ServerProtocol::ServerProtocol(ServerEventHandler& eventHandl)
    : handler(eventHandl) {}

ServerProtocol::~ServerProtocol() {}

void ServerProtocol::decode(std::string packedEvent) {
  std::vector<uint32_t> event;
  msgpack::object_handle oh =
      msgpack::unpack(packedEvent.data(), packedEvent.size());
  oh.get().convert(event);

  uint32_t eventType = event[0];
  switch (eventType) {
    case PLAYER_MOVEMENT:
      playerMovement(event);
      break;
    case CLICK_ON_ENTITY:
      entityClick(event);
      break;
    case CLICK_ON_INVENTORY:
      inventoryClick(event);
      break;
    case COMMAND:
      messageSent(event);
      break;
    default:
      break;
  }
}

void ServerProtocol::playerMovement(std::vector<uint32_t> event) {
  uint32_t playerId = event[1];
  uint32_t movementType = event[2];
  UserMoved ev(playerId, movementType);
  handler.handle(ev);
}

void ServerProtocol::entityClick(std::vector<uint32_t> event) {
  uint32_t originId = event[1];
  uint32_t destinyId = event[2];
  EntityClick ev(originId, destinyId);
  handler.handle(ev);    
}

void ServerProtocol::inventoryClick(std::vector<uint32_t> event) {
  uint32_t playerId = event[1];
  uint32_t slot = event[2];   
  InventoryClick ev(playerId, slot);
  handler.handle(ev); 
}

void ServerProtocol::messageSent(std::vector<uint32_t> event) {
  uint32_t playerId = event[1];
  std::vector<char> msg;
  for (int i = 2; i < event.size(); i++) {
    msg.push_back(event[i]);
  }
  std::string text(msg.begin(), msg.end());
  MessageSent ev(playerId, text);
  handler.handle(ev);
}
