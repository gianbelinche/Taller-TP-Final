#include "MeditationState.h"


void MeditationState::move(PlayerNet &player, int x, int y) {
  player.changeState(&PlayerState::normal);
  PlayerState::normal.move(player, x, y);
}
