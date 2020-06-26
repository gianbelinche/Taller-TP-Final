#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <SDL2/SDL.h>
#include "EntityManager.h"
#include "MessageQueue.h"

class EventManager {
    private:
        bool writing;
        uint32_t playerID;
        MessageQueue &msgQueue;
        EntityManager &entityManager;
        SDL_Event event;

        void checkKeyDown(SDL_Event &event);
        void checkKeyUp(SDL_Event &event);
        void checkClick(SDL_Event &event);
        
    public:
        EventManager(EntityManager &anEntityManager, uint32_t playerID, 
                     MessageQueue &msgQueue);
        ~EventManager();

        EventManager(const EventManager& copy) = delete;

        void run();
        void handle(SDL_Event &event);
};

#endif
