#ifndef EQUATIONS_H
#define EQUATIONS_H

namespace equation {
  int pointsRecovery(float raceRecoveryFac, float seconds);

  int meditationRecovery(float meditationFactor, float intelligence,
                         float seconds);

  int causedDamage(float strength, int minDmg, int maxDmg);

  int playerDefense(int minArmorDef, int maxArmorDef, int minShieldDef, 
                    int maxShieldDef, int minHelmetDef, int maxHelmetDef);
} // namespace equation

#endif // EQUATIONS_H
