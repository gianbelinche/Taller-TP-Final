#ifndef CLASS_GRAPHIC_INVENTORY
#define CLASS_GRAPHIC_INVENTORY

#include <map>
#include <string>
#include <vector>
#include "FilteredImage.h"
#include "Image.h"

class GraphicInventory {
private:
    SDL_Renderer* mainRenderer;
    std::map<std::string,FilteredImage> images;
    std::vector<std::string> present_images;
    Image itemBoxes;
    std::map<std::string,int> image_positions;
    std::vector<std::string> selected;
    void insert(std::string key,std::string path,int position);
    void renderSelected(int screen_w,int screen_h);
public:
    GraphicInventory(SDL_Renderer* mainRenderer);
    void addImage(std::string key);
    void removeImage(std::string key);
    void render(int screen_width,int screen_heigth);
    void select(std::string key);

};

#endif
