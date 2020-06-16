#include "MonsterType.h"

MonsterType::MonsterType(int hp, int damage) : hp(hp), damage(damage) {}

MonsterType::~MonsterType() {}

int MonsterType::getHp() {
  return hp;
}

int MonsterType::getDamage() {
  return damage;
}

Monster* MonsterType::newMonster(int x, int y) {
  return new Monster(*this, x, y);
}
