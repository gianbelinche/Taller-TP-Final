#include "GraphicInventory.h"
#include "SDLError.h"
#define MAX_NUMBER_OF_ITEMS 20
#define NUMBER_OF_COLUMNS 5
#define MAX_NUMBER_OF_SELECTED_ITEMS 4
#define INTERIOR_BOX_W (screen_w / 24)
#define INTERIOR_BOX_H (screen_h / 19)
#define EXTERIOR_BOX_X (screen_w * 1743 / 2550)
#define EXTERIOR_BOX_Y (screen_h / 10)
#define EXTERIOR_BOX_W (screen_w / 16)
#define EXTERIOR_BOX_H (screen_h / 14)
#define ITEM_BOXES_W (screen_w / 15)
#define ITEM_BOXES_H (screen_h *3 / 8)
#define ITEM_BOXES_X (screen_w * 3 / 5)
#define SELECTED_INT_BOX_W (screen_w / 22)
#define SELECTED_INT_BOX_H (screen_h / 17)
#define SELECTED_EXT_BOX_X (screen_w * 305 / 500)
#define SELECTED_EXT_BOX_Y (screen_h / 48)
#define SELECTED_EXT_BOX_H (screen_h * 104 / 1100)
#define SELECTED_TYPE_0 0
#define SELECTED_TYPE_1 1
#define SELECTED_TYPE_2 2
#define SELECTED_TYPE_3 3


GraphicInventory::GraphicInventory(SDL_Renderer* mainRenderer) : 
mainRenderer(mainRenderer), itemBoxes(NULL) {
    Image itemBoxes(mainRenderer);
    itemBoxes.loadFromFile("Layout_graphics/Inventory/ItemBoxes.png");
    this->itemBoxes = std::move(itemBoxes);
    equiped.push_back("");
    equiped.push_back("");
    equiped.push_back("");
    equiped.push_back("");
    this->insert("sword","Layout_graphics/Inventory/espada.png",SELECTED_TYPE_0);
    this->insert("axe","Layout_graphics/Inventory/hacha.png",SELECTED_TYPE_0);
    this->insert("hammer","Layout_graphics/Inventory/martillo.png",SELECTED_TYPE_0);
    this->insert("fresno rod","Layout_graphics/Inventory/vara de fresno.png",SELECTED_TYPE_0);
    this->insert("baculo nudoso","Layout_graphics/Inventory/baculo nudoso.png",SELECTED_TYPE_0);
    this->insert("baculo engarzado","Layout_graphics/Inventory/baculo engarzado.png",SELECTED_TYPE_0);
    this->insert("simple bow","Layout_graphics/Inventory/arco simple.png",SELECTED_TYPE_0);
    this->insert("composed bow","Layout_graphics/Inventory/arco compuesto.png",SELECTED_TYPE_0);
    this->insert("leather armor","Layout_graphics/Inventory/armadura de cuero.png",SELECTED_TYPE_1);
    this->insert("plate armor","Layout_graphics/Inventory/armadura de placas.png",SELECTED_TYPE_1);
    this->insert("iron helmet","Layout_graphics/Inventory/casco de hierro.png",SELECTED_TYPE_2);
    this->insert("iron shield","Layout_graphics/Inventory/escudo de hierro.png",SELECTED_TYPE_3);
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

void GraphicInventory::render(Camera& camera){
    int screen_w = camera.getWidth();
    int screen_h = camera.getHeight();
    this->renderEquiped(screen_w,screen_h);
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rQuad = {0,0,INTERIOR_BOX_W,INTERIOR_BOX_H};
    int i = 0;
    int x = EXTERIOR_BOX_X;
    int y = EXTERIOR_BOX_Y; 
    for (auto& it : present_images){
        images.at(it).render(x,y,&clip,&rQuad);
        i++;
        x += EXTERIOR_BOX_W; 
        if (i % NUMBER_OF_COLUMNS == 0){
            x = EXTERIOR_BOX_X;
            y += EXTERIOR_BOX_H; 
        }
        if (i > MAX_NUMBER_OF_ITEMS){
            throw SDLError("Demasiados objetos en el inventario \n");
        }
    }
}

void GraphicInventory::renderEquiped(int screen_w,int screen_h){
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rQuad = {0,0,ITEM_BOXES_W,ITEM_BOXES_H};
    itemBoxes.render(ITEM_BOXES_X,0,&clip,&rQuad);
    rQuad = {0,0,SELECTED_INT_BOX_W,SELECTED_INT_BOX_H};
    int x = SELECTED_EXT_BOX_X;
    int y = SELECTED_EXT_BOX_Y;
    for (int i = 0; i < MAX_NUMBER_OF_SELECTED_ITEMS; i++){
        if (equiped[i] != ""){
            images.at(equiped[i]).render(x,y,&clip,&rQuad);
        }
        y += SELECTED_EXT_BOX_H;
    }
}

void GraphicInventory::equip(std::string key){
    equiped[image_positions.at(key)] = key;
}

std::string GraphicInventory::select(int x,int y,Camera& camera){
    int screen_w = camera.getWidth();
    int screen_h = camera.getHeight();
    int selected = -1;
    int actual_x = EXTERIOR_BOX_X;
    int actual_y = EXTERIOR_BOX_Y; 

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
        if ((x > actual_x) && (x < (actual_x + EXTERIOR_BOX_W)) && (y > actual_y) && (y < (actual_y + EXTERIOR_BOX_H))){
            selected = i;
            break;
        }
        actual_x += EXTERIOR_BOX_W; 
        if ((i+1) % NUMBER_OF_COLUMNS == 0){
            actual_x = EXTERIOR_BOX_X;
            actual_y += EXTERIOR_BOX_H; 
        }
    }
    if (selected == -1 || selected >= present_images.size()){
        return "";
    }
    return present_images[selected];
}