#include "EntityManager.h"

EntityManager::EntityManager(SDL_Renderer *aRenderer, Player &aPlayer) : 
                                                        player(aPlayer), 
                                                        renderer(aRenderer) {}

EntityManager::~EntityManager() {}

void EntityManager::addNPC(NPCType type, int anID, int aPosX, int aPosY, 
                              View aView) {
    std::unique_lock<std::mutex> lk(mux);
    switch (type) {
        case SPYDER:
            entities.emplace_back(Spyder(renderer, anID, aPosX, aPosY, aView));
            break;
        
        case SKELETON:
            entities.emplace_back(Skeleton(renderer, anID, aPosX, aPosY, aView));
            break;

        case GOBLIN:
            entities.emplace_back(Goblin(renderer, anID, aPosX, aPosY, aView));
            break;

        case ZOMBIE:
            entities.emplace_back(Zombie(renderer, anID, aPosX, aPosY, aView));
            break;

        case BANKER:
            entities.emplace_back(Banker(renderer, anID, aPosX, aPosY, aView));
            break;

        case MERCHANT:
            entities.emplace_back(Merchant(renderer, anID, aPosX, aPosY, aView));
            break;

        case HEALER:
            entities.emplace_back(Healer(renderer, anID, aPosX, aPosY, aView));
            break;

        default:
            //ERROR, NO EXISTE ESA ENTIDAD, DEBERIA TIRAR ALGUN ERROR
            break;
    }
}

void EntityManager::addDrop(ItemType type, int anID, int aPosX, int aPosY) {
    entities.emplace_back(Item(renderer, anID, aPosX, aPosY, type));
}

void EntityManager::addPlayer() {
    std::unique_lock<std::mutex> lk(mux);
    /*COMPLETAR*/
}

void EntityManager::destroyEntity(int ID) {
    /* ACCEDERA LA ENTIDAD CON ESE ID Y DESTRUIRLA */
}

void EntityManager::refreshEntities() {
    /* FOR DEL HASH CHEQUEANDO SI HAY ALGUNA ENTIDAD DESTRUIDA */
}

void EntityManager::renderEntities(Camera &camera) {
    std::unique_lock<std::mutex> lk(mux);
    for (auto& entity : entities) {
        entity.render(camera);
    }

    player.render(camera);
}
