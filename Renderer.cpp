#include "Renderer.h"
#include <unistd.h>

Renderer::Renderer(Camera &aCamera, Player &aPlayer, MainMap &aMainMap, 
                   EntityManager &anEntityManager, SDL_Renderer *aRenderer,
                 Layout &layout, GraphicInventory &inventory, MiniChat &chat,
                 ExpBar &expbar) : 
                                            closed(false), camera(aCamera),
                                            player(aPlayer), mainMap(aMainMap),
                                            entityManager(anEntityManager),
                                            renderer(aRenderer),
                                            layout(layout), 
                                            inventory(inventory),
                                            chat(chat), expbar(expbar) {}

Renderer::~Renderer() {}

void Renderer::run() {
    Uint32 time1 = 0;
    Uint32 time2 = 0;

    while (!closed) {
        time1 = SDL_GetTicks();

        camera.refresh(player.getPosX(), player.getPosY());

        SDL_RenderClear(renderer);

        mainMap.renderTerrain(camera);
        entityManager.renderEntities(camera);
        mainMap.renderStructures(camera);
        layout.render(SCREEN_WIDTH,SCREEN_HEIGHT);
        inventory.render(SCREEN_WIDTH,SCREEN_HEIGHT);
        expbar.render(SCREEN_WIDTH,SCREEN_HEIGHT);
        chat.render(SCREEN_WIDTH,SCREEN_HEIGHT);

        SDL_RenderPresent(renderer);
        
        time2 = SDL_GetTicks();
        if (time2 - time1 < 30) usleep(30000 - (time2 - time1) * 1000);
    }
}

void Renderer::close() {
    std::unique_lock<std::mutex> lk(mux);
    closed = true;
}
