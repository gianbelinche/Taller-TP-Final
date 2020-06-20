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

void EntityManager::addNPC(NPCType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY, 
                              View aView) {
    std::unique_lock<std::mutex> lk(mux);
    /*DEBERIA ARMAR TAMBIEN EL OTRO HASH PARA RENDERIZAR EN ORDEN*/
    switch (type) {
        case SPYDER:
            entities[anID] = new Spyder(renderer, anID, aPosX, aPosY, aView);
            break;
        
        case SKELETON:
            entities[anID] = new Skeleton(renderer, anID, aPosX, aPosY, aView);
            break;

        case GOBLIN:
            entities[anID] = new Goblin(renderer, anID, aPosX, aPosY, aView);
            break;

        case ZOMBIE:
            entities[anID] = new Zombie(renderer, anID, aPosX, aPosY, aView);
            break;

        case BANKER:
            entities[anID] = new Banker(renderer, anID, aPosX, aPosY, aView);
            break;

        case MERCHANT:
            entities[anID] = new Merchant(renderer, anID, aPosX, aPosY, aView);
            break;

        case HEALER:
            entities[anID] = new Healer(renderer, anID, aPosX, aPosY, aView);
            break;

        default:
            //ERROR, NO EXISTE ESA ENTIDAD, DEBERIA TIRAR ALGUN ERROR
            break;
    }
}

void EntityManager::addDrop(ItemType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY) {
    entities[anID] = new Item(renderer, anID, aPosX, aPosY, type);
}

void EntityManager::addPlayer(PlayerRace aRace, uint32_t anID, uint16_t aPosX, uint16_t aPosY) {
    std::unique_lock<std::mutex> lk(mux);
    entities[anID] = new Player(renderer, aRace, anID, aPosX, aPosY);
}

void EntityManager::destroyEntity(uint32_t ID) {
    std::unique_lock<std::mutex> lk(mux);
    entities[ID]->destroy();
}

void EntityManager::refreshEntities() {
    std::unique_lock<std::mutex> lk(mux);
    for (auto& entity : entities) {
        if (entity.second->isDestroyed()) {
            entities.erase(entity.first);
        }
    }
}

void EntityManager::moveEntity(uint32_t ID, MovementType moveType) {
    std::unique_lock<std::mutex> lk(mux); //necesario??
    if (ID == playerID) player.refreshPosition(moveType);
    else entities[ID]->refreshPosition(moveType);
}

void EntityManager::renderEntities(Camera &camera) {
    std::unique_lock<std::mutex> lk(mux);
    for (auto& entity : entities) {
        entity.second->render(camera);
    }

    player.render(camera);
}

uint32_t EntityManager::checkClickEntities(Camera &camera, uint16_t x, uint16_t y) {
    std::unique_lock<std::mutex> lk(mux); //necesario??
    uint16_t xCam = camera.getX();
    uint16_t yCam = camera.getY();

    for (auto &entity : entities) {
        if (entity.second->collision(x + xCam, y + yCam)) {
            return entity.second->getID();
        }
    }
}
