#include "Layout.h"
#include <sstream>
#include <string>

Layout::Layout(SDL_Renderer* mainRenderer) : mainRenderer(mainRenderer), 
layout(NULL), gold(NULL), life(NULL), mana(NULL), level(NULL), inventory(mainRenderer) {
    Image layout(mainRenderer);
    layout.setKeyColor(10,0,0);
    layout.loadFromFile("Layout_graphics/layout_prototype3.png");
    this->gFont = TTF_OpenFont("Fonts/OpenSans.ttf", 50);
    this->layout = std::move(layout);

    Text gold(mainRenderer);
    this->gold = std::move(gold);
    this->changeGold(1000);

    Text life(mainRenderer);
    this->life = std::move(life);
    this->changeLife(1000,1000);

    Text mana(mainRenderer);
    this->mana = std::move(mana);
    this->changeMana(2000,2000);

    Text level(mainRenderer);
    this->level = std::move(level);
    this->changeLevel(3);

    inventory.addImage("sword");
    inventory.addImage("axe");
    inventory.addImage("hammer");
    inventory.addImage("axe");
    inventory.addImage("hammer");
    inventory.addImage("axe");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");
    inventory.addImage("sword");

}

Layout::~Layout(){
    TTF_CloseFont(gFont);
}

void Layout::changeGold(int gold){
    std::stringstream s;
    s << "Oro: " << gold;
    this->gold.loadText(s.str(),gFont);
}

void Layout::changeLife(int life, int max_life){
    std::stringstream s;
    s << "Vida: " << life << "/" << max_life;
    this->life.loadText(s.str(),gFont);
}

void Layout::changeMana(int mana, int max_mana){
    std::stringstream s;
    s << "Mana: " << mana << "/" << max_mana;
    this->mana.loadText(s.str(),gFont);
}

void Layout::changeLevel(int level){
    std::stringstream s;
    s << "Nivel: " << level;
    this->level.loadText(s.str(),gFont);
}

void Layout::render(int screen_width,int screen_heigth){
    SDL_Rect clip = {0,0,screen_width,screen_heigth};
    SDL_Rect rq = {0,0,screen_width / 3,screen_heigth};
    layout.render(screen_width - layout.getWidth(),0,&clip,&rq);
    rq = {0,0,layout.getWidth() * 40 / 100, layout.getHeight() / 22};
    gold.render(screen_width - layout.getWidth() * 0.95, 0, &clip,&rq);
    life.render(screen_width - layout.getWidth() * 0.95,layout.getHeight() / 22,&clip,&rq);
    mana.render(screen_width - layout.getWidth() * 0.95/2,layout.getHeight() / 22,&clip,&rq);
    level.render(screen_width - layout.getWidth() * 0.95/2,0,&clip,&rq);
    inventory.render(screen_width,screen_heigth,layout.getWidth(),layout.getHeight());
}