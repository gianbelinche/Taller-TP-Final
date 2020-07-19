#ifndef CLASS_H
#define CLASS_H

#include "Configuration.h"
#include <string>

class Class {
 private:
  float hpFactor;
  float manaFactor;
  float meditationFactor;
  float strengthFactor;
  float constitutionFactor;
  float intelligenceFactor;
  float agilityFactor;
  int class_type;

 public:
  Class(Configuration& config, std::string typeStr, int classType);

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
