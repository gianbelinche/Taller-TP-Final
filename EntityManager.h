#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <map>
#include <mutex>
#include <SDL2/SDL.h>
#include "Entity.h"
#include "Player.h"
#include "NPC.h"
#include "Spyder.h"
#include "Skeleton.h"
#include "Goblin.h"
#include "Zombie.h"
#include "Merchant.h"
#include "Banker.h"
#include "Healer.h"
#include "Camera.h"
#include "Item.h"

class EntityManager {
    private:
        Player &player;
        uint32_t playerID;
        SDL_Renderer *renderer;
        std::map<uint32_t, Entity*> entities;
        std::map<uint32_t, Entity*> entitiesRender;
        std::mutex mux;
        
    public:
        EntityManager(SDL_Renderer *aRenderer, Player &aPlayer, uint32_t aPlayerID);
        ~EntityManager();

        void addNPC(NPCType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY, View aView);
        void addDrop(ItemType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY);
        void addPlayer(PlayerRace aRace, uint32_t anID, uint16_t aPosX, uint16_t aPosY);
        
        void destroyEntity(uint32_t ID);
        void refreshEntities();

        void moveEntity(uint32_t ID, MovementType moveType);
        void renderEntities(Camera &camera);

        uint32_t checkClickEntities(Camera &camera, uint16_t x, uint16_t y);
};

#endif 
