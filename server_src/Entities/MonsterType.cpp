#include "../headers/MonsterType.h"

MonsterType::MonsterType(int hp, int damage) : hp(hp), damage(damage) {}

MonsterType::~MonsterType() {}

int MonsterType::getHp() { return hp; }

int MonsterType::getDamage() { return damage; }

Monster* MonsterType::newMonster(int id, int x, int y, int level,
                                 GameState& world,
                                 ServerEventListener& eventListener) {
  return new Monster(*this, id, x, y, level, world, eventListener);
}
