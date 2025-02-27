#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <map>
#include <unordered_map>
#include <mutex>
#include <list>
#include <SDL2/SDL.h>
#include "Entity.h"
#include "Player.h"
#include "NPC.h"
#include "Mob.h"
#include "Camera.h"
#include "Item.h"
#include "Equippable.h"
#include "Attack.h"

class EntityManager {
    private:
        uint32_t playerID;
        SDL_Renderer *renderer;
        std::unordered_map<uint32_t, Entity*> entities;
        std::list<Attack*> attacks;
        std::mutex mux;
        
    public:
        EntityManager(SDL_Renderer *aRenderer, Player *aPlayer, uint32_t aPlayerID);
        ~EntityManager();

        void addNPC(NPCType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY);
        void addMob(MobType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY);
        void addDrop(ItemType type, uint32_t anID, uint16_t aPosX, uint16_t aPosY);
        void addPlayer(PlayerRace aRace, uint32_t anID, uint16_t aPosX, 
                       uint16_t aPosY, uint8_t aState, EquipType aWeapon,
                       EquipType anArmor, EquipType aShield, 
                       EquipType aHelmet);
        void addAttack(AttackType type, uint16_t aPosX, uint16_t aPosY);
        
        void destroyEntity(uint32_t ID);
        void changeEntityState(uint32_t ID, uint8_t state);
        void changeEntityEquipment(uint32_t ID, EquipType equipType, uint8_t what);

        void moveEntity(uint32_t ID, MovementType moveType);
        void teleportEntity(uint32_t ID, uint16_t posX, uint16_t posY);
        void renderEntities(Camera &camera);
        void renderAttacks(Camera &camera);

        uint32_t checkClickEntities(Camera &camera, uint16_t x, uint16_t y);
        static bool entityComp(Entity* ent1, Entity* ent2);
};

#endif 
