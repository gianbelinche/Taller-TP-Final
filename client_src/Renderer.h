#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Thread.h"
#include "ModelController.h"
#include "Camera.h"
#include "Player.h"
#include "MainMap.h"
#include "EntityManager.h"
#include <atomic>
#include "Layout.h"
#include "GraphicInventory.h"
#include "MiniChat.h"
#include "ExpBar.h"
#include "LoginScreen.h"

class Renderer : public Thread {
    private:
        std::atomic<bool> closed;
        Camera &camera;
        Player &player;
        MainMap &mainMap;
        EntityManager &entityManager;
        SDL_Renderer *renderer;
        Layout &layout;
        GraphicInventory &inventory;
        MiniChat &chat;
        ExpBar &expbar;
        ModelController &modelController;
        LoginScreen &loginScreen;

    public:
        Renderer(Camera &aCamera, Player &aPlayer, MainMap &aMainMap, 
                 EntityManager &anEntityManager, SDL_Renderer *aRenderer,
                 Layout &aLayout, GraphicInventory &anInventory, 
                 MiniChat &aChat, ExpBar &anExpbar,
                 ModelController &aModelController,
                 LoginScreen &loginScreen);
        ~Renderer();

        Renderer(const Renderer& copy) = delete;

        void run();
};

#endif
