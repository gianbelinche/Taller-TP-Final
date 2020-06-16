#ifndef CLASS_H
#define CLASS_H

enum {WIZARD, CLERIC, PALADIN, WARRIOR};

class Class {
private:
  char class_type;
  int hpFactor;
  int manaFactor;
  int meditationFactor;

public:
  Class(char class_type, int hpFac, int manaFac, int meditFac);

  ~Class();

  int getHpFactor();

  int getManaFactor();

  int getmeditationFactor();
};

#endif // CLASS_H
