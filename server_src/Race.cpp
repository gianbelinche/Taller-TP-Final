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
