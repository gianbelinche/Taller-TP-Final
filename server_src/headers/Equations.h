#ifndef EQUATIONS_H
#define EQUATIONS_H

namespace equation {
  int pointsRecovery(float raceRecoveryFac, float seconds);

  int meditationRecovery(float meditationFactor, float intelligence,
                         float seconds);

  int causedDamage(float strength, int minDmg, int maxDmg);

  int playerDefense(int minArmorDef, int maxArmorDef, int minShieldDef, 
                    int maxShieldDef, int minHelmetDef, int maxHelmetDef);

  int maxGold(int level);

  int dropGold(int maxHpNPC);

  int playerHitExp(int attackerLevel, int attackedLevel, int damage);

  int playerDeathExp(int maxHp, int attackedLevel, int attackerLevel);

  int monsterHitExp(int monsterLevel, int damage);

  int monsterDeathExp(int monsterLevel, int maxHp);

  int playerMaxHp(int constitution, int classHpFac, int raceHpFac, int level);

  int playerMaxMana(int intelligence, int manaClassFac,
                    int manaRaceFac, int level);

  int playerMaxExp(int level);

  bool isCritical();

  bool dodgeAttack(int agility);

  int getCurrentLevelStrength(int baseStrength, int level);
} // namespace equation

#endif // EQUATIONS_H
