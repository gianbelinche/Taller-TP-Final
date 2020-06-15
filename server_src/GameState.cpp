

#include "GameState.h"

GameState::GameState() {
}

GameState::~GameState() {
}

PlayerNet* GameState::getPlayer(int id) {
  if (players.find(id) != players.end()) {
    return players[id];
  } else {
    return nullptr;
  }
}

bool GameState::isValidPosition(int x, int y) {
  if (y < 0|| y >= colisionMap.size() ||x < 0 || x >= colisionMap[0].size()) {
    return false;
  } else if (colisionMap[y/TILE_SIZE][x/TILE_SIZE] != 0) {
    return false;
  } else {
    return true;
  }
}

void GameState::playerMoved(int id) {
  // Aca se llama a algo que encole el mensaje del jugador en la cola de
  // mensajes salientes
}