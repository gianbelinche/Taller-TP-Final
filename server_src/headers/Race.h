#ifndef RACE_H
#define RACE_H

#include "Configuration.h"
#include <string>

class Race {
 private:
  float hpFactor;
  float recoveryFactor;
  float manaFactor;
  float constitution;
  float strength;
  float intelligence;
  float agility;
  int race_type;

 public:
  Race(Configuration& config, const char* typeStr, int raceType);

  ~Race();

  float getHpFactor();

  float getRecoveryFactor();

  float getManaFactor();

  float getConstitution();

  float getStrength();

  float getIntelligence();

  float getAgility();

  int getRaceT();
};

#endif  // RACE_H
