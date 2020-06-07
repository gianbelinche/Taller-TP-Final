#include "Layout.h"
#include <sstream>
#include <string>

Layout::Layout(SDL_Renderer* mainRenderer) : mainRenderer(mainRenderer), 
layout(NULL), gold(NULL), life(NULL), mana(NULL), level(NULL) {
    Image layout(mainRenderer);
    layout.loadFromFile("Layout_graphics/layout_prototype2.png");
    
    this->layout = std::move(layout);
    this->changeGold(10000000);
    this->changeLife(100,200);
    this->changeMana(50,100);
    this->changeLevel(3);
}

void Layout::changeGold(int gold){
    std::stringstream s;
    s << "Oro: " << gold;
    Text text(mainRenderer);
    text.loadText(s.str(),50);
    this->gold = std::move(text);
}

void Layout::changeLife(int life, int max_life){
    std::stringstream s;
    s << "Vida: " << life << "/" << max_life;
    Text text(mainRenderer);
    text.loadText(s.str(),50);
    this->life = std::move(text);
}

void Layout::changeMana(int mana, int max_mana){
    std::stringstream s;
    s << "Mana: " << mana << "/" << max_mana;
    Text text(mainRenderer);
    text.loadText(s.str(),50);
    this->mana = std::move(text);
}

void Layout::changeLevel(int level){
    std::stringstream s;
    s << "Nivel: " << level;
    Text text(mainRenderer);
    text.loadText(s.str(),50);
    this->level = std::move(text);
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
}