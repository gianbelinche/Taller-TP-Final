#include "../headers/Priest.h"
#include "../headers/PlayerState.h"
#include "../headers/ImmobilizedState.h"
#include "../headers/MasterFactory.h"

//#include "../headers/"

Priest::Priest(int id, int x, int y, ServerEventListener& eventListener,
               MasterFactory& factory)
    : NPC(id, x, y, eventListener, factory) {
  itemsAvailable = {factory.createItem(VARAFRESNO_TYPE),
                    factory.createItem(FLAUTAELFICA_TYPE),
                    factory.createItem(BACULOENGARZADO_TYPE),
                    factory.createItem(BACULONUDOSO_TYPE),
                    factory.createItem(SOMBREROMAGICO_TYPE),
                    factory.createItem(POCIONHP_TYPE),
                    factory.createItem(POCIONMANA_TYPE)};
  npcType = PRIEST_TYPE;
}

Priest::~Priest() {
  for (auto& item: itemsAvailable) {
    delete item;
  }
}

void Priest::heal(PlayerNet* player) {
  player->heal(player->getMaxHp()); // Nunca se cura mas de maxHp
  player->recoverMana(player->getMaxMana());
}

void Priest::resurrect(PlayerNet* player) {
  player->changeState(&PlayerState::immobilized);
  // COMPLETAR
}
