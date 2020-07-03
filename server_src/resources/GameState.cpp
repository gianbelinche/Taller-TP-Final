#include "../headers/GameState.h"

#include <cmath>
#include <limits>

#define FRAMES_PER_SECOND 30

GameState::GameState(std::vector<std::vector<bool>>& collisions, int fps)
    : colisionMap(collisions), framesPerSecond(fps) {}

GameState::~GameState() {}

PlayerNet* GameState::getPlayer(int id) {
  if (players.find(id) != players.end()) {
    return players[id];
  } else {
    return nullptr;
  }
}

bool GameState::isValidPosition(int x, int y) {
  if (y < 0 || y >= (int)colisionMap.size() || x < 0 ||
      x >= (int)colisionMap[0].size()) {
    return false;
  } else if (colisionMap[y / TILE_SIZE][x / TILE_SIZE] != 0) {
    return false;
  } else {
    return true;
  }
}

void GameState::playerMoved(int id, char direction) {
  // Aca se llama a algo que encole el mensaje del jugador en la cola de
  // mensajes salientes
}

float GameState::entitiesDistance(Entity* ent1, Entity* ent2) {
  int dist_x = abs(ent1->getX() - ent2->getX());
  int dist_y = abs(ent1->getY() - ent2->getY());
  return sqrt(pow(dist_x, 2) + pow(dist_y, 2));
}

PlayerNet* GameState::getNearestPlayer(Entity* ent, Condition* cond) {
  PlayerNet* nearest = nullptr;
  float smallestDistance = std::numeric_limits<float>::infinity();
  float curr;
  for (auto& it : players) {
    if ((curr = entitiesDistance(ent, it.second)) < smallestDistance &&
        (cond->evaluate(it.second))) {
      nearest = it.second;
      smallestDistance = curr;
    }
  }
  return nearest;
}

void GameState::monsterMoved(int id) {
  // Busca el bichito en el map de bichos(o no) y manda el mensaje
  // Ver si no conviene mergear con el playerMoved
}

int GameState::getFPS() { return framesPerSecond; }

Entity* GameState::getEntity(int id) {
  if (entities.find(id) != entities.end()) {
    return entities[id];
  } else {
    return nullptr;
  }
}

bool GameState::playerCanAttack(PlayerNet* player, Entity* ent) {
  if (!player->isAlive() || !ent->isAlive() || !ent->canBeAttackedBy(player)) {
    return false;
  } else if (player->getAttackRange() < entitiesDistance(player, ent)) {
    return false;
  } else if (player->getId() == ent->getId()) {
    if (player->getDamage() >=
        0) {  // Se puede curar, pero no dañarse a si mismo
      return false;
    }
  }
  return true;
}

void GameState::addEntity(Entity* ent) {
  entities[ent->getId()] = ent;
  // Aca deberia avisarle a los jugadores que aparecio un bichito
}

void GameState::addPlayer(PlayerNet* player) {
  players[player->getId()] = player;
  entities[player->getId()] = player;
  // Idem anterior, hay que brodcastear que aparecio
}

void GameState::playerDied(int id) {}

void GameState::playerTookDamage(int id, int damage) {}

void GameState::entityDisappear(int id) {}

void GameState::playerDealtDamage(int id, int damage) {}

void GameState::playerLeveledUp(int id) {}

void GameState::playerExpGain(int id, int gain) {}

void GameState::update() {
  for (auto &it: entities) {
    it.second->update();
  }    
}
