#include "../headers/MonsterType.h"

#include "../headers/Monster.h"

MonsterType::MonsterType(Configuration& config, std::string typeStr, int npcType)
    : hp(config.getValues(typeStr)["hp"]), 
      damage(config.getValues(typeStr)["damage"]),
      level(config.getValues(typeStr)["level"]),
      velocity(config.getValues(typeStr)["velocity"]),
      atkRange(config.getValues(typeStr)["attackRange"]),
      pursuitDistance(config.getValues(typeStr)["pursuitDistance"]),
      npcType(npcType) {}

MonsterType::~MonsterType() {}

int MonsterType::getHp() { return hp; }

int MonsterType::getDamage() { return damage; }

int MonsterType::getNpcType() { return npcType; }

Monster* MonsterType::newMonster(int id, int x, int y, GameState& world,
                                 ServerEventListener& eventListener) {
  return new Monster(*this, id, x, y, level, velocity, atkRange,
                     pursuitDistance, world, eventListener);
}
