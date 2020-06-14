#include "Layout.h"
#include <sstream>
#include <string>

Layout::Layout(SDL_Renderer* mainRenderer) : mainRenderer(mainRenderer), 
layout(NULL), gold(NULL), life(NULL), mana(NULL), level(NULL),
inventory(mainRenderer), expBar(mainRenderer) {
    Image layout(mainRenderer);
    layout.loadFromFile("Layout_graphics/layout_prototype_r.png");
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

void Layout::changeExp(int exp,int max_exp){
    expBar.changeExp(exp,max_exp);
}

void Layout::addItem(std::string item){
    inventory.addImage(item);
}

void Layout::removeItem(std::string item){
    inventory.removeImage(item);
}

void Layout::selectItem(std::string item){
    inventory.select(item);
}

void Layout::render(int screen_width,int screen_heigth){
    SDL_Rect clip = {0,0,screen_width,screen_heigth};
    SDL_Rect rq = {0,0,screen_width / 3,screen_heigth};
    int lay_w = screen_width * layout.getWidth() / 640;
    int lay_h = screen_heigth * layout.getHeight() / 480;
    layout.render(screen_width - lay_w,0,&clip,&rq);
    rq = {0,0,lay_w * 40 / 100, lay_h / 22};
    gold.render(screen_width - lay_w * 0.95, 0, &clip,&rq);
    life.render(screen_width - lay_w * 0.95,screen_heigth / 24,&clip,&rq); // l_h / 22
    mana.render(screen_width - lay_w * 0.95/2,screen_heigth / 24,&clip,&rq);
    level.render(screen_width - lay_w * 0.95/2,0,&clip,&rq);
    inventory.render(screen_width,screen_heigth,lay_w,lay_h);
    expBar.render(screen_width,screen_heigth);
}