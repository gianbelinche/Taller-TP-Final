#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

#include "Thread.h"

class PlayerTest : public Thread {
private:
  int x;
  int y;
  const int id;
public:
  PlayerTest(int id);

  ~PlayerTest();
};

#endif
