#ifndef CLASS_GRAPHIC_INVENTORY
#define CLASS_GRAPHIC_INVENTORY

#include <map>
#include <string>
#include <vector>
#include "FilteredImage.h"
#include "Image.h"
#include "Camera.h"

class GraphicInventory {
private:
    SDL_Renderer* mainRenderer;
    std::map<int,FilteredImage> images;
    std::vector<int> present_images;
    Image itemBoxes;
    std::map<int,int> image_positions;
    std::vector<int> equiped;
    void insert(int key,std::string path,int position);
    void renderEquiped(int screen_w,int screen_h);
public:
    GraphicInventory(SDL_Renderer* mainRenderer);

    void addImage(int key);
    void removeImage(int pos);
    void equip(int key);
    int select(int x,int y,Camera& camera);
    void render(Camera& camera);
};

#endif
