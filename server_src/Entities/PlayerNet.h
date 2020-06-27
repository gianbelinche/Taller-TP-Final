#ifndef PLAYERNET_H
#define PLAYERNET_H

class GameState;

#include "../Items/Armor.h"
#include "../Items/Helmet.h"
#include "../Items/Shield.h"
#include "../Items/Weapon.h"
#include "Class.h"
#include "Entity.h"
#include "PlayerState.h"
#include "Race.h"

class PlayerNet : public Entity {
 private:
  PlayerState* state;  // Ver si puede ser una referencia
  Class* playerClass;
  Race* playerRace;
  int mana;
  int maxHp = 100;
  int maxMana;
  int velocity;
  int level;
  int exp;
  int gold;
  GameState& world;
  Weapon* weapon;
  Armor* armor;
  Helmet* helmet;
  Shield* shield;

 public:
  PlayerNet(int x, int y, int id, GameState& currState, int hp, int mana,
            int velocity, int currExp, int currGold, Weapon* wea, Armor* arm,
            Helmet* helm, Shield* sh, PlayerState* sta, Class* cla, Race* ra);

  ~PlayerNet();

  /* ------------- Getters ------------- */

  int getAttackRange();

  int getDamage();
  
  int getCurrFrame();

  int getFPS();  // Para la recuperacion se necesitan los segundos pasados

  float getIntelligence();

  float getMeditationFactor();

  float getRaceRecovery();

  float getStrength();

  /* ---------- Acciones ---------- */

  int attack(Entity* ent);

  void changeState(PlayerState* new_state);

  void heal(int points);

  // Pre: la posicion es valida(no colisiona)
  void move(int x, int y);

  void recoverMana(int mPoints);

  int takeDamage(int dmgToTake) override;

  void update() override;
};

#endif  // PLAYERNET_H
