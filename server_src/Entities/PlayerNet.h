#ifndef PLAYERNET_H
#define PLAYERNET_H

class GameState;

#include "../Items/Armor.h"
#include "../Items/Helmet.h"
#include "../Items/Shield.h"
#include "../Items/Weapon.h"
#include "Class.h"
#include "Entity.h"
#include "Race.h"
#include "PlayerState.h"

class PlayerNet : public Entity{
private:
  PlayerState* state; // Ver si puede ser una referencia
  Class* playerClass;
  Race* playerRace;
  int mana;
  int maxHp;
  int maxMana;
  int velocity;
  int level;
  int exp;
  int gold;
  GameState &world;
  Weapon* weapon;
  Armor* armor;
  Helmet* helmet;
  Shield* shield;
public:
  PlayerNet(int x, int y, int id, GameState &currState, int hp, int mana,
            int velocity, int currExp, int currGold);

  ~PlayerNet();

  void update() override;

  // Pre: la posicion es valida(no colisiona)
  void move(int x, int y);

  void changeState(PlayerState* new_state);

  float getRaceRecovery();

  float getMeditationFactor();

  int getFPS(); // Para la recuperacion se necesitan los segundos pasados

  void heal(int points);

  void recoverMana(int mPoints);

  float getIntelligence();

  float getStrength();

  int getCurrFrame();

  int attack(Entity* ent);

  int takeDamage(int dmgToTake) override;

};

#endif // PLAYERNET_H
