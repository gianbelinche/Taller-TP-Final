#include "../headers/Class.h"

Class::Class(Configuration& config, std::string typeStr, int classType)
    : 
      hpFactor(config.getValues(typeStr)["hpFactor"]),
      manaFactor(config.getValues(typeStr)["manaFactor"]),
      meditationFactor(config.getValues(typeStr)["meditFac"]),
      strengthFactor(config.getValues(typeStr)["strengthFactor"]),
      constitutionFactor(config.getValues(typeStr)["constitutionFactor"]),
      intelligenceFactor(config.getValues(typeStr)["intelligenceFactor"]),
      agilityFactor(config.getValues(typeStr)["agilityFactor"]),
      class_type(classType) {}

Class::~Class() {}

float Class::getHpFactor() { return hpFactor; }

float Class::getManaFactor() { return manaFactor; }

float Class::getmeditationFactor() { return meditationFactor; }

float Class::getStrengthFactor() { return strengthFactor; }

float Class::getConstitutionFactor() { return constitutionFactor; }

float Class::getIntelligenceFactor() { return intelligenceFactor; }

float Class::getAgilityFactor() { return agilityFactor; }

int Class::getClassT() { return class_type; }
