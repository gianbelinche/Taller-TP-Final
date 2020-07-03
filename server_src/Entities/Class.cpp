#include "../headers/Class.h"

Class::Class(char class_type, float hpFac, float manaFac, float meditFac)
    : class_type(class_type),
      hpFactor(hpFac),
      manaFactor(manaFac),
      meditationFactor(meditFac) {}

Class::~Class() {}

float Class::getHpFactor() { return hpFactor; }

float Class::getManaFactor() { return manaFactor; }

float Class::getmeditationFactor() { return meditationFactor; }

float Class::getStrengthFactor() { return strengthFactor; }

float Class::getConstitutionFactor() { return constitutionFactor; }

float Class::getIntelligenceFactor() { return intelligenceFactor; }

float Class::getAgilityFactor() { return agilityFactor; }
