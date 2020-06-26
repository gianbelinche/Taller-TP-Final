#include "MonsterType.h"

MonsterType::MonsterType(int hp, int damage) : hp(hp), damage(damage) {}

MonsterType::~MonsterType() {}

int MonsterType::getHp() { return hp; }

int MonsterType::getDamage() { return damage; }

Monster* MonsterType::newMonster(int id, int x, int y, GameState& world) {
  return new Monster(*this, id, x, y, world);
}
