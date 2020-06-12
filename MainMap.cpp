#include "MainMap.h"

MainMap::MainMap(std::map<uint32_t, std::vector<std::string>> &tiles, 
                 SDL_Renderer *aRenderer, std::vector<std::vector<uint32_t>> aMap)
                 : player(aRenderer), map(std::move(aMap)) {
    this->camera = {player.getPosX(), player.getPosY(), SCREEN_WIDTH, 
                    SCREEN_HEIGHT};
    
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
                                    map(std::move(other.map)),
                                    textures(std::move(other.textures)),
                                    player(std::move(other.player)) {}

MainMap& MainMap::operator=(MainMap&& other) {
    if (this == &other) {
        return *this;
    }

    this->camera = std::move(other.camera);
    this->map = std::move(other.map);
    this->textures = std::move(other.textures);
    this->player = std::move(other.player);

    return *this;
}

void MainMap::render() {
    int x = 0;
    int y = 0;

    for (auto &row : this->map) {
        for (auto &index : row) {
            if (index == 0) {
                x += 32;
                continue;
            }
            int key = index;
            while (this->textures.find(key) == this->textures.end()) {
                key--;
            }
            this->textures.at(key).renderFromTile(index-key, x, y);
            x += 32;
        }
        y += 32;
        x = 0;
    }
}
