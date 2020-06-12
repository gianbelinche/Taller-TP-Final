#ifndef __MAIN_MAP_H__
#define __MAIN_MAP_H__

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "MapImage.h"
#include "Player.h"

/* TAMAÑO DE LA PANTALLA */
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define CHARACTER_POSITION_X 0
#define CHARACTER_POSITION_Y 0

class MainMap {
    private:
        SDL_Rect camera;
        std::map<uint32_t, MapImage> textures;
        std::vector<std::vector<uint32_t>> map;
        Player player;
        
    public:
        MainMap(std::map<uint32_t, std::vector<std::string>> &tiles, 
                SDL_Renderer *aRenderer, std::vector<std::vector<uint32_t>> aMap);
        ~MainMap();

        MainMap(const MainMap &copy) = delete;
        MainMap(MainMap&& other);
        MainMap& operator=(MainMap&& other);

        void render();
};

#endif
