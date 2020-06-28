#include "PlayerNet.h"

#include <algorithm>
#include <iostream>

#include "../GameState.h"
#include "../config/Equations.h"
#include "GhostState.h"
#include "PlayerState.h"

PlayerNet::PlayerNet(int x, int y, int id, GameState& currState, int hp,
                     int mana, int velocity, int currExp, int currGold,
                     Weapon* wea, Armor* arm, Helmet* helm, Shield* sh,
                     PlayerState* sta, Class* cla, Race* ra)
    : Entity(x, y, id,
             equation::playerMaxHp(
                 cla->getConstitutionFactor() * ra->getConstitution(),
                 cla->getHpFactor(), ra->getHpFactor(), level),
             hp, level),
      state(sta),
      playerClass(cla),
      playerRace(ra),
      mana(mana),
      velocity(velocity),
      exp(currExp),
      gold(currGold),
      world(currState),
      weapon(wea),
      armor(arm),
      helmet(helm),
      shield(sh) {}

PlayerNet::~PlayerNet() {}

int PlayerNet::PlayerNet::getAttackRange() {
  if (weapon == nullptr) {
    return -1;  // Es lo que hay por ahora
  }
  return weapon->getAttackRange();
}

int PlayerNet::PlayerNet::getDamage() {
  return equation::causedDamage(getStrength(), weapon->getMinDmg(),
                                weapon->getMaxDmg());
}

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
  return state->attack(*this, ent, getDamage());
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
  std::cout << "La defensa resulto: " << defense << std::endl;
  int finalDmg = std::max(0, dmgToTake - defense);
  int oldHp = hp;

  hp = std::max(0, hp - finalDmg);
  world.playerTookDamage(id, oldHp - hp);
  if (hp == 0) {
    changeState(&PlayerState::dead);
    world.playerDied(id);
    std::cout << "Se murió el jugador" << std::endl;

    // Dropear los items
  }
  std::cout << "Ahora tiene vida: " << hp << std::endl;
  return oldHp - hp;  // Daño efectivo
}

void PlayerNet::update() {
  currentFrame++;
  if (currentFrame == 30) {
    std::cout << "Tenia " << hp << "de vida\n";
    state->update(*this);
    std::cout << "Ahora tiene:" << hp << std::endl;
    currentFrame = 0;
  }
}

int PlayerNet::getVelocity() { return velocity; }

int PlayerNet::getHitExp(int AttackerLevel, int damage) {
  return equation::playerHitExp(AttackerLevel, level, damage);
}

int PlayerNet::getDeathExp(int attackerLevel) {
  return equation::playerDeathExp(maxHp, level, attackerLevel);
}

void PlayerNet::receiveExp(int amount) {}
