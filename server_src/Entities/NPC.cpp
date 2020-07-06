#include "../headers/NPC.h"

#include <string>
#include <utility>

#include "../headers/PlayerNet.h"

NPC::NPC(int id, int x, int y, ServerEventListener& eventListener)
    : Entity(x, y, id, NPCMAXHP, NPCLEVEL), listener(eventListener) {}

NPC::~NPC() {}

void NPC::listItems(PlayerNet* player) {
  std::string msg = std::move(getPrettyPrint(itemsAvailable));
  listener.playerSendMessageToChat(player->getId(), std::move(msg));
}

std::string NPC::getPrettyPrint(std::vector<Item*> items) {
  std::string message;
  for (auto& item : items) {
    message.append(std::to_string(item->getItemType()) + ": " +
                   item->getItemName());
    message.append("\n");
  }
  return message;
}

void NPC::goldDeposit(PlayerNet* player, int amount) {}

void NPC::goldExtraction(PlayerNet* player, int amount) {}

void NPC::depositItem(Item* item, int id) {}

