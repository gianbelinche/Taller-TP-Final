#ifndef __MAIN_MAP_H__
#define __MAIN_MAP_H__

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "MapImage.h"
#include "Player.h"
#include "Camera.h"

class MainMap {
    private:
        std::map<uint32_t, MapImage> textures;
        std::vector<std::vector<uint32_t>> texMap;
        std::vector<std::vector<uint32_t>> strMap;
        
    public:
        MainMap(std::map<uint32_t, std::vector<std::string>> &tiles, 
                SDL_Renderer *aRenderer, std::vector<std::vector<uint32_t>> aTexMap,
                std::vector<std::vector<uint32_t>> aStrMap);
        ~MainMap();

        MainMap(const MainMap &copy) = delete;
        MainMap(MainMap&& other);
        MainMap& operator=(MainMap&& other);

        void renderTerrain(Camera &camera);
        void renderStructures(Camera &camera);
        uint8_t getZone(uint16_t x, uint16_t y);
};

#endif
