

#include "PlayerNet.h"

PlayerNet::PlayerNet(int id, GameState &currState, int maxHP, int maxMana,
                     int currExp, int currGold) :
                     id(id), world(currState), maxHp(maxHP), maxMana(maxMana),
                     exp(currExp), gold(currGold) {}

PlayerNet::~PlayerNet()
{
}