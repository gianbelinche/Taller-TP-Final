#include "../headers/Race.h"

Race::Race(Configuration& config, std::string typeStr, int raceType)
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

int Race::getConstitution() { return constitution; }

int Race::getStrength() { return strength; }

int Race::getIntelligence() { return intelligence; }

int Race::getAgility() { return agility; }

int Race::getRaceT() { return race_type; }
