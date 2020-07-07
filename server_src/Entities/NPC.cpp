#include "../headers/NPC.h"

#include <algorithm>
#include <string>
#include <utility>

#include "../headers/MasterFactory.h"
#include "../headers/PlayerNet.h"

NPC::NPC(int id, int x, int y, ServerEventListener& eventListener,
         MasterFactory& factory)
    : Entity(x, y, id, NPCMAXHP, NPCLEVEL),
      listener(eventListener),
      factory(factory) {}

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

Item* NPC::substractItem(int choice, int id) { return nullptr; }

int NPC::sellItem(Item* item) {
  int moneyEarned = item->getSellPrice();
  delete item;  // Aca desaparece el item, se libera la memoria asociada
  return moneyEarned;
}

Item* NPC::buyItem(PlayerNet* player, int choice) {
  int itemPos = -1;
  size_t i;
  for (i = 0; i < itemsAvailable.size(); i++) {
    if (itemsAvailable[i]->getItemType() == choice) {
      itemPos = i;
      break;
    }
  }

  if (itemPos < 0) {
    listener.playerSendMessageToChat(player->getId(),
                                     "El item pedido no se ha encontrado");
    return nullptr;
  }
  if (itemsAvailable[i]->getBuyPrice() > player->getGold()) {
    listener.playerSendMessageToChat(
        player->getId(), "No se tiene el oro suficiente para comprar el item");
    return nullptr;
  }
  return factory.createItem(choice);
}

void NPC::heal(PlayerNet* player) {}

void NPC::resurrect(PlayerNet* player) {}

bool NPC::canBeAttackedBy(Entity* ent) { return false; }

int NPC::takeDamage(int dmgToTake) { return 0; }

std::vector<uint32_t> NPC::getSendable() {
  std::vector<uint32_t> npcInfo = {1};
  npcInfo.push_back(id);
  npcInfo.push_back(npcType);
  npcInfo.push_back(x);
  npcInfo.push_back(y);
  return npcInfo;
}
