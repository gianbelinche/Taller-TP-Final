#include "../headers/GameState.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <random>

#include "../headers/MasterFactory.h"
#include "../headers/Monster.h"
#include "../headers/Persistor.h"

#define FRAMES_PER_SECOND 30
#define TAKE_RANGE 30

GameState::GameState(std::vector<std::vector<bool>>& collisions,
                     std::vector<std::vector<bool>>& cities, int fps,
                     ServerEventListener& eventListener, MasterFactory& fac,
                     Configuration& configuration,
                     std::unordered_map<std::string, float>& NPCsAmount)
    : config(configuration),
      colisionMap(collisions),
      citiesMap(cities),
      framesPerSecond(fps),
      listener(eventListener),
      factory(fac),
      maxNPCsAmount(NPCsAmount) {
  spawnCooloff = config.getConfigValue("spawnCooloffFrames");
  for (auto& npc: maxNPCsAmount) {
    currentNPCsAmount[npc.first] = 0;
  }
}

GameState::~GameState() {
  for (auto& ent: entities) {
    delete ent.second;
  }
  for (auto& item: droppedItems) {
    delete item.second;
  }
  for (auto& npc: npcs) {
    delete npc.second;
  }
}

PlayerNet* GameState::getPlayer(int id) {
  if (players.find(id) != players.end()) {
    return players[id];
  } else {
    return nullptr;
  }
}

bool GameState::isValidPosition(int x, int y) {
  if (y < 0 || (int)(y / TILE_SIZE) >= (int)colisionMap.size() || x < 0 ||
      (int)(x / TILE_SIZE) >= (int)colisionMap[0].size()) {
    return false;
  } else if (colisionMap[y / TILE_SIZE][x / TILE_SIZE] != 0) {
    return false;
  } else {
    return true;
  }
}

bool GameState::isCityPosition(int x, int y) {
  if (citiesMap[y / TILE_SIZE][x / TILE_SIZE] == 0) {
    return false;
  } else {
    return true;
  }
}

float GameState::entitiesDistance(Entity* ent1, Entity* ent2) {
  int dist_x = abs(ent1->getX() - ent2->getX());
  int dist_y = abs(ent1->getY() - ent2->getY());
  return sqrt(pow(dist_x, 2) + pow(dist_y, 2));
}

PlayerNet* GameState::getNearestPlayer(Entity* ent, Condition* cond) {
  PlayerNet* nearest = nullptr;
  float smallestDistance = std::numeric_limits<float>::infinity();
  float curr;
  for (auto& it : players) {
    if ((curr = entitiesDistance(ent, it.second)) < smallestDistance &&
        (cond->evaluate(it.second))) {
      nearest = it.second;
      smallestDistance = curr;
    }
  }
  return nearest;
}

NPC* GameState::getNearestPriest(Entity* ent) {
  NPC* nearest = nullptr;
  float curr;
  float smallestDistance = std::numeric_limits<float>::infinity();
  for (auto& it : npcs) {
    if (it.second->getNpcType() == PRIEST_TYPE &&
        (curr = entitiesDistance(ent, it.second)) < smallestDistance) {
      nearest = it.second;
      smallestDistance = curr;
    }
  }
  return nearest;
}

int GameState::getFPS() { return framesPerSecond; }

Entity* GameState::getEntity(int id) {
  if (entities.find(id) != entities.end()) {
    return entities[id];
  } else {
    return nullptr;
  }
}

bool GameState::playerCanAttack(PlayerNet* player, Entity* ent) {
  if (player->getId() == ent->getId() && player->isAlive()) {
    if (player->getDamage() >= 0) {  // Se puede curar,pero no dañarse a si
                                     // mismo
      return false;
    }
    return true;
  }
  if (!player->isAlive() || !ent->isAlive() || !ent->canBeAttackedBy(player) ||
      isCityPosition(player->getX(), player->getY())) {
    return false;
  } else if (player->getAttackRange() < entitiesDistance(player, ent)) {
    return false;
  }
  return true;
}

void GameState::addEntity(Entity* ent) {
  entities[ent->getId()] = ent;
}

void GameState::addPlayerFromData(std::vector<uint32_t>& playerData) {
  PlayerNet* newPlayer = factory.createPlayer(playerData, *this);
  std::unique_lock<std::mutex> l(entitiesMapMutex);
  players[newPlayer->getId()] = newPlayer;
  entities[newPlayer->getId()] = newPlayer;
}

void GameState::update() {
  for (auto& it : entities) {
    it.second->update();
  }
  if (spawnCooloff == 0) {
    spawnCooloff = config.getConfigValue("spawnCooloffFrames");
    verifyNPCsAmount();
  }
  spawnCooloff--;
}

void GameState::verifyNPCsAmount() {
  for (auto& npc : currentNPCsAmount) {
    if (npc.second < maxNPCsAmount[npc.first]) {
      generateMonsterType(std::stoi(npc.first));
    }
  }
}

void GameState::generateMonsterType(int monsterType) {
  std::pair<int, int> position = getSpawnPosition(monsterType);
  int spawnX = position.first;
  int spawnY = position.second;

  Monster* newMonster;
  switch (monsterType) {
    case SPIDER_TYPE:
      newMonster = factory.newSpider(spawnX, spawnY, *this);
      break;
    case SKELETON_TYPE:
      newMonster = factory.newSkeleton(spawnX, spawnY, *this);
      break;
    case GOBLIN_TYPE:
      newMonster = factory.newGoblin(spawnX, spawnY, *this);
      break;
    case ZOMBIE_TYPE:
      newMonster = factory.newZombie(spawnX, spawnY, *this);
      break;
    default:
      std::cerr << "Tipo de mob invalido\n";
      return;
  }
  listener.entitySpawn(newMonster->getSendable());
  currentNPCsAmount[std::to_string(monsterType)]++;
  addEntity(newMonster);
}

std::pair<int, int> GameState::getSpawnPosition(int monsterType) {
  std::unordered_map<std::string, float>& unorderSpawnPos =
      config.getValues(config.spawnStrByMonsterType(monsterType));
  std::map<std::string, float> spawnPositions(unorderSpawnPos.begin(),
                                              unorderSpawnPos.end());

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> location(0, (spawnPositions.size()/2) - 1);
  int locationPos = location(gen);

  // El X e Y se dan como dos pares (clave,valor) consecutivos en el map
  std::map<std::string,float>::iterator it=spawnPositions.begin();
  for (int i = 0; it!=spawnPositions.end() && i<(locationPos * 2); ++it) {
    i++;
  }
  int spawnX = spawnPositions[it->first];
  it++;
  int spawnY = spawnPositions[it->first];

  return std::make_pair(spawnX, spawnY);
}

void GameState::sendState(int id) {
  std::vector<uint32_t> sendable;
  for (auto& ent : entities) {
    if ((ent.second)->getId() != id) {
      sendable = std::move((ent.second)->getSendable());
      listener.updateUserWorldState(id, sendable);
    }
  }
  for (auto& npc : npcs) {
    sendable = std::move((npc.second)->getSendable());
    listener.updateUserWorldState(id, sendable);
  }
  for (auto& item : droppedItems) {
    sendable = std::move((item.second)->getSendable());
    std::pair<int, int> position = itemsPositions[item.second->getId()];
    sendable.push_back(position.first);
    sendable.push_back(position.second);
    listener.updateUserWorldState(id, sendable);
  }
}

void GameState::spawnUnParDeMobs() {
  Monster* newSpider = factory.newSpider(4000, 2550, *this);
  entities[newSpider->getId()] = newSpider;
  Monster* newZombie = factory.newZombie(3801, 2540, *this);
  entities[newZombie->getId()] = newZombie;
  listener.npcSpawn(newSpider->getId(), newSpider->getNpcType(),
                    newSpider->getX(), newSpider->getY());
  listener.npcSpawn(newZombie->getId(), newZombie->getNpcType(),
                    newZombie->getX(), newZombie->getY());
}

void GameState::rmPlayer(int id) {
  std::unique_lock<std::mutex> l(entitiesMapMutex);
  entities.erase(id);
  players.erase(id);
}

void GameState::rmEntity(int id) {
  std::unique_lock<std::mutex> l(entitiesMapMutex);
  entities.erase(id);
}

bool GameState::isNpc(int id) { return npcs.find(id) != npcs.end(); }

bool GameState::isPlayer(int id) { return players.find(id) != players.end(); }

bool GameState::isDroppedItem(int id) {
  return droppedItems.find(id) != droppedItems.end();
}

NPC* GameState::getNpc(int id) {
  if (npcs.find(id) != npcs.end()) {
    return npcs[id];
  }
  return nullptr;
}

void GameState::addUsernameId(std::string& user, int id) {
  std::unique_lock<std::mutex> l(usrIdMutex);
  usrToId[user] = id;
}

void GameState::rmUsrId(std::string& user) {
  std::unique_lock<std::mutex> l(usrIdMutex);
  usrToId.erase(user);
}

int GameState::getIdByUsername(std::string& username) {
  std::unique_lock<std::mutex> l(usrIdMutex);
  if (usrToId.find(username) == usrToId.end()) {
    return -1;
  }
  return usrToId[username];
}

void GameState::addIdUsername(int id, std::string& user) {
  std::unique_lock<std::mutex> l(idUsrMutex);
  idToUsr[id] = user;
}

std::string GameState::getUsernameById(int id) {
  std::unique_lock<std::mutex> l(idUsrMutex);
  if (idToUsr.find(id) == idToUsr.end()) {
    return "";
  }
  return idToUsr[id];
}

void GameState::rmIdUsr(int id) {
  std::unique_lock<std::mutex> l(idUsrMutex);
  idToUsr.erase(id);
}

void GameState::init() {
  initNPCs();
  initMobs();
}

void GameState::initNPCs() {
  std::unordered_map<std::string, float> city1 =
      config.getValues("npcsCiudad1");
  Merchant* mer1 =
      factory.createMerchant(city1["merchantX"], city1["merchantY"]);
  Priest* pri1 = factory.createPriest(city1["priestX"], city1["priestY"]);
  Banker* bank1 = factory.createBanker(city1["bankerX"], city1["bankerY"]);
  npcs[mer1->getId()] = mer1;
  npcs[pri1->getId()] = pri1;
  npcs[bank1->getId()] = bank1;

  std::unordered_map<std::string, float> city2 =
      config.getValues("npcsCiudad2");
  Merchant* mer2 =
      factory.createMerchant(city2["merchantX"], city2["merchantY"]);
  Priest* pri2 = factory.createPriest(city2["priestX"], city2["priestY"]);
  Banker* bank2 = factory.createBanker(city2["bankerX"], city2["bankerY"]);
  npcs[mer2->getId()] = mer2;
  npcs[pri2->getId()] = pri2;
  npcs[bank2->getId()] = bank2;

  std::unordered_map<std::string, float> city3 =
      config.getValues("npcsCiudad3");
  Merchant* mer3 =
      factory.createMerchant(city3["merchantX"], city3["merchantY"]);
  Priest* pri3 = factory.createPriest(city3["priestX"], city3["priestY"]);
  Banker* bank3 = factory.createBanker(city3["bankerX"], city3["bankerY"]);
  npcs[mer3->getId()] = mer3;
  npcs[pri3->getId()] = pri3;
  npcs[bank3->getId()] = bank3;
}

void GameState::initMobs() {
  for (auto& mob: maxNPCsAmount) {
    for (int i = 0; i < mob.second; i++) {
      generateMonsterType(std::stoi(mob.first));
    }
  }
  for (auto& mob: entities) {
    for (int i = 0; i < config.getConfigValue("initialWandering"); i++) {
      (static_cast<Monster*>(mob.second))->moveRandom();
    }
  }
}

void GameState::dropItem(Item* item, int x, int y) {
  droppedItems[item->getId()] = item;
  itemsPositions[item->getId()] = std::make_pair(x, y);
  listener.dropSpawn(item->getId(), item->getItemType(), x, y);
}

Item* GameState::getCloseItem(int x, int y) {
  Item* nearest = nullptr;
  float distance;
  float smallestDistance = std::numeric_limits<float>::infinity();
  for (auto& it : itemsPositions) {
    int dist_x = abs(x - it.second.first);
    int dist_y = abs(y - it.second.second);
    distance = sqrt(pow(dist_x, 2) + pow(dist_y, 2));

    if (distance < smallestDistance) {
      nearest = droppedItems[it.first];
      smallestDistance = distance;
    }
  }
  if (smallestDistance < TAKE_RANGE) {
    return nearest;
  }
  return nullptr;
}

void GameState::rmItem(int id) {
  droppedItems.erase(id);  // No fallan si no existe
  itemsPositions.erase(id);
}

void GameState::generateDrop(int x, int y, int goldAmount) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> drop(1, 10);
  int is_drop = drop(gen);

  if (is_drop <= 3) {  // 30%
    std::uniform_int_distribution<> distr(1, 19);
    int rand_val = distr(gen);  // Valor random
    Item* item = factory.createItem(rand_val);
    droppedItems[item->getId()] = item;
    itemsPositions[item->getId()] = std::make_pair(x, y);
    listener.dropSpawn(item->getId(), item->getItemType(), x, y);
  } else if (is_drop > 3 && is_drop <= 8) {  // 50%
    GoldDrop* gold = factory.createDroppableGold(goldAmount);
    droppedItems[gold->getId()] = gold;
    itemsPositions[gold->getId()] = std::make_pair(x, y);
    listener.dropSpawn(gold->getId(), gold->getItemType(), x, y);
  }
}

GoldDrop* GameState::generateDroppableGold(int goldAmount) {
  return factory.createDroppableGold(goldAmount);
}

std::pair<int, int> GameState::generateNewMonsterPosition() {
  int randX;
  int randY;
  bool validPosition = false;
  while (!validPosition) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> posX(1, 9900);

    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> posY(1, 7100);
    randX = posX(gen);
    randY = posY(gen2);

    validPosition =
        isValidPosition(randX, randY) && !isCityPosition(randX, randY);
  }
  return std::make_pair(randX, randY);
}

Monster* GameState::generateRandomMonster(int x, int y) {
  Monster* monst;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(1, 4);
  int rand_val = distr(gen);
  switch (rand_val) {
    case 1:
      monst = factory.newGoblin(x, y, *this);
      break;

    case 2:
      monst = factory.newSkeleton(x, y, *this);
      break;

    case 3:
      monst = factory.newSpider(x, y, *this);
      break;

    case 4:
      monst = factory.newZombie(x, y, *this);
      break;
  }
  return monst;
}

bool GameState::isEntitiy(int id) {
  return entities.find(id) != entities.end();
}

void GameState::persist() {
  Persistor persistor;
  for (auto& player : players) {
    std::string username = this->getUsernameById(player.second->getId());
    persistor.persistPlayer(player.second->getData(), username);
    for (auto& npc : npcs) {
      if ((npc.second)->getNpcType() == BANKER_TYPE) {
        Banker* banker = (Banker*)(npc.second);
        persistor.persistBank(std::move(banker->getData()));
      }
    }
  }
}

bool GameState::isPlayerConnected(std::string& username) {
  std::unique_lock<std::mutex> l(idUsrMutex);
  return usrToId.find(username) != usrToId.end();
}

void GameState::decreaseMonsterAmount(int type) {
  currentNPCsAmount[std::to_string(type)]--;
}
