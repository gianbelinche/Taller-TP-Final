#include "MainMap.h"

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
    /*uint32_t key = 0;
    uint32_t index = 0;

    for (int y = -64, posY = camera.getY() - 64; y < camera.getHeight() + 64; y += 32, posY += 32) {
        for (int x = -64, posX = camera.getX() - 64; x < camera.getWidth() + 64; x += 32, posX += 32) {
            std::vector<uint32_t> *r = &texMap[posY/32];
            index = (*r)[posX/32];
            if (!index) continue;
            key = index;
            while (this->textures.find(key) == this->textures.end()) {
                key--;
            }
            this->textures.at(key).renderFromTile(index-key, x, y);
        }
    }*/
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
    /*uint32_t key = 0;
    uint32_t index = 0;

    for (int y = -64, posY = camera.getY() - 64; y < camera.getHeight() + 64; y += 32, posY += 32) {
        for (int x = -64, posX = camera.getX() - 64; x < camera.getWidth() + 64; x += 32, posX += 32) {
            std::vector<uint32_t> *r = &strMap[posY/32];
            index = (*r)[posX/32];
            if (!index) continue;
            key = index;
            while (this->textures.find(key) == this->textures.end()) {
                key--;
            }
            this->textures.at(key).renderFromTile(index-key, x, y);
        }
    }*/

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
