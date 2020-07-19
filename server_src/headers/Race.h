#ifndef RACE_H
#define RACE_H

#include "Configuration.h"
#include <string>

class Race {
 private:
  float hpFactor;
  float recoveryFactor;
  float manaFactor;
  int constitution;
  int strength;
  int intelligence;
  int agility;
  int race_type;

 public:
  Race(Configuration& config, const char* typeStr, int raceType);

  ~Race();

  float getHpFactor();

  float getRecoveryFactor();

  float getManaFactor();

  int getConstitution();

  int getStrength();

  int getIntelligence();

  int getAgility();

  int getRaceT();
};

#endif  // RACE_H
