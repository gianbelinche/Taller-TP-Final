#include "../headers/MonsterType.h"

MonsterType::MonsterType(int hp, int damage, int level)
    : hp(hp), damage(damage), level(level) {}

MonsterType::~MonsterType() {}

int MonsterType::getHp() { return hp; }

int MonsterType::getDamage() { return damage; }

Monster* MonsterType::newMonster(int id, int x, int y,
                                 GameState& world,
                                 ServerEventListener& eventListener) {
  return new Monster(*this, id, x, y, level, world, eventListener);
}
