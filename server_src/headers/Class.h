#ifndef CLASS_H
#define CLASS_H

enum { WIZARD, CLERIC, PALADIN, WARRIOR };  // Esto seria class_type
// La idea es que haya una instancia de este objeto por cada clase del juego
// y cada jugador tiene una referencia/puntero a la que le corresponde
class Class {
 private:
  int class_type;
  float hpFactor;
  float manaFactor;        // 0 para el guerrero
  float meditationFactor;  // idem
  float strengthFactor;
  float constitutionFactor;
  float intelligenceFactor;
  float agilityFactor;

 public:
  Class(int class_type, float hpFac, float manaFac, float meditFac,
        float strFac, float constFac, float intFac, float agiFac);

  ~Class();

  float getHpFactor();

  float getManaFactor();

  float getmeditationFactor();

  float getStrengthFactor();

  float getConstitutionFactor();

  float getIntelligenceFactor();

  float getAgilityFactor();

  int getClassT();
};

#endif  // CLASS_H
