#ifndef RACE_H
#define RACE_H

enum {HUMAN, ELF, DWARF, GNOME};

class Race {
private:
  char race_type;
  int hpFactor;
  int recoveryFactor;
  int manaFactor;
public:
  Race(char race_t, int hpFac, int recFac, int manaFac);

  ~Race();

  int getHpFactor();

  int getRecoveryFactor();

  int getManaFactor();
};

#endif // RACE_H
