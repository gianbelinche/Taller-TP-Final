#include <algorithm>
#include <cmath>
#include <random>
#include <iostream>

#include "../headers/Equations.h"

// Castea el resultado a int para que no moleste
int equation::pointsRecovery(float raceRecoveryFac, float seconds) {
  return raceRecoveryFac*seconds;
}

int equation::meditationRecovery(float meditationFactor, float intelligence,
                                 float seconds) {
  return meditationFactor * intelligence * seconds;
}

int equation::causedDamage(float strength, int minDmg, int maxDmg) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(minDmg, maxDmg);
  return strength * dist(gen);
}

int equation::playerDefense(int minArmorDef, int maxArmorDef, int minShieldDef,
                            int maxShieldDef, int minHelmetDef,
                            int maxHelmetDef) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<int> armorDef(minArmorDef, maxArmorDef);
  std::uniform_int_distribution<int> shieldDef(minShieldDef, maxShieldDef);
  std::uniform_int_distribution<int> helmetDef(minHelmetDef, maxHelmetDef);

  return armorDef(gen) + shieldDef(gen) + helmetDef(gen);
}

int equation::maxGold(int level) {
  return 100 * pow(level, 1.1);
}

int equation::dropGold(int maxHpNPC) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> r(0.01, 0.2);
  return r(gen) * maxHpNPC;
}

int equation::playerHitExp(int attackerLevel, int attackedLevel, int damage) {
  return damage * std::max(attackedLevel - attackerLevel + 10, 0);
}

int equation::playerDeathExp(int maxHp, int attackedLevel, int attackerLevel) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> r(0, 0.1);
  return r(gen) * maxHp * std::max(attackedLevel - attackerLevel + 10, 0);
}

int equation::monsterHitExp(int monsterLevel, int damage) {

  return damage * monsterLevel; 
}

int equation::monsterDeathExp(int monsterLevel, int maxHp) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> r(0, 0.1);
  return r(gen) * maxHp * monsterLevel; 
}

int equation::playerMaxHp(int constitution, int classHpFac, 
                          int raceHpFac, int level) {
  return constitution * classHpFac * raceHpFac * level;
}

int equation::playerMaxExp(int level) {
  return 1000 * pow(level, 1.8);    
}

int equation::playerMaxMana(int intelligence, int manaClassFac,
                            int manaRaceFac, int level) {
  return intelligence * manaClassFac * manaRaceFac * level;
}

bool equation::isCritical() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> r(0, 1);
  return r(gen) < 0.05; // 5% de proba
}

bool equation::dodgeAttack(int agility) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> r(0, 1);
  return pow(r(gen), agility) < 0.001;
}
