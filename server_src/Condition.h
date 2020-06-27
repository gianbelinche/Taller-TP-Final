#ifndef CONDITION_H
#define CONDITION_H

#include "Entities/PlayerNet.h"

class IsAlive;
class PlayerNet;

class Condition {  // AKA callback version objetos
 private:
 public:
  Condition();

  ~Condition();

  bool virtual evaluate(PlayerNet* player);

 public:
  static IsAlive isAlive;
};

#endif // CONDITION_H
