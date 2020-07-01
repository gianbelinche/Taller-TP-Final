#ifndef CLASS_GRAPHIC_INVENTORY
#define CLASS_GRAPHIC_INVENTORY

#include <map>
#include <string>
#include <vector>
#include "FilteredImage.h"
#include "Image.h"
#include "Camera.h"

/*
    Implementa un inventario de manera gráfica
    Donde en cada slot se grafica una imagen    
*/
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

    //Añade un objeto al inventario
    void addImage(int key);
    //Quita un objeto del inventario en el slot pos
    void removeImage(int pos);
    //Equipa un objeto
    void equip(int key);
    //Devuelve que slot fue clickeado, o -1 si no se clickeo ningun slot
    int select(int x,int y,Camera& camera);
    void render(Camera& camera);
};

#endif
