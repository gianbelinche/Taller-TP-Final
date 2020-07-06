#include "../headers/Banker.h"

#include <string>

#include "../headers/PlayerNet.h"

Banker::Banker(int id, int x, int y, ServerEventListener& eventListener,
               Bank& bank)
    : NPC(id, x, y, eventListener), bank(bank) {}

Banker::~Banker() {}

void Banker::listItems(PlayerNet* player) {
  std::string msg = getPrettyPrint(bank.getUserItems(player->getId()));
  listener.playerSendMessageToChat(player->getId(), msg);
}

void Banker::goldDeposit(PlayerNet* player, int amount) {
  if (amount > player->getGold()) {
    listener.playerSendMessageToChat(player->getId(),
                                     "No tienes esa cantidad de oro");
    return;
  }
  player->substractGold(amount);
  bank.addGoldTo(player->getId(), amount);
}

void Banker::goldExtraction(PlayerNet* player, int amount) {
  if (amount > bank.getUserGold(player->getId())) {
    listener.playerSendMessageToChat(
        player->getId(), "No tienes suficiente oro depositado");
    return;
  }
  player->addGold(amount);
  bank.substractGoldTo(player->getId(), amount);
}