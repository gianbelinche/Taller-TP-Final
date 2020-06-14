#include "ExpBar.h"
#include <iostream>

ExpBar::ExpBar(SDL_Renderer* mainRenderer) : mainRenderer(mainRenderer),
emptyBar(NULL), expBar(NULL), exp(0), max_exp(100) {
    Image emptyBar(mainRenderer);
    emptyBar.loadFromFile("Layout_graphics/emptyBar.png");
    this->emptyBar = std::move(emptyBar);
    Image expBar(mainRenderer);
    expBar.loadFromFile("Layout_graphics/expBar.png");
    this->expBar = std::move(expBar);
}

void ExpBar::changeExp(int exp, int max_exp){
    this->exp = exp;
    this->max_exp = max_exp;
}

void ExpBar::render(int screen_w,int screen_h){
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rQuad = {0,0,screen_w / 15,screen_h * 127 / 200}; // ver este tamaño
    emptyBar.render(screen_w * 3 / 5,screen_h * 74 / 200,&clip,&rQuad);
    float progress = ((float)exp / (float)max_exp);
    if (progress < 0.05 && progress != 0)
        progress = 0.05;
    rQuad.h = rQuad.h * progress;
    expBar.render(screen_w * 3 / 5,screen_h * 74 / 200,&clip,&rQuad);
}
