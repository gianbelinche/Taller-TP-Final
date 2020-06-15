#ifndef __MAIN_MAP_H__
#define __MAIN_MAP_H__

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "MapImage.h"
#include "Player.h"

/* TAMAÑO DE LA PANTALLA */
#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 1080
#endif
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 720
#endif
#define CHARACTER_POSITION_X 0
#define CHARACTER_POSITION_Y 0

#define LEVEL_WIDTH 9056
#define LEVEL_HEIGHT 7392

class MainMap {
    private:
        SDL_Rect camera;
        std::map<uint32_t, MapImage> textures;
        std::vector<std::vector<uint32_t>> texMap;
        std::vector<std::vector<uint32_t>> strMap;
        Player player;
        
    public:
        MainMap(std::map<uint32_t, std::vector<std::string>> &tiles, 
                SDL_Renderer *aRenderer, std::vector<std::vector<uint32_t>> aTexMap,
                std::vector<std::vector<uint32_t>> aStrMap);
        ~MainMap();

        MainMap(const MainMap &copy) = delete;
        MainMap(MainMap&& other);
        MainMap& operator=(MainMap&& other);

        void handleEvent(SDL_Event &event);
        void render();
};

#endif
