#include "../headers/Monster.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

#include "../headers/Equations.h"
#include "../headers/Condition.h"
#include "../headers/IsAlive.h"
#include "../headers/MonsterType.h"
#include "../headers/PlayerNet.h"

#define MIN_DIST 200  // Esto debe ser configurable no se como
#define ATK_DIST 20
#define STEP 3

Monster::Monster(MonsterType &type, int id, int x, int y, int level,
                 GameState &world, ServerEventListener& eventListener)
    : Entity(x, y, id, type.getHp(), level),
      kind(type),
      world(world),
      listener(eventListener) {}

Monster::~Monster() {}

void Monster::update() {
  currentFrame++;
  if (currentFrame == 5) {  // TODO: Hacer configurable el valor
    currentFrame = 0;
    PlayerNet *player = world.getNearestPlayer(this, &Condition::isAlive);
    int new_x = x;
    int new_y = y;
    int direction;
    if (player != nullptr &&
        world.entitiesDistance(this, player) < MIN_DIST) {
      if (world.entitiesDistance(this, player) <= ATK_DIST) {
        attack(player);
      } else {
        float x_dist = abs(x - player->getX());
        float y_dist = abs(y - player->getY());

        if (x_dist < y_dist) {  // Me muevo en el eje en que haya mas distancia
          if (y < player->getY()) {
            new_y = y + STEP;
            direction = 1;
          } else {
            new_y = y - STEP;
            direction = 0;
          }
        } else {
          if (x < player->getX()) {
            new_x = x + STEP;
            direction = 3;
          } else {
            new_x = x - STEP;
            direction = 2;
          }
        }
        if (world.isValidPosition(new_x, new_y)) {
          moveTo(new_x, new_y, direction);
        }
      }
    } else {  // Si no hay jugador cerca
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<> distr(0, 1);
      float rand_val = distr(gen);  // Valor random
      if (rand_val < 0.25) {
        new_x -= STEP;
        direction = 2;
      } else if (rand_val >= 0.25 && rand_val < 0.5) {
        new_y -= STEP;
        direction = 0;
      } else if (rand_val >= 0.5 && rand_val < 0.75) {
        direction = 3;
        new_x += STEP;
      } else {
        new_y += STEP;
        direction = 1;
      }
      if (world.isValidPosition(new_x, new_y)) {
        moveTo(new_x, new_y, direction);
      }
    }
  }
}

int Monster::takeDamage(int dmgToTake) {
  int oldHp = hp;
  hp = std::max(0, hp - dmgToTake);
  std::cout << "Le hizo: " << dmgToTake << " daño al motro\n";
  if (hp == 0) {
    std::cout << "Se murio el mostro\n";
    world.rmEntity(id);
    listener.entityDisappear(id);
  }
  return oldHp - hp;
}

int Monster::attack(PlayerNet* player) {
  int damageDealt = player->takeDamage(kind.getDamage());

  return damageDealt;
}

int Monster::getDeathExp(int attackerLevel) {
  return equation::monsterDeathExp(level, maxHp);
}

int Monster::getHitExp(int AttackerLevel, int damage) {
  return equation::monsterHitExp(level, damage);
}

bool Monster::canBeAttackedBy(Entity* ent) {
  return true;
}

void Monster::moveTo(int new_x, int new_y, int direction) {
  x = new_x;
  y = new_y;
  //for (int i = 0; i < STEP; i++) {
  listener.entityMoved(id, direction);
  //}
  animFrame++;
  if (animFrame == 4) {
    listener.entityMoved(id, 4);
    animFrame = 0;
  }
}

std::vector<uint32_t> Monster::getSendable() {
  std::vector<uint32_t> monsterInfo = {1};
  monsterInfo.push_back(id);
  monsterInfo.push_back(kind.getNpcType());
  monsterInfo.push_back(x);
  monsterInfo.push_back(y);
  return monsterInfo;
}

int Monster::getNpcType() {
  return kind.getNpcType();
}

