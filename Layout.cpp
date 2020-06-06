#include "Layout.h"
#include <sstream>
#include <string>

Layout::Layout(SDL_Renderer* mainRenderer) : mainRenderer(mainRenderer), 
layout(NULL), gold(NULL), life(NULL), mana(NULL), level(NULL) {
    Image layout(mainRenderer);
    layout.loadFromFile("Layout_graphics/layout_prototype2.png");
    
    this->layout = std::move(layout);
    this->changeGold(100);
    this->changeLife(100,200);
    this->changeMana(50,100);
    this->changeLevel(3);
}

void Layout::changeGold(int gold){
    std::stringstream s;
    s << "Oro: " << gold;
    Text text(mainRenderer);
    text.loadText(s.str(),14);
    this->gold = std::move(text);
}

void Layout::changeLife(int life, int max_life){
    std::stringstream s;
    s << "Vida: " << life << "/" << max_life;
    Text text(mainRenderer);
    text.loadText(s.str(),14);
    this->life = std::move(text);
}

void Layout::changeMana(int mana, int max_mana){
    std::stringstream s;
    s << "Mana: " << mana << "/" << max_mana;
    Text text(mainRenderer);
    text.loadText(s.str(),14);
    this->mana = std::move(text);
}

void Layout::changeLevel(int level){
    std::stringstream s;
    s << "Nivel: " << level;
    Text text(mainRenderer);
    text.loadText(s.str(),14);
    this->level = std::move(text);
}

void Layout::render(int screen_width,int screen_heigth){
    layout.render(screen_width - layout.getWidth(),0);
    gold.render(screen_width - gold.getWidth() * 3.3,gold.getHeight() / 3);
    life.render(screen_width - life.getWidth() * 2.3,life.getHeight() * 1.35);
    mana.render(screen_width - mana.getWidth() * 1.1,mana.getHeight() * 1.35); //Ver forma mas eficaz de hacer esto
    level.render(screen_width - level.getWidth() * 1.7,level.getHeight() * 0.3);
}