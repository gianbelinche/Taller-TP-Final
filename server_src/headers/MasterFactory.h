#include <atomic>

#include "Configuration.h"
#include "GameState.h"
#include "Monster.h"
#include "MonsterType.h"
#include "ServerEventListener.h"

#define GOBLIN "goblin"
#define SKELETON "skeleton"
#define SPIDER "spider"
#define ZOMBIE "zombie"

class MasterFactory {
 private:
  std::atomic<uint32_t>& idGenerator;
  Configuration& config;
  GameState& world;
  ServerEventListener& listener;
  MonsterType goblin;
  MonsterType spider;
  MonsterType skeleton;
  MonsterType zombie;

 public:
  MasterFactory(std::atomic<uint32_t>& idCounter, Configuration& configuration,
                GameState& gameState, ServerEventListener& eventListener);

  ~MasterFactory();

  Monster* newGoblin(int x, int y);

  Monster* newSkeleton(int x, int y);

  Monster* newSpider(int x, int y);

  Monster* newZombie(int x, int y);

  
};
