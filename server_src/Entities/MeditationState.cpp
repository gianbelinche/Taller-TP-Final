#include "../config/Equations.h"
#include "MeditationState.h"


void MeditationState::move(PlayerNet &player, int x, int y) {
  player.changeState(&PlayerState::normal);
  PlayerState::normal.move(player, x, y);
}

void MeditationState::manaRecover(PlayerNet &player) {
  int manaGain = equation::meditationRecovery(player.getMeditationFactor(), 
                                              player.getIntelligence(),
                                              player.getCurrFrame() / 
                                              player.getFPS());
  player.recoverMana(manaGain);
}
