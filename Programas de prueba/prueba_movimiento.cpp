#include <unistd.h>

#include "Game.h"
#include "Spider.h"

int main() {
  Game juego;
  juego.addPlayer(1);
  juego.addEntity();
  juego.start();
  usleep(100000);
  juego.addIncoming("1r");
  usleep(3000000);
  juego.addIncoming("1r");
  usleep(1000000);
  juego.addIncoming("1d");
  juego.join();

  return 0;
}