#include "GraphicInventory.h"
#include "SDLError.h"
#define MAX_NUMBER_OF_ITEMS 20
#define NUMBER_OF_COLUMNS 5
#define MAX_NUMBER_OF_SELECTED_ITEMS 4
#define INTERIOR_BOX_W (screen_w / 24)
#define INTERIOR_BOX_H (screen_h / 19)
#define EXTERIOR_BOX_X (screen_w * 1743 / 2550)
#define EXTERIOR_BOX_Y (screen_h / 10)
#define EXTERIOR_BOX_W ((screen_w / 16) * 105/100)
#define EXTERIOR_BOX_H (screen_h / 14)
#define EXTERIOR_BOX_W_SELECTED (screen_w / 16)
#define EXTERIOR_BOX_SELECTED_H (EXTERIOR_BOX_H * 97/100)
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

enum items{
    SWORD,
    AXE,
    HAMMER,
    FRESNO_ROD,
    ELFIC_FLUTE,
    BACULO_NUDOSO,
    BACULO_ENGARZADO,
    SIMPLE_BOW,
    COMPOSED_BOW,
    LEATHER_ARMOR,
    PLATE_ARMOR,
    BLUE_TUNIC,
    HOOD,
    IRON_HELMET,
    TURTLE_SHIELD,
    IRON_SHIELD,
    MAGIC_HAT
};


GraphicInventory::GraphicInventory(SDL_Renderer* mainRenderer) : 
mainRenderer(mainRenderer), itemBoxes(NULL) {
    Image itemBoxes(mainRenderer);
    itemBoxes.loadFromFile("Layout_graphics/Inventory/ItemBoxes.png");
    this->itemBoxes = std::move(itemBoxes);
    equiped.push_back(-1);
    equiped.push_back(-1);
    equiped.push_back(-1);
    equiped.push_back(-1);
    this->insert(SWORD,"Layout_graphics/Inventory/espada.png",SELECTED_TYPE_0);
    this->insert(AXE,"Layout_graphics/Inventory/hacha.png",SELECTED_TYPE_0);
    this->insert(HAMMER,"Layout_graphics/Inventory/martillo.png",SELECTED_TYPE_0);
    this->insert(FRESNO_ROD,"Layout_graphics/Inventory/vara de fresno.png",SELECTED_TYPE_0);
    this->insert(BACULO_NUDOSO,"Layout_graphics/Inventory/baculo nudoso.png",SELECTED_TYPE_0);
    this->insert(BACULO_ENGARZADO,"Layout_graphics/Inventory/baculo engarzado.png",SELECTED_TYPE_0);
    this->insert(SIMPLE_BOW,"Layout_graphics/Inventory/arco simple.png",SELECTED_TYPE_0);
    this->insert(COMPOSED_BOW,"Layout_graphics/Inventory/arco compuesto.png",SELECTED_TYPE_0);
    this->insert(LEATHER_ARMOR,"Layout_graphics/Inventory/armadura de cuero.png",SELECTED_TYPE_1);
    this->insert(PLATE_ARMOR,"Layout_graphics/Inventory/armadura de placas.png",SELECTED_TYPE_1);
    this->insert(IRON_HELMET,"Layout_graphics/Inventory/casco de hierro.png",SELECTED_TYPE_2);
    this->insert(IRON_SHIELD,"Layout_graphics/Inventory/escudo de hierro.png",SELECTED_TYPE_3);
}

void GraphicInventory::insert(int key,std::string path,int position){
    FilteredImage image(mainRenderer);
    image.loadFromFile(path);
    images.insert(std::pair<int,FilteredImage>(key,std::move(image)));
    image_positions.insert(std::pair<int,int>(key,position));
}

void GraphicInventory::addImage(int key){
    present_images.push_back(key);
}

void GraphicInventory::removeImage(int pos){
    if (pos >= present_images.size()){
        throw SDLError("No hay ningun objeto en la posicion a eliminar\n");
    }
    present_images.erase(present_images.begin() + pos);
}

void GraphicInventory::render(int screen_w,int screen_h){
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
        if (equiped[i] != -1){
            images.at(equiped[i]).render(x,y,&clip,&rQuad);
        }
        y += SELECTED_EXT_BOX_H;
    }
}

void GraphicInventory::equip(int key){
    equiped[image_positions.at(key)] = key;
}

int GraphicInventory::select(int x,int y,int screen_w,int screen_h){
    int selected = -1;
    int actual_x = EXTERIOR_BOX_X;
    int actual_y = EXTERIOR_BOX_Y; 

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
        if ((x >= actual_x) && (x <= (actual_x + EXTERIOR_BOX_W_SELECTED)) && (y >= actual_y) && (y <= (actual_y + EXTERIOR_BOX_SELECTED_H))){
            selected = i;
            break;
        }
        actual_x += EXTERIOR_BOX_W_SELECTED; 
        if ((i+1) % NUMBER_OF_COLUMNS == 0){
            actual_x = EXTERIOR_BOX_X;
            actual_y += EXTERIOR_BOX_SELECTED_H; 
        }
    }
    return selected;
}