#include <algorithm>

#include "PlayerNet.h"
#include "PlayerState.h"

PlayerNet::PlayerNet(int x, int y, int id, GameState &currState, int hp,
                     int mana, int velocity, int currExp, int currGold) :
                     Entity(x, y, id), hp(hp), mana(mana), world(currState),
                     velocity(velocity), exp(currExp), gold(currGold) {}

PlayerNet::~PlayerNet() {}

void PlayerNet::update() {
  currentFrame++;
  if (currentFrame == 30) {
    state->update(*this);
  }
}

void PlayerNet::move(int x, int y) {
  state->move(*this, x, y);
}
void PlayerNet::PlayerNet::changeState(PlayerState* new_state) {
  state = new_state;
}

float PlayerNet::getRaceRecovery() {
  return playerRace->getRecoveryFactor();    
}

int PlayerNet::getFPS() {
  return world.getFPS();   
}

void PlayerNet::heal(int points) {
  hp = std::min(hp + points, maxHp);
}

void PlayerNet::recoverMana(int mPoints) {
  mana = std::min(mana + mPoints, maxMana);
}

float PlayerNet::getIntelligence() {
  return playerRace->getIntelligence() * playerClass->getIntelligenceFactor();
}

float PlayerNet::getMeditationFactor() {
  return playerClass->getmeditationFactor();
}

int PlayerNet::getCurrFrame() {
  return currentFrame;
}

bool PlayerNet::isAlive() {
  return (hp > 0);
}
