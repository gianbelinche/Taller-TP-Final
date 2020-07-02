#include "Renderer.h"
#include "QueueClosedException.h"
#include <unistd.h>
#include <iostream>

Renderer::Renderer(Camera &aCamera, Player &aPlayer, MainMap &aMainMap, 
                   EntityManager &anEntityManager, SDL_Renderer *aRenderer,
                   Layout &aLayout, GraphicInventory &anInventory, 
                   MiniChat &aChat, ExpBar &anExpbar, 
                   ModelController &aModelController,
                   LoginScreen &loginScreen) : 
                                            closed(false), camera(aCamera),
                                            player(aPlayer), mainMap(aMainMap),
                                            entityManager(anEntityManager),
                                            renderer(aRenderer), 
                                            layout(aLayout), 
                                            inventory(anInventory), chat(aChat),
                                            expbar(anExpbar), 
                                            modelController(aModelController),
                                            loginScreen(loginScreen) {}

Renderer::~Renderer() {}

void Renderer::run() {
    try {
        Uint32 time1 = 0;
        Uint32 time2 = 0;

        int cont = 0;

        while (!closed) {
            time1 = SDL_GetTicks();

            modelController.run(closed); //chequear

            camera.refresh(player.getPosX(), player.getPosY());

            SDL_RenderClear(renderer);

            if (loginScreen.is_active()){
                loginScreen.render(camera);
            } else {
                mainMap.renderTerrain(camera);
                entityManager.renderEntities(camera);
                mainMap.renderStructures(camera);
                layout.render(camera);
                inventory.render(camera);
                expbar.render(camera);
                chat.render(camera);
            }

            SDL_RenderPresent(renderer);
            
            time2 = SDL_GetTicks();
            if (time2 - time1 < 30) usleep(30000 - ((time2 - time1) * 1000));
        }
    } catch (const QueueClosedException &e) {
    } catch(const std::exception& e) {
        std::cerr << "Render: ";
        std::cerr << e.what() << '\n';
        modelController.closeQueue();
    } catch(...) {
        std::cerr << "Render: ";
        std::cerr << "Error Renderer: unknown" << '\n';
        modelController.closeQueue();
    }
}
