#ifndef CLASS_H
#define CLASS_H

enum {WIZARD, CLERIC, PALADIN, WARRIOR}; // Esto seria class_type
// La idea es que haya una instancia de este objeto por cada clase del juego
// y cada jugador tiene una referencia/puntero a la que le corresponde
class Class {
private:
  char class_type;
  int hpFactor;
  int manaFactor; // 0 para el guerrero
  int meditationFactor; // idem
  int stregthFactor;
  int constitutionFactor;
  int intelligenceFactor;
  int agilityFactor;

public:
  Class(char class_type, int hpFac, int manaFac, int meditFac);

  ~Class();

  int getHpFactor();

  int getManaFactor();

  int getmeditationFactor();

  int getStrengthFactor();

  int getConstitutionFactor();

  int getIntelligenceFactor();

  int getAgilityFactor();
};

#endif // CLASS_H
