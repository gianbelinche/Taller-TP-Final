#include "Race.h"

Race::Race(char race_t, float hpFac, float recFac, float manaFac) {}

Race::~Race() {}

float Race::getHpFactor() {
  return hpFactor;
}

float Race::getRecoveryFactor() {
  return recoveryFactor;
}

float Race::getManaFactor() {
  return manaFactor;
}

int Race::getConstitution() {
  return constitution;
}

int Race::getStrength() {
  return strength;
}

int Race::getIntelligence() {
  return intelligence;
}

int Race::getAgility() {
  return agility;
}
