#include <iostream>
#include <unistd.h>

#include "Game.h"
#include "Spider.h"

Game::Game() : keep_running(true) {}

Game::~Game() {}

void Game::run() {
  loop();
}

void Game::loop() {
  while (keep_running) {
    processInput(); // Decodifica y procesa todos los eventos encolados
    update();
    usleep(30000); // Algo mas de 30 fps
  }
}

void Game::processInput() {
  std::vector<std::string> packedEvents;
  incomingEvents.emptyQueue(packedEvents);
  for (auto &ev : packedEvents) {
    // Aca el protocolo decodificaria el evento
    // Por ahora solo puede mover al jugador
    movePlayer(ev);
  }
}

void Game::update() {
  for (auto &ent : entities) {
    ent->update();
  }
}

void Game::movePlayer(std::string &move) {
  // Hardcodeo violento para testing
  int id_user = std::stoi(move.substr(0,1));
  std::string direction = move.substr(1, 1);

  
  const int x = onlinePlayers.at(id_user).getX();
  const int y = onlinePlayers.at(id_user).getY();

  int new_x = x;
  int new_y = y;

  if (direction == "u") {
    new_y--;
  } else if (direction == "d") {
    new_y++;
  } else if (direction == "l") {
    new_x--;
  } else if (direction == "r") {
    new_x++;
  }
  // Aca se deberia chequear si el movimiento es valido

  onlinePlayers.at(id_user).setX(new_x);
  onlinePlayers.at(id_user).setY(new_y);

  std::cout << "El user esta en X: " << new_x << " Y: " << new_y << std::endl;

  // Enviar al usuario el movimiento
}


void Game::addPlayer(int id) {
  onlinePlayers.insert(std::make_pair(id, PlayerTestNet{id}));
}

void Game::addEntity() { // Hardcodeado de momento, no me importa nada
  entities.push_back(new Spider());
}

void Game::addIncoming(std::string s) {
  incomingEvents.push(s);
}
