#include "../headers/PlayerNet.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "../headers/Equations.h"
#include "../headers/GameState.h"
#include "../headers/GhostState.h"
#include "../headers/PlayerState.h"

PlayerNet::PlayerNet(int x, int y, int id, GameState& currState, int hp,
                     int mana, int velocity, int currExp, int currLevel,
                     int currGold, Weapon* wea, Armor* arm, Helmet* helm,
                     Shield* sh, PlayerState* sta, Class* cla, Race* ra,
                     ServerEventListener& eventListener)
    : Entity(x, y, id,
             equation::playerMaxHp(
                 cla->getConstitutionFactor() * ra->getConstitution(),
                 cla->getHpFactor(), ra->getHpFactor(), currLevel),
             hp, currLevel),
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
      shield(sh),
      listener(eventListener) {
  maxMana = equation::playerMaxMana(getIntelligence(), cla->getManaFactor(),
                                    ra->getManaFactor(), level);
  maxExp = equation::playerMaxExp(level);
  maxGold = equation::maxGold(level);
}

PlayerNet::~PlayerNet() {}

int PlayerNet::getAttackRange() {
  if (weapon == nullptr) {
    return -1;  // Es lo que hay por ahora
  }
  return weapon->getAttackRange();
}

int PlayerNet::getDamage() {
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
  listener.playerTookDamage(id, oldHp - hp);
  if (hp == 0) {
    changeState(&PlayerState::dead);
    listener.playerDied(id);
    std::cout << "Se murió el jugador" << std::endl;

    // Dropear los items
  }
  std::cout << "Ahora tiene vida: " << hp << std::endl;
  return oldHp - hp;  // Daño efectivo
}

void PlayerNet::update() {
  currentFrame++;
  if (currentFrame == 100) {
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

void PlayerNet::receiveExp(int amount) {
  exp += amount;
  if (exp >= maxExp) {
    levelUp();
    std::cout << "subio de nivel\n";
  } else {
    listener.playerExpGain(id, amount);
  }
  std::cout << "El jugador gano: " << amount << " de exp y ahora tiene: " << exp
            << " de experiencia\n";
}

int PlayerNet::getLevel() { return level; }

void PlayerNet::updateMaxHp() {
  maxHp = equation::playerMaxHp(getConstitution(), playerClass->getHpFactor(),
                                playerRace->getHpFactor(), level);
}

void PlayerNet::updateMaxMana() {
  maxMana =
      equation::playerMaxMana(getIntelligence(), playerClass->getManaFactor(),
                              playerRace->getManaFactor(), level);
}

int PlayerNet::getConstitution() {
  return playerClass->getConstitutionFactor() * playerRace->getConstitution();
}

void PlayerNet::updateMaxGold() { maxGold = equation::maxGold(level); }

void PlayerNet::updateMaxExp() { maxExp = equation::playerMaxExp(level); }

void PlayerNet::levelUp() {
  exp = 0;
  level++;
  updateMaxHp();
  updateMaxMana();
  updateMaxGold();
  updateMaxExp();
  hp = maxHp;
  mana = maxMana;
  listener.playerLeveledUp(id);
}

bool PlayerNet::canBeAttackedBy(Entity* ent) {
  return (abs(ent->getLevel() - level) <= 10) && (level > 12);
}
