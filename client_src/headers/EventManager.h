#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "BlockingMsgQueue.h"
#include "ClientProtocol.h"
#include "MiniChat.h"
#include "GraphicInventory.h"

class EventManager {
    private:
        bool writing;
        uint32_t playerID;
        BlockingMsgQueue &msgQueue;
        EntityManager &entityManager;
        Camera &camera;
        ClientProtocol &clProtocol;
        MiniChat &chat;
        GraphicInventory &inventory;
        SDL_Event event;

        void checkKeyDown(SDL_Event &event);
        void checkKeyUp(SDL_Event &event);
        void checkClick(SDL_Event &event);
        
    public:
        EventManager(EntityManager &anEntityManager, uint32_t playerID, 
                     BlockingMsgQueue &msgQueue, Camera &aCamera, 
                     ClientProtocol &aClProtocol,MiniChat &chat,
                     GraphicInventory &inventory);
        ~EventManager();

        EventManager(const EventManager& copy) = delete;

        void run();
        void handle(SDL_Event &event);
};

#endif
