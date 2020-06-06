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
    text.loadText(s.str(),10);
    this->gold = std::move(text);
}

void Layout::changeLife(int life, int max_life){
    std::stringstream s;
    s << "Vida: " << life << "/" << max_life;
    Text text(mainRenderer);
    text.loadText(s.str(),10);
    this->life = std::move(text);
}

void Layout::changeMana(int mana, int max_mana){
    std::stringstream s;
    s << "Mana: " << mana << "/" << max_mana;
    Text text(mainRenderer);
    text.loadText(s.str(),10);
    this->mana = std::move(text);
}

void Layout::changeLevel(int level){
    std::stringstream s;
    s << "Level: " << level;
    Text text(mainRenderer);
    text.loadText(s.str(),10);
    this->level = std::move(text);
}

void Layout::render(){
    layout.render(0,0);
    gold.render(0,0);
    life.render(0,0);
    mana.render(0,0);
    level.render(0,0);
}