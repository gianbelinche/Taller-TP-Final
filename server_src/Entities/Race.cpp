#include "Race.h"

Race::Race(char race_t, int hpFac, int recFac, int manaFac) {

}

Race::~Race() {
    
}

int Race::getHpFactor() {
  return hpFactor;
}

int Race::getRecoveryFactor() {
  return recoveryFactor;
}

int Race::getManaFactor() {
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
