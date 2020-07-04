#include "Layout.h"
#include <sstream>
#include <string>
#include <iostream>

#define FONT_SIZE 50
#define INITIAL_VALUES 1
#define LAY_W (screen_width * 215 / 640)
#define LAY_X (screen_width - LAY_W)
#define TEXT_H (screen_heigth / 22)
#define TEXT_W (LAY_W * 40 / 100)
#define GOLD_LIFE_X (screen_width - LAY_W * 0.95)
#define MANA_LEVEL_X (screen_width - LAY_W * 0.95/2)
#define LIFE_MANA_Y (screen_heigth / 24)
#define ITEM_BOXES_W (screen_width / 15)

Layout::Layout(SDL_Renderer* mainRenderer) : mainRenderer(mainRenderer), 
layout(NULL), gold(NULL), life(NULL), mana(NULL), level(NULL) {
    Image layout(mainRenderer);
    layout.loadFromFile("Layout_graphics/layout_prototype_r.png");
    this->gFont = TTF_OpenFont("Fonts/OpenSans.ttf", FONT_SIZE);
    this->layout = std::move(layout);

    Text gold(mainRenderer);
    this->gold = std::move(gold);
    this->changeGold(INITIAL_VALUES);

    Text life(mainRenderer);
    this->life = std::move(life);
    this->changeLife(INITIAL_VALUES,INITIAL_VALUES);

    Text mana(mainRenderer);
    this->mana = std::move(mana);
    this->changeMana(INITIAL_VALUES,INITIAL_VALUES);

    Text level(mainRenderer);
    this->level = std::move(level);
    this->changeLevel(INITIAL_VALUES);

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


void Layout::render(const Camera& camera){
    int screen_width = camera.getWidth();
    int screen_heigth = camera.getHeight();
    SDL_Rect clip = {0,0,screen_width,layout.getHeight()};
    SDL_Rect rq = {0,0,LAY_W,screen_heigth};
    int lay_w = LAY_W;
    layout.render(LAY_X,0,&clip,&rq);
    clip = {0,0,screen_width,screen_heigth};
    rq = {0,0,TEXT_W, TEXT_H};
    gold.render(GOLD_LIFE_X, 0, &clip,&rq);
    life.render(GOLD_LIFE_X,LIFE_MANA_Y,&clip,&rq);
    mana.render(MANA_LEVEL_X,LIFE_MANA_Y,&clip,&rq);
    level.render(MANA_LEVEL_X,0,&clip,&rq);
}

bool Layout::isClicked(int x,int screen_width) const{
    return (x > screen_width - LAY_W - ITEM_BOXES_W);
}