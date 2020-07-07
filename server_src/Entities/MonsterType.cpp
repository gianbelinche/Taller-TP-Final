#include "../headers/MonsterType.h"

#include "../headers/Monster.h"

MonsterType::MonsterType(int hp, int damage, int level, int npcType,
                         int velocity, int atkRange, int pursuitDistance)
    : hp(hp),
      damage(damage),
      level(level),
      npcType(npcType),
      velocity(velocity),
      atkRange(atkRange),
      pursuitDistance(pursuitDistance) {}

MonsterType::~MonsterType() {}

int MonsterType::getHp() { return hp; }

int MonsterType::getDamage() { return damage; }

int MonsterType::getNpcType() { return npcType; }

Monster* MonsterType::newMonster(int id, int x, int y, GameState& world,
                                 ServerEventListener& eventListener) {
  return new Monster(*this, id, x, y, level, velocity, atkRange,
                     pursuitDistance, world, eventListener);
}
