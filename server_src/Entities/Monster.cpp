#include "Monster.h"

#include <algorithm>
#include <cmath>
#include <random>

#include "Condition.h"
#include "IsAlive.h"
#include "MonsterType.h"
#include "PlayerNet.h"

#define MIN_DIST 150  // Esto debe ser configurable no se como
#define ATK_DIST 20
#define STEP 10

Monster::Monster(MonsterType &type, int id, int x, int y, GameState &world)
    : Entity(x, y, id, type.getHp()), kind(type), world(world) {}

Monster::~Monster() {}

void Monster::update() {
  currentFrame++;
  if (currentFrame == 30) {  // TODO: Hacer configurable el valor
    currentFrame = 0;
    PlayerNet *player = world.getNearestPlayer(this, &Condition::isAlive);
    int new_x = x;
    int new_y = y;

    if (player != nullptr &&
        world.entitiesDistance(this, player) < MIN_DIST) {
      if (world.entitiesDistance(this, player) <= ATK_DIST) {
        // ATACA
      } else {
        float x_dist = abs(x - player->getX());
        float y_dist = abs(y - player->getY());

        if (x_dist < y_dist) {  // Me muevo en el eje en que haya mas distancia
          if (y < player->getY()) {
            new_y = y + STEP;
          } else {
            new_y = y - STEP;
          }
        } else {
          if (x < player->getX()) {
            new_x = x + STEP;
          } else {
            new_x = x - STEP;
          }
        }
        if (world.isValidPosition(new_x, new_y)) {
          x = new_x;
          y = new_y;
          world.monsterMoved(id);
        }
      }
    } else {  // Si no hay jugador cerca
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_real_distribution<> distr(0, 1);
      float rand_val = distr(gen);  // Valor random
      if (rand_val < 0.25) {
        new_x -= STEP;
      } else if (rand_val >= 0.25 && rand_val < 0.5) {
        new_y -= STEP;
      } else if (rand_val >= 0.5 && rand_val < 0.75) {
        new_x += STEP;
      } else {
        new_y += STEP;
      }
      if (world.isValidPosition(new_x, new_y)) {
        x = new_x;
        y = new_y;
        world.monsterMoved(id);
      }
    }
  }
}

int Monster::takeDamage(int dmgToTake) {
  int oldHp = hp;
  hp = std::max(0, hp - dmgToTake);
  if (hp == 0) {
    world.entityDisappear(id);
  }
  return oldHp - hp;
}

int Monster::attack(PlayerNet* player) {
  int damageDealt = player->takeDamage(kind.getDamage());
  world.playerTookDamage(player->getId(), damageDealt);
}
