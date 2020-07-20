#include "../headers/Monster.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

#include "../headers/Condition.h"
#include "../headers/Equations.h"
#include "../headers/IsAlive.h"
#include "../headers/MonsterType.h"
#include "../headers/PlayerNet.h"

Monster::Monster(MonsterType& type, int id, int x, int y, int level,
                 int velocity, int atkRange, int pursuitDistance,
                 GameState& world, ServerEventListener& eventListener,
                 int attackCooldown, int maxStepsPerdirection)
    : Entity(x, y, id, type.getHp(), level),
      kind(type),
      world(world),
      listener(eventListener),
      velocity(velocity),
      atkRange(atkRange),
      pursuitDistance(pursuitDistance),
      attackCooldown(attackCooldown),
      currentAttackCooldown(0),
      maxStepsToTake(maxStepsPerdirection),
      stepsToTake(0),
      currentDirection(0) {}

Monster::~Monster() {}

void Monster::moveToPlayer(PlayerNet* player) {
  int new_x = x;
  int new_y = y;
  float x_dist = abs(x - player->getX());
  float y_dist = abs(y - player->getY());
  int direction;

  if (x_dist < y_dist) {  // Me muevo en el eje en que haya mas distancia
    if (y < player->getY()) {
      new_y = y + velocity;
      direction = 1;
    } else {
      new_y = y - velocity;
      direction = 0;
    }
  } else {
    if (x < player->getX()) {
      new_x = x + velocity;
      direction = 3;
    } else {
      new_x = x - velocity;
      direction = 2;
    }
  }
  if (world.isValidPosition(new_x, new_y) &&
      !world.isCityPosition(new_x, new_y)) {
    moveTo(new_x, new_y, direction);
  }
}

void Monster::moveRandom() {
  if (stepsToTake == 0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> random_direction(0, 4);
    std::uniform_int_distribution<> randomAmountSteps(1, maxStepsToTake);
    currentDirection = random_direction(gen);
    stepsToTake = randomAmountSteps(gen);
  }
  int new_x = x;
  int new_y = y;

  switch (currentDirection) {
  case 0:
    new_y -= velocity;
    break;
  case 1:
    new_y += velocity;
    break;
  case 2:
    new_x -= velocity;
    break;
  case 3:
    new_x += velocity;
    break;
  default:
    break;
  }
  stepsToTake--;
  if (world.isValidPosition(new_x, new_y) &&
      !world.isCityPosition(new_x, new_y)) {
    moveTo(new_x, new_y, currentDirection);
  }
}

void Monster::update() {
  currentFrame++;
  if (currentFrame == 5) {  // TODO: Hacer configurable el valor
    currentFrame = 0;
    PlayerNet* player = world.getNearestPlayer(this, &Condition::isAlive);
    if (player != nullptr &&
        world.entitiesDistance(this, player) < pursuitDistance) {
      if (world.entitiesDistance(this, player) <= atkRange) {
        if (currentAttackCooldown == 0) {
          attack(player);
          currentAttackCooldown = attackCooldown;
        }
        currentAttackCooldown--;
      } else {
        moveToPlayer(player);
      }
    } else {  // Si no hay jugador cerca
      moveRandom();
    }
  }
}

int Monster::takeDamage(int dmgToTake, bool canDodge) {
  int oldHp = hp;
  hp = std::max(0, hp - dmgToTake);
  if (hp == 0) {
    world.rmEntity(id);
    world.decreaseMonsterAmount(kind.getNpcType());
    listener.entityDisappear(id);
    world.generateDrop(x, y, equation::dropGold(maxHp));
  }
  return oldHp - hp;
}

int Monster::attack(PlayerNet* player) {
  int damageDealt = player->takeDamage(kind.getDamage(), true);

  return damageDealt;
}

int Monster::getDeathExp(int attackerLevel) {
  return equation::monsterDeathExp(level, maxHp);
}

int Monster::getHitExp(int AttackerLevel, int damage) {
  return equation::monsterHitExp(level, damage);
}

bool Monster::canBeAttackedBy(Entity* ent) { return true; }

void Monster::moveTo(int new_x, int new_y, int direction) {
  x = new_x;
  y = new_y;
  listener.entityMoved(id, direction);
  animFrame++;
  if (animFrame == 8) {
    listener.entityMoved(id, 4);
    animFrame = 0;
  }
}

std::vector<uint32_t> Monster::getSendable() {
  std::vector<uint32_t> monsterInfo = {1};
  monsterInfo.push_back(id);
  monsterInfo.push_back(MOB_TYPE);
  monsterInfo.push_back(kind.getNpcType());
  monsterInfo.push_back(x);
  monsterInfo.push_back(y);
  return monsterInfo;
}

int Monster::getNpcType() { return kind.getNpcType(); }

bool Monster::mustBeDeleted() { return !isAlive(); }
