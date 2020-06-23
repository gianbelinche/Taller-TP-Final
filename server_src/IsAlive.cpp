#include "IsAlive.h"


IsAlive::IsAlive() {
    
}

IsAlive::~IsAlive() {
    
}

bool IsAlive::evaluate(PlayerNet* player) {
  return player->isAlive();    
}
