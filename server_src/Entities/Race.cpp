#include "../headers/Race.h"

Race::Race(Configuration& config, const char* typeStr, int raceType)
    : hpFactor(config.getValues(typeStr)["hpFactor"]),
      recoveryFactor(config.getValues(typeStr)["recoveryFactor"]),
      manaFactor(config.getValues(typeStr)["manaFactor"]),
      constitution(config.getValues(typeStr)["constitution"]),
      strength(config.getValues(typeStr)["strength"]),
      intelligence(config.getValues(typeStr)["intelligence"]),
      agility(config.getValues(typeStr)["agility"]),
      race_type(raceType) {}

Race::~Race() {}

float Race::getHpFactor() { return hpFactor; }

float Race::getRecoveryFactor() { return recoveryFactor; }

float Race::getManaFactor() { return manaFactor; }

float Race::getConstitution() { return constitution; }

float Race::getStrength() { return strength; }

float Race::getIntelligence() { return intelligence; }

float Race::getAgility() { return agility; }

int Race::getRaceT() { return race_type; }
