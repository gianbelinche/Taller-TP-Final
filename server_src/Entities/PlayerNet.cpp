#include "PlayerNet.h"

#include <algorithm>

#include "../config/Equations.h"
#include "PlayerState.h"

PlayerNet::PlayerNet(int x, int y, int id, GameState& currState, int hp,
                     int mana, int velocity, int currExp, int currGold)
    : Entity(x, y, id, hp),
      mana(mana),
      world(currState),
      velocity(velocity),
      exp(currExp),
      gold(currGold) {}

PlayerNet::~PlayerNet() {}

int PlayerNet::getCurrFrame() { return currentFrame; }

int PlayerNet::getFPS() { return world.getFPS(); }

float PlayerNet::getIntelligence() {
  return playerRace->getIntelligence() * playerClass->getIntelligenceFactor();
}

float PlayerNet::getStrength() {
  return playerRace->getStrength() * playerClass->getStrengthFactor();
}

float PlayerNet::getMeditationFactor() {
  return playerClass->getmeditationFactor();
}

float PlayerNet::getRaceRecovery() { return playerRace->getRecoveryFactor(); }

int PlayerNet::attack(Entity* ent) {
  // Se tiene que fijar si puede atacar, si el jugador esta dentro del rango
  // Quizas hacer el chequeo de jugador vivo aca
  int playerDmg = equation::causedDamage(getStrength(), weapon->getMinDmg(),
                                         weapon->getMaxDmg());
  state->attack(*this, ent, playerDmg);
}

void PlayerNet::changeState(PlayerState* new_state) { state = new_state; }

void PlayerNet::heal(int points) { hp = std::min(hp + points, maxHp); }

void PlayerNet::move(int x, int y) { state->move(*this, x, y); }

void PlayerNet::recoverMana(int mPoints) {
  mana = std::min(mana + mPoints, maxMana);
}

int PlayerNet::takeDamage(int dmgToTake) {
  int defense = equation::playerDefense(
      armor->getMinDef(), armor->getMaxDef(), shield->getMinDef(),
      shield->getMaxDef(), helmet->getMinDef(), helmet->getMaxDef());
  int finalDmg = std::max(0, dmgToTake - defense);
  int oldHp = hp;
  hp = std::max(0, hp - finalDmg);
  // Mandar mensaje a game status sobre el daño recibido;
  if (hp == 0) {
    // jugador muerto, cambiar el estado a fantasma y mandar mensaje
  }
  return oldHp - hp;  // Daño efectivo
}

void PlayerNet::update() {
  currentFrame++;
  if (currentFrame == 30) {
    state->update(*this);
  }
}
