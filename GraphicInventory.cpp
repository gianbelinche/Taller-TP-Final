#include "GraphicInventory.h"
#include "SDLError.h"

GraphicInventory::GraphicInventory(SDL_Renderer* mainRenderer) : 
mainRenderer(mainRenderer) {
    this->insert("sword","Layout_graphics/Inventory/espada.png");
    this->insert("axe","Layout_graphics/Inventory/hacha.png");
    this->insert("hammer","Layout_graphics/Inventory/martillo.png");
    this->insert("fresno rod","Layout_graphics/Inventory/vara de fresno.png");
    this->insert("baculo nudoso","Layout_graphics/Inventory/baculo nudoso.png");
    this->insert("baculo engarzado","Layout_graphics/Inventory/baculo engarzado.png");
    this->insert("simple bow","Layout_graphics/Inventory/arco simple.png");
    this->insert("composed bow","Layout_graphics/Inventory/arco compuesto.png");
}

void GraphicInventory::insert(std::string key,std::string path){
    Image image(mainRenderer);
    image.loadFromFile(path);
    images.insert(std::pair<std::string,Image>(key,std::move(image)));
}

void GraphicInventory::addImage(std::string key){
    present_images.push_back(key);
}

void GraphicInventory::removeImage(std::string key){
    std::vector<std::string>::iterator it;
    for (it = present_images.begin(); it != present_images.end(); it++){
        if (*it == key){
            present_images.erase(it);
            break;
        }
    }
}

void GraphicInventory::render(int screen_w,int screen_h,int layout_w, int layout_h){
    int i = 0;
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rQuad = {0,0,screen_w / 22,screen_h / 17}; //ver tamaño
    int x = screen_w - layout_w * 95 / 100;
    int y = screen_h / 10; //ver este num 10
    for (auto& it : present_images){
        images.at(it).render(x,y,&clip,&rQuad);
        i++;
        x += screen_w / 16; //mismo 5 que arriba
        if (i == 5 || i == 10 || i == 15){
            x = screen_w - layout_w * 95 / 100;
            y += screen_h / 14; //mismo 12 que arriba
        }
        if (i > 20){
            throw SDLError("Demasiados objetos en el inventario \n");
        }
    }
}