#include <random>

#include "Equations.h"

// Castea el resultado a int para que no moleste
int equation::pointsRecovery(float raceRecoveryFac, float seconds) {
  return raceRecoveryFac*seconds;
}

int equation::meditationRecovery(float meditationFactor, float intelligence,
                                 float seconds) {
  return meditationFactor * intelligence * seconds;
}

int equation::causedDamage(float strength, int minDmg, int maxDmg) {
  std::default_random_engine gen;
  std::uniform_int_distribution<int> dist(minDmg, maxDmg);
  return strength * dist(gen);
}

int equation::playerDefense(int minArmorDef, int maxArmorDef, int minShieldDef,
                            int maxShieldDef, int minHelmetDef,
                            int maxHelmetDef) {
  std::default_random_engine gen;
  std::uniform_int_distribution<int> armorDef(minArmorDef, maxArmorDef);
  std::uniform_int_distribution<int> shieldDef(minShieldDef, maxShieldDef);
  std::uniform_int_distribution<int> helmetDef(minHelmetDef, maxHelmetDef);

  return armorDef(gen) + shieldDef(gen) + helmetDef(gen);
}
