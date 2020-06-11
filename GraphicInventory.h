#ifndef CLASS_GRAPHIC_INVENTORY
#define CLASS_GRAPHIC_INVENTORY

#include <map>
#include <string>
#include <vector>
#include "FilteredImage.h"

class GraphicInventory {
private:
    SDL_Renderer* mainRenderer;
    std::map<std::string,FilteredImage> images;
    std::map<std::string,Image> images;
    std::vector<std::string> present_images;
    void insert(std::string key,std::string path);
public:
    GraphicInventory(SDL_Renderer* mainRenderer);
    void addImage(std::string key);
    void removeImage(std::string key);
    void render(int screen_width,int screen_heigth,int layout_w, int layout_h);

};

#endif
