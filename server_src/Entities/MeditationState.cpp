#include "../headers/MeditationState.h"

#include "../headers/Equations.h"
#include "../headers/ServerEventListener.h"

MeditationState PlayerState::meditating{};

MeditationState::MeditationState() {
    
}

MeditationState::~MeditationState() {
    
}

void MeditationState::move(PlayerNet &player, int x, int y) {
  player.changeState(&PlayerState::normal);
  
  PlayerState::normal.move(player, x, y);
}

void MeditationState::manaRecover(PlayerNet &player) {
  int manaGain = equation::meditationRecovery(
      player.getMeditationFactor(), player.getIntelligence(),
      player.getCurrFrame() / player.getFPS());
  player.recoverMana(manaGain);
}

int MeditationState::attack(PlayerNet &player, Entity *ent, int damage, bool canDodge) {
  player.changeState(&PlayerState::normal);
  return PlayerState::normal.attack(player, ent, damage, canDodge);
}
