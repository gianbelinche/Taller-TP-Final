#include "GraphicInventory.h"
#include "SDLError.h"

GraphicInventory::GraphicInventory(SDL_Renderer* mainRenderer) : 
mainRenderer(mainRenderer), itemBoxes(NULL) {
    Image itemBoxes(mainRenderer);
    itemBoxes.loadFromFile("Layout_graphics/Inventory/ItemBoxes.png");
    this->itemBoxes = std::move(itemBoxes);
    selected.push_back("");
    selected.push_back("");
    selected.push_back("");
    selected.push_back("");
    this->insert("sword","Layout_graphics/Inventory/espada.png",0);
    this->insert("axe","Layout_graphics/Inventory/hacha.png",0);
    this->insert("hammer","Layout_graphics/Inventory/martillo.png",0);
    this->insert("fresno rod","Layout_graphics/Inventory/vara de fresno.png",0);
    this->insert("baculo nudoso","Layout_graphics/Inventory/baculo nudoso.png",0);
    this->insert("baculo engarzado","Layout_graphics/Inventory/baculo engarzado.png",0);
    this->insert("simple bow","Layout_graphics/Inventory/arco simple.png",0);
    this->insert("composed bow","Layout_graphics/Inventory/arco compuesto.png",0);
    this->insert("leather armor","Layout_graphics/Inventory/armadura de cuero.png",1);
    this->insert("plate armor","Layout_graphics/Inventory/armadura de placas.png",1);
    this->insert("iron helmet","Layout_graphics/Inventory/casco de hierro.png",2);
    this->insert("iron shield","Layout_graphics/Inventory/escudo de hierro.png",3);
}

void GraphicInventory::insert(std::string key,std::string path,int position){
    FilteredImage image(mainRenderer);
    image.loadFromFile(path);
    images.insert(std::pair<std::string,FilteredImage>(key,std::move(image)));
    image_positions.insert(std::pair<std::string,int>(key,position));
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
    this->renderSelected(screen_w,screen_h);
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rQuad = {0,0,screen_w / 22,screen_h / 17};
    int i = 0;
    int x = screen_w - layout_w * 95 / 100;
    int y = screen_h / 10; 
    for (auto& it : present_images){
        images.at(it).render(x,y,&clip,&rQuad);
        i++;
        x += screen_w / 16; 
        if (i == 5 || i == 10 || i == 15){
            x = screen_w - layout_w * 95 / 100;
            y += screen_h / 14; 
        }
        if (i > 20){
            throw SDLError("Demasiados objetos en el inventario \n");
        }
    }
}

void GraphicInventory::renderSelected(int screen_w,int screen_h){
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rQuad = {0,0,screen_w / 15,screen_h *3 / 8}; // ver este tamaño
    itemBoxes.render(screen_w * 3 / 5,0,&clip,&rQuad);
    rQuad = {0,0,screen_w / 22,screen_h / 17};
    int x = screen_w * 305 / 500;
    int y = screen_h / 48;
    for (int i = 0; i < 4; i++){
        if (selected[i] != ""){
            images.at(selected[i]).render(x,y,&clip,&rQuad);
        }
        y += screen_h * 104 / 1100;
    }
}

void GraphicInventory::select(std::string key){
    selected[image_positions.at(key)] = key;
}