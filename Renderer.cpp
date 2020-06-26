#include "Renderer.h"

Renderer::Renderer() : closed(false) {}

Renderer::~Renderer() {}

void Renderer::run() {
    Uint32 time1 = 0;
    Uint32 time2 = 0;

    while (!closed) {
        time1 = SDL_GetTicks();

        camera.refresh(player.getPosX(), player.getPosY());

        SDL_RenderClear(mainRenderer);

        mainMap.renderTerrain(camera);
        entMan.renderEntities(camera);
        mainMap.renderStructures(camera);

        SDL_RenderPresent(mainRenderer);
        
        time2 = SDL_GetTicks();
        if (time2 - time1 < 25) usleep(25000 - (time2 - time1) * 1000); //33 ms para 30 fps
    }
}

void Renderer::close() {
    std::unique_lock<std::mutex> lk(mux);
    closed = true;
}
