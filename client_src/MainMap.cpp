#include "MainMap.h"

#define CITY_1 (x >= 4800 && x < 6528 && y >= 1376 && y < 3744)
#define CITY_2 (x >= 1568 && x < 3264 && y >= 5376 && y < 6656)
#define CITY_3 (x >= 5472 && x < 9088 && y >= 4512 && y < 7104)
#define DESERT (x >= 0    && x < 5472 && y >= 1376 && y < 7104)
#define CAVE   (x >= 0    && x < 6528 && y >= 0    && y < 1376)
#define FOREST (x >= 6528 && x < 9088 && y >= 0    && y < 4512)

MainMap::MainMap(std::map<uint32_t, std::vector<std::string>> &tiles, 
                 SDL_Renderer *aRenderer, std::vector<std::vector<uint32_t>> aTexMap,
                 std::vector<std::vector<uint32_t>> aStrMap)
                 : texMap(std::move(aTexMap)), strMap(std::move(aStrMap)) {
    for (auto& obj : tiles) {
        int tileWidth = std::stoi(obj.second.back());
        obj.second.pop_back();
        int tileHeight = std::stoi(obj.second.back());
        obj.second.pop_back();
        std::string source = obj.second.back();
        MapImage mImg(aRenderer, source, tileHeight, tileWidth);
        textures.emplace(obj.first, std::move(mImg));
    }
}

MainMap::~MainMap() {}

MainMap::MainMap(MainMap&& other) : texMap(std::move(other.texMap)),
                                    strMap(std::move(other.strMap)),
                                    textures(std::move(other.textures)) {}

MainMap& MainMap::operator=(MainMap&& other) {
    if (this == &other) {
        return *this;
    }

    this->texMap = std::move(other.texMap);
    this->strMap = std::move(other.strMap);
    this->textures = std::move(other.textures);

    return *this;
}

void MainMap::renderTerrain(Camera &camera) {
    int x = 0 - camera.getX();
    int y = 0 - camera.getY();

    for (auto &row : this->texMap) {
        for (auto &index : row) {
            if (!(x < -96 || x > (camera.getWidth() + 96) || y < -96 || y > (camera.getHeight() + 96) || index == 0)) {
                int key = index;
                while (this->textures.find(key) == this->textures.end()) {
                    key--;
                }
                this->textures.at(key).renderFromTile(index-key, x, y);
                
            }
            x += 32;
        }
        y += 32;
        x = 0 - camera.getX();
    }
}

void MainMap::renderStructures(Camera &camera) {
    int x = 0 - camera.getX();
    int y = 0 - camera.getY();

    for (auto &row : this->strMap) {
        for (auto &index : row) {
            if (!(x < -96 || x > (camera.getWidth() + 96) || y < -96 || y > (camera.getHeight() + 96) || index == 0)) {
                int key = index;
                while (this->textures.find(key) == this->textures.end()) {
                    key--;
                }
                this->textures.at(key).renderFromTile(index-key, x, y);
            }
            x += 32;
        }
        y += 32;
        x = 0 - camera.getX();
    }
}

uint8_t MainMap::getZone(uint16_t x, uint16_t y) {
    if (CITY_1 || CITY_2 || CITY_3) {
        return 0;
    } else if (DESERT) {
        return 1;
    } else if (FOREST) {
        return 2;
    } else if (CAVE) {
        return 3;
    }
}
