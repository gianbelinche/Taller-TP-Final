#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Thread.h"
#include "Camera.h"
#include "Player.h"
#include "MainMap.h"
#include "EntityManager.h"
#include <mutex>

class Renderer : public Thread {
    private:
        std::mutex mux;
        bool closed;
        Camera &camera;
        Player &player;
        MainMap &mainMap;
        EntityManager &entityManager;
        SDL_Renderer *renderer;

    public:
        Renderer(Camera &aCamera, Player &aPlayer, MainMap &aMainMap, 
                 EntityManager &anEntityManager, SDL_Renderer *aRenderer);
        ~Renderer();

        void run();
        void close();
};

#endif
