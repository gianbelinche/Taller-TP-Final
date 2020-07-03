#include "EntityManager.h"

EntityManager::EntityManager(SDL_Renderer *aRenderer, Player &aPlayer, uint32_t aPlayerID) : 
                                                        playerID(aPlayerID),
                                                        player(aPlayer), 
                                                        renderer(aRenderer) {}

EntityManager::~EntityManager() {
    for (auto &entity : entities) {
        delete(entity.second);
    }
}

void EntityManager::addNPC(NPCType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY) {
    std::unique_lock<std::mutex> lk(mux);
    switch (type) {
        case SPYDER:
            entities[anID] = new Spyder(renderer, anID, aPosX, aPosY);
            break;
        
        case SKELETON:
            entities[anID] = new Skeleton(renderer, anID, aPosX, aPosY);
            break;

        case GOBLIN:
            entities[anID] = new Goblin(renderer, anID, aPosX, aPosY);
            break;

        case ZOMBIE:
            entities[anID] = new Zombie(renderer, anID, aPosX, aPosY);
            break;

        case BANKER:
            entities[anID] = new Banker(renderer, anID, aPosX, aPosY);
            break;

        case MERCHANT:
            entities[anID] = new Merchant(renderer, anID, aPosX, aPosY);
            break;

        case HEALER:
            entities[anID] = new Healer(renderer, anID, aPosX, aPosY);
            break;

        default:
            break;
    }
}

void EntityManager::addDrop(ItemType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY) {
    std::unique_lock<std::mutex> lk(mux);
    entities[anID] = new Item(renderer, anID, aPosX, aPosY, type);
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
    delete(entities[ID]);
    entities.erase(ID);
}

void EntityManager::changeEntityState(uint32_t ID, uint8_t state) {
    std::unique_lock<std::mutex> lk(mux);
    if (ID == playerID) player.changeState(state);
    entities[ID]->changeState(state);
}

void EntityManager::changeEntityEquipment(uint32_t ID, EquipType equipType, uint8_t what) {
    std::unique_lock<std::mutex> lk(mux);
    if (ID == playerID) player.changeEquipment(equipType, what);
    entities[ID]->changeEquipment(equipType, what);
}

void EntityManager::moveEntity(uint32_t ID, MovementType moveType) {
    std::unique_lock<std::mutex> lk(mux);
    if (ID == playerID) player.refreshPosition(moveType);
    else entities[ID]->refreshPosition(moveType);
}

void EntityManager::renderEntities(Camera &camera) {
    std::unique_lock<std::mutex> lk(mux);

    std::map<uint32_t, Entity*> entitiesRender;

    for (auto& entity : entities) {
        entitiesRender[entity.second->getPosY()] = entity.second;
    }

    for (auto& entityRender : entitiesRender) {
        entityRender.second->render(camera);
    }

    player.render(camera);
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
