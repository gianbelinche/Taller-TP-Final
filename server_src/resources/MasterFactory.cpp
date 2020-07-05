#include "../headers/MasterFactory.h"

MasterFactory::MasterFactory(std::atomic<uint32_t>& idCounter,
                             Configuration& configuration, GameState& gameState,
                             ServerEventListener& eventListener)
    : idGenerator(idCounter),
      config(configuration),
      world(gameState),
      listener(eventListener),
      goblin(config.getValues(GOBLIN)["hp"], config.getValues(GOBLIN)["damage"],
             config.getValues(GOBLIN)["level"]),
      spider(config.getValues(SPIDER)["hp"], config.getValues(SPIDER)["damage"],
             config.getValues(SPIDER)["level"]),
      skeleton(config.getValues(SKELETON)["hp"],
               config.getValues(SKELETON)["damage"],
               config.getValues(SKELETON)["level"]),
      zombie(config.getValues(ZOMBIE)["hp"], config.getValues(ZOMBIE)["damage"],
             config.getValues(ZOMBIE)["level"]) {}

MasterFactory::~MasterFactory() {}

Monster* MasterFactory::newGoblin(int x, int y) {
  return goblin.newMonster(idGenerator++, x, y, world, listener);
}

Monster* MasterFactory::newSkeleton(int x, int y) {
  return skeleton.newMonster(idGenerator++, x, y, world, listener);
}

Monster* MasterFactory::newSpider(int x, int y) {
  return spider.newMonster(idGenerator++, x, y, world, listener);
}

Monster* MasterFactory::newZombie(int x, int y) {
  return zombie.newMonster(idGenerator++, x, y, world, listener);
}

