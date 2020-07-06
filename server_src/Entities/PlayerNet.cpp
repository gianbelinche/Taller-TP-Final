#include "../headers/PlayerNet.h"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "../headers/Equations.h"
#include "../headers/GameState.h"
#include "../headers/GhostState.h"
#include "../headers/PlayerState.h"

PlayerNet::PlayerNet(int x, int y, int id, GameState& currState, int velocity,
                     int currExp, int currLevel, int currGold, Weapon* wea,
                     Armor* arm, Helmet* helm, Shield* sh, PlayerState* sta,
                     Class* cla, Race* ra, ServerEventListener& eventListener)
    : Entity(x, y, id,
             equation::playerMaxHp(
                 cla->getConstitutionFactor() * ra->getConstitution(),
                 cla->getHpFactor(), ra->getHpFactor(), currLevel),
             currLevel),
      state(sta),
      playerClass(cla),
      playerRace(ra),
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
  mana = maxMana;
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
  selectNpc(-1);
  return state->attack(*this, ent, getDamage());
}

void PlayerNet::changeState(PlayerState* new_state) { state = new_state; }

void PlayerNet::heal(int points) {
  hp = std::min(hp + points, maxHp);
  listener.lifeUpdate(id, hp, maxHp);
}

void PlayerNet::move(int x, int y) {
  selectNpc(-1);
  state->move(*this, x, y);
}

void PlayerNet::recoverMana(int mPoints) {
  mana = std::min(mana + mPoints, maxMana);
  listener.manaUpdate(id, mana, maxMana);
}

int PlayerNet::takeDamage(int dmgToTake) {
  int defense = equation::playerDefense(
      armor->getMinDef(), armor->getMaxDef(), shield->getMinDef(),
      shield->getMaxDef(), helmet->getMinDef(), helmet->getMaxDef());
  int finalDmg = std::max(0, dmgToTake - defense);
  int oldHp = hp;

  hp = std::max(0, hp - finalDmg);
  int effectiveDamage = oldHp - hp;

  if (effectiveDamage > 0) {
    listener.playerTookDamage(id, effectiveDamage);
  }
  listener.lifeUpdate(id, hp, maxHp);
  if (hp == 0) {
    changeState(&PlayerState::dead);
    listener.playerDied(id);
    std::cout << "Se murió el jugador" << std::endl;

    // Dropear los items
  }
  return oldHp - hp;  // Daño efectivo
}

void PlayerNet::update() {
  currentFrame++;
  if (currentFrame == 500) {
    state->update(*this);
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

int PlayerNet::getGold() { return gold; }

int PlayerNet::getHp() { return hp; }

int PlayerNet::getMaxHp() { return maxHp; }

int PlayerNet::getMana() { return mana; }

int PlayerNet::getMaxMana() { return maxMana; }

int PlayerNet::getExp() { return exp; }

int PlayerNet::getMaxExp() { return maxExp; }

std::vector<uint32_t> PlayerNet::getSendable() {
  std::vector<uint32_t> playerInfo = {2, (uint32_t)id};
  playerInfo.push_back(playerRace->getRaceT());
  playerInfo.push_back(x);
  playerInfo.push_back(y);
  if (hp == 0) {
    playerInfo.push_back(1);
  } else {
    playerInfo.push_back(0);
  }
  playerInfo.push_back(weapon->getItemType());
  playerInfo.push_back(armor->getItemType());
  playerInfo.push_back(shield->getItemType());
  playerInfo.push_back(helmet->getItemType());

  return playerInfo;
}

void PlayerNet::substractGold(int amount) {
  gold -= amount;
  listener.goldUpdate(id, gold);
}

void PlayerNet::addGold(int amount) {
  gold += amount;
  listener.goldUpdate(id, gold);
}

void PlayerNet::selectNpc(int id) {
  selectedNpc = id;
}

int PlayerNet::getSelectedNpc() {
  return selectedNpc;
}

int PlayerNet::getInventorySize() {
  return inventory.getSize();
}

Inventory& PlayerNet::getInventory() {
  return inventory;
}

int PlayerNet::getSelectedSlot() {
  return selectedSlot;
}

void PlayerNet::selectSlot(int slot) {
  selectedSlot = slot;
}


