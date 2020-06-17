#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <vector>
#include <mutex>
#include <SDL2/SDL.h>
#include "Player.h"
#include "Entity.h"
#include "Spyder.h"
#include "Skeleton.h"
#include "Goblin.h"
#include "Zombie.h"
#include "Merchant.h"
#include "Banker.h"
#include "Healer.h"

/* Entidades añadibles */
enum EntityType {SPYDER, SKELETON, GOBLIN, ZOMBIE, BANKER, MERCHANT, HEALER}; //agregar los drops

class EntityManager {
    private:
        Player &player;
        SDL_Renderer *renderer;
        std::vector<Entity> entities;
        std::mutex mux;
        
    public:
        EntityManager(SDL_Renderer *aRenderer, Player &aPlayer);
        ~EntityManager();

        /*
        ESTO SE PUEDE HACER ASI O SE PUEDE PEDIR QUE SE
        PASE EL COMANDO ENVIADO POR EL SERVIDOR
        Y DECODIFICARLO ADENTRO
        */
        void addEntity(EntityType type, int anID, int aPosX, int aPosY,
                       View aView);
        void addPlayer();

        void renderEntities(SDL_Rect &camera);
};

#endif 
