#ifndef PLAYERNET_H
#define PLAYERNET_H

class GameState;

class PlayerNet {
private:
  int id;
  int hp;
  int mana;
  int maxHp;
  int maxMana;
  int x;
  int y;
  int exp;
  int gold;
  GameState &world;
  int currFrame;
public:
  PlayerNet(int id, GameState &currState, int maxHP, int maxMana,
            int currExp, int currGold);
  ~PlayerNet();
};

#endif // PLAYERNET_H
