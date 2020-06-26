

#include "Entities/PlayerNet.h"

class IsAlive;

class Condition {  // AKA callback version objetos
 private:
 public:
  Condition();

  ~Condition();

  bool virtual evaluate(PlayerNet* player);

 public:
  static IsAlive isAlive;
};
