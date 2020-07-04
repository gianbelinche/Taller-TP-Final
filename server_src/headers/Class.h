#ifndef CLASS_H
#define CLASS_H

enum { WIZARD, CLERIC, PALADIN, WARRIOR };  // Esto seria class_type
// La idea es que haya una instancia de este objeto por cada clase del juego
// y cada jugador tiene una referencia/puntero a la que le corresponde
class Class {
 private:
  char class_type;
  float hpFactor;
  float manaFactor;        // 0 para el guerrero
  float meditationFactor;  // idem
  float strengthFactor = 1;
  float constitutionFactor = 1;
  float intelligenceFactor = 15;
  float agilityFactor = 2;

 public:
  Class(char class_type, float hpFac, float manaFac, float meditFac);

  ~Class();

  float getHpFactor();

  float getManaFactor();

  float getmeditationFactor();

  float getStrengthFactor();

  float getConstitutionFactor();

  float getIntelligenceFactor();

  float getAgilityFactor();
};

#endif  // CLASS_H
