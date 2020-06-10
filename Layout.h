#ifndef CLASS_LAYOUT
#define CLASS_LAYOUT
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Image.h"
#include "Text.h"
#include "GraphicInventory.h"

class Layout {
private:
    SDL_Renderer* mainRenderer;
    Image layout;
    Text gold;
    Text life;
    Text mana;
    Text level;
    TTF_Font* gFont;    
    GraphicInventory inventory;
public:
    Layout(SDL_Renderer* mainRenderer);
    void changeGold(int gold);
    void changeLife(int life, int max_life);
    void changeMana(int mana, int max_mana);
    void changeLevel(int level);
    void addItem(std::string item);
    void removeItem(std::string item);
    void render(int screen_width,int screen_height);
    ~Layout();

};

#endif