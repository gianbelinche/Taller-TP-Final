#ifndef PLAYERNET_H
#define PLAYERNET_H

class GameState;

#include "Armor.h"
#include "Class.h"
#include "Entity.h"
#include "Helmet.h"
#include "Inventory.h"
#include "PlayerState.h"
#include "Race.h"
#include "ServerEventListener.h"
#include "Shield.h"
#include "Weapon.h"

class PlayerNet : public Entity {
 private:
  PlayerState* state;  // Ver si puede ser una referencia
  Class* playerClass;
  Race* playerRace;
  Inventory inventory;
  int mana;
  int maxMana;
  int velocity;
  int maxExp;
  int exp;
  int gold;
  int excessGold;
  int maxGold;
  int selectedNpc = -1;
  int selectedSlot = -1;
  int immobilizedFramesLeft = 0;
  int framesPerUpdate;
  GameState& world;
  Weapon* weapon;
  Armor* armor;
  Helmet* helmet;
  Shield* shield;
  ServerEventListener& listener;
  Weapon* defaultWeapon;
  Armor* defaultArmor;
  Helmet* defaultHelmet;
  Shield* defaultShield;

 public:
  PlayerNet(int x, int y, int id, GameState& currState, int velocity,
            int currExp, int currLevel, int currGold, Weapon* wea, Armor* arm,
            Helmet* helm, Shield* sh, PlayerState* sta, Class* cla, Race* ra,
            ServerEventListener& eventListener, int framesBetweenUpdate,
            Weapon* defaultWeap, Armor* defaultArm, Helmet* defaultHelm, 
            Shield* defaultShiel);

  ~PlayerNet();

  /* ------------- Getters ------------- */

  int getAttackRange();

  int getDamage();

  int getConstitution();

  int getCurrFrame();

  int getFPS();  // Para la recuperacion se necesitan los segundos pasados

  int getDeathExp(int attackerLevel) override;

  int getHitExp(int AttackerLevel, int damage) override;

  float getIntelligence();

  int getLevel();

  float getMeditationFactor();

  float getRaceRecovery();

  float getStrength();

  float getAgility();

  int getVelocity();

  int getGold();

  int getMaxGold();

  int getHp();

  int getMaxHp();

  int getMana();

  int getMaxMana();

  int getExp();

  int getMaxExp();

  int getSelectedNpc();

  int getSelectedSlot();

  int getInventorySize();

  int getWeaponType();

  int getArmorType();

  int getShieldType();

  int getHemletType();

  bool canMove();

  void decreaseImmobilizedFramesLeft();

  Inventory& getInventory();

  std::vector<uint32_t> getSendable() override;

  std::vector<uint32_t> getData();

  /* ---------- Acciones ---------- */

  int attack(Entity* ent);

  bool canBeAttackedBy(Entity* ent) override;

  void changeState(PlayerState* new_state);

  void heal(int points);

  // Pre: la posicion es valida(no colisiona)
  void move(int x, int y);

  void receiveExp(int amount);

  void recoverMana(int mPoints);

  int takeDamage(int dmgToTake, bool canDodge) override;

  void substractMana(int amount);

  void selectNpc(int id);

  void selectSlot(int slot);

  void substractGold(int amount);

  void addGold(int amount);

  void update() override;

  void equipWeapon(Weapon* weapon);

  void equipArmor(Armor* armor);

  void equipHelmet(Helmet* helmet);

  void equipShield(Shield* shield);

  void setImmobilizedTime(int frames);

  bool isAlive() override;

  void dropItem(int slot, int x, int y);

  void removeItemFromInventory(int slot);

  void addItemToInventory(Item* item);

 private:
  void levelUp();

  void updateMaxHp();

  void updateMaxMana();

  void updateMaxGold();

  void updateMaxExp();
};

#endif  // PLAYERNET_H
