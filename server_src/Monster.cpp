#include "Monster.h"

Monster::Monster(MonsterType &type, int x, int y) : 
                 Entity(x, y), kind(type), hp(type.getHp()) {}

Monster::~Monster() {}



void Monster::update() { 
    // TODO
}
