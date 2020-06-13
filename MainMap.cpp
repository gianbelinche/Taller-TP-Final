#include "MainMap.h"

MainMap::MainMap(std::map<uint32_t, std::vector<std::string>> &tiles, 
                 SDL_Renderer *aRenderer, std::vector<std::vector<uint32_t>> aTexMap,
                 std::vector<std::vector<uint32_t>> aStrMap)
                 : player(aRenderer), texMap(std::move(aTexMap)), strMap(std::move(aStrMap)) {
    camera.x = (player.getPosX() + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = (player.getPosY() + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;
    camera.h = SCREEN_HEIGHT;
    camera.w = SCREEN_WIDTH;

    if (camera.x < 0) {
            camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    
    for (auto& v : tiles) {
        int tileWidth = std::stoi(v.second.back());
        v.second.pop_back();
        int tileHeight = std::stoi(v.second.back());
        v.second.pop_back();
        std::string source = v.second.back();
        MapImage mImg(aRenderer, source, tileHeight, tileWidth);
        textures.emplace(v.first, std::move(mImg));
    }
}

MainMap::~MainMap() {}

MainMap::MainMap(MainMap&& other) : camera(std::move(other.camera)),
                                    texMap(std::move(other.texMap)),
                                    strMap(std::move(other.strMap)),
                                    textures(std::move(other.textures)),
                                    player(std::move(other.player)) {}

MainMap& MainMap::operator=(MainMap&& other) {
    if (this == &other) {
        return *this;
    }

    this->camera = std::move(other.camera);
    this->texMap = std::move(other.texMap);
    this->strMap = std::move(other.strMap);
    this->textures = std::move(other.textures);
    this->player = std::move(other.player);

    return *this;
}

void MainMap::handleEvent(SDL_Event &event) {
    if ((event.type == SDL_KEYDOWN) || (event.type == SDL_KEYUP)) {
        player.move(event);
    }
}

void MainMap::render() {

    camera.x = (player.getPosX() + PLAYER_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = (player.getPosY() + PLAYER_HEIGHT / 2) - SCREEN_HEIGHT / 2;

    if (camera.x < 0) {
            camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }/*
    if (camera.x > LEVEL_WIDTH - camera.w) {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h) {
        camera.y = LEVEL_HEIGHT - camera.h;
    }*/

    int x = 0 - camera.x;
    int y = 0 - camera.y;

    for (auto &row : this->texMap) {
        for (auto &index : row) {
            if (!(x < -96 || x > (SCREEN_WIDTH + 96) || y < -96 || y > (SCREEN_HEIGHT + 96) || index == 0)) {
                int key = index;
                while (this->textures.find(key) == this->textures.end()) {
                    key--;
                }
                this->textures.at(key).renderFromTile(index-key, x, y);
                
            }
            x += 32;
        }
        y += 32;
        x = 0 - camera.x;
    }

    player.render(camera.x, camera.y);

    x = 0 - camera.x;
    y = 0 - camera.y;

    for (auto &row : this->strMap) {
        for (auto &index : row) {
            if (!(x < -96 || x > (SCREEN_WIDTH + 96) || y < -96 || y > (SCREEN_HEIGHT + 96) || index == 0)) {
                int key = index;
                while (this->textures.find(key) == this->textures.end()) {
                    key--;
                }
                this->textures.at(key).renderFromTile(index-key, x, y);
            }
            x += 32;
        }
        y += 32;
        x = 0 - camera.x;
    }
}
