#include "../headers/EntityManager.h"
#include <algorithm>

EntityManager::EntityManager(SDL_Renderer *aRenderer, Player *aPlayer, uint32_t aPlayerID) :  
                                                        playerID(aPlayerID),
                                                        renderer(aRenderer) {
    entities[playerID] = aPlayer;
}

EntityManager::~EntityManager() {
    for (auto &entity : entities) {
        if (entity.first != playerID) delete(entity.second);
    }
}

void EntityManager::addNPC(NPCType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY) {
    std::unique_lock<std::mutex> lk(mux);
    entities[anID] = new NPC(renderer, type, anID, aPosX, aPosY);
}

void EntityManager::addMob(MobType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY) {
    std::unique_lock<std::mutex> lk(mux);
    entities[anID] = new Mob(renderer, type, anID, aPosX, aPosY);
}

void EntityManager::addDrop(ItemType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY) {
    std::unique_lock<std::mutex> lk(mux);
    entities[anID] = new Item(renderer, type, anID, aPosX, aPosY);
}

void EntityManager::addPlayer(PlayerRace aRace, uint32_t anID, uint16_t aPosX, 
                              uint16_t aPosY, uint8_t aState, EquipType aWeapon,
                              EquipType anArmor, EquipType aShield, 
                              EquipType aHelmet) {
    std::unique_lock<std::mutex> lk(mux);
    entities[anID] = new Player(renderer, aRace, anID, aPosX, aPosY, aState, 
                                aWeapon, anArmor, aShield, aHelmet);
}

void EntityManager::destroyEntity(uint32_t ID) {
    std::unique_lock<std::mutex> lk(mux);
    if (entities.find(ID) == entities.end()) return;
    if (ID != playerID) delete(entities[ID]);
    entities.erase(ID);
}

void EntityManager::changeEntityState(uint32_t ID, uint8_t state) {
    std::unique_lock<std::mutex> lk(mux);
    if (entities.find(ID) == entities.end()) return;
    else entities[ID]->changeState(state);
}

void EntityManager::changeEntityEquipment(uint32_t ID, EquipType equipType, uint8_t what) {
    std::unique_lock<std::mutex> lk(mux);
    if (entities.find(ID) == entities.end()) return;
    else entities[ID]->changeEquipment(equipType, what);
}

void EntityManager::moveEntity(uint32_t ID, MovementType moveType) {
    std::unique_lock<std::mutex> lk(mux);
    if (entities.find(ID) == entities.end()) return;
    else entities[ID]->refreshPosition(moveType);
}

void EntityManager::teleportEntity(uint32_t ID, uint16_t posX, uint16_t posY) {
    std::unique_lock<std::mutex> lk(mux);
    if (entities.find(ID) == entities.end()) return;
    else entities[ID]->teleportTo(posX, posY);
}

bool EntityManager::entityComp (Entity* ent1, Entity* ent2) { 
    return (ent1->getPosY() < ent2->getPosY());
}

void EntityManager::renderEntities(Camera &camera) {
    std::unique_lock<std::mutex> lk(mux);

    std::vector<Entity*> entitiesRender;

    for (auto& entity : entities) {
        entitiesRender.push_back(entity.second);
    }

    std::sort(entitiesRender.begin(), entitiesRender.end(), 
              EntityManager::entityComp);

    for (auto& entityRender : entitiesRender) {
        entityRender->render(camera);
    }
}

uint32_t EntityManager::checkClickEntities(Camera &camera, uint16_t x, uint16_t y) {
    std::unique_lock<std::mutex> lk(mux);
    uint16_t xCam = camera.getX();
    uint16_t yCam = camera.getY();

    for (auto &entity : entities) {
        if (entity.second->collision(x + xCam, y + yCam)) {
            return entity.first;
        }
    }

    return 0;
}
