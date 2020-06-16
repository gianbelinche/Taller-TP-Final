#ifndef CLASS_LAYOUT
#define CLASS_LAYOUT
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Image.h"
#include "Text.h"
#include "GraphicInventory.h"
#include "ExpBar.h"
#include "MiniChat.h"

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
    ExpBar expBar;
    MiniChat chat;
public:
    Layout(SDL_Renderer* mainRenderer);
    void changeGold(int gold);
    void changeLife(int life, int max_life);
    void changeMana(int mana, int max_mana);
    void changeLevel(int level);
    void changeExp(int exp,int max_exp);
    void addItem(std::string item);
    void removeItem(std::string item);
    void selectItem(std::string item);
    void sendCharacter(std::string c);
    void removeCharacter();
    void addMessage(std::string message);
    void sendMessage();
    void render(int screen_width,int screen_height);
    ~Layout();

};

#endif
