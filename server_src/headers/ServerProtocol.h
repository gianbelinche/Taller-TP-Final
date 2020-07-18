#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>

#include "Event.h"
#include "EntityClick.h"
#include "MessageSent.h"
#include "UserMoved.h"
#include "PlayerConnection.h"
#include "ServerEventHandler.h"

#define PLAYER_MOVEMENT 0
#define CLICK_ON_ENTITY 1
#define CLICK_ON_INVENTORY 2
#define COMMAND 3
#define LOGIN_O 4
#define NEW_CONNECTION 5

class ServerProtocol {
private:
  ServerEventHandler& handler;
public:
  ServerProtocol(ServerEventHandler& eventHandl);
  
  ~ServerProtocol();

  void decode(std::string& packedEvent);

  void playerMovement(std::vector<uint32_t> event);

  void entityClick(std::vector<uint32_t> event);

  void inventoryClick(std::vector<uint32_t> event);

  void messageSent(std::vector<uint32_t> event);

  void playerConnection(std::vector<uint32_t> event);
};

#endif // SERVERPROTOCOL_H
