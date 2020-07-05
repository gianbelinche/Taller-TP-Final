#ifndef RACE_H
#define RACE_H

enum { HUMAN, ELF, DWARF, GNOME };
// Las razas tiene los valores base de los atributos y las clases
// tienen multiplicadores
class Race {
 private:
  int race_type;
  float hpFactor;
  float recoveryFactor;
  float manaFactor;
  int constitution;
  int strength;
  int intelligence;
  int agility;

 public:
  Race(int race_t, float hpFac, float recFac, float manaFac, int consti,
       int str, int intell, int agil);

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
