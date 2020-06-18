#ifndef RACE_H
#define RACE_H

enum {HUMAN, ELF, DWARF, GNOME};
// Las razas tiene los valores base de los atributos y las clases
// tienen multiplicadores
class Race {
private:
  char race_type;
  int hpFactor;
  int recoveryFactor;
  int manaFactor;
  int constitution;
  int strength;
  int intelligence;
  int agility;
public:
  Race(char race_t, int hpFac, int recFac, int manaFac);

  ~Race();

  int getHpFactor();

  int getRecoveryFactor();

  int getManaFactor();

  int getConstitution();

  int getStrength();

  int getIntelligence();

  int getAgility();
};

#endif // RACE_H
