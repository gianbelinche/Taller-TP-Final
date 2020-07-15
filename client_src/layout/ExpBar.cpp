#include "../headers/ExpBar.h"
#include "../headers/paths.h"
#include <iostream>

#define BAR_X (screen_w * 3 / 5)
#define BAR_Y (screen_h * 74 / 200)
#define EMPTY_BAR_W (screen_w / 15)
#define EMPTY_BAR_H (screen_h * 127 / 200)

ExpBar::ExpBar(SDL_Renderer* mainRenderer) : mainRenderer(mainRenderer),
emptyBar(NULL), expBar(NULL), exp(0), max_exp(100) {
    Image emptyBar(mainRenderer);
    emptyBar.loadFromFile(EMPTY_BAR_PATH);
    this->emptyBar = std::move(emptyBar);
    Image expBar(mainRenderer);
    expBar.loadFromFile(EXP_BAR_PATH);
    this->expBar = std::move(expBar);
}

void ExpBar::changeExp(int exp, int max_exp){
    this->exp = exp;
    this->max_exp = max_exp;
}

void ExpBar::render(const Camera& camera){
    int screen_w = camera.getWidth();
    int screen_h = camera.getHeight();
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rQuad = {0,0,EMPTY_BAR_W,EMPTY_BAR_H};
    emptyBar.render(BAR_X,BAR_Y,&clip,&rQuad);
    float progress = ((float)exp / (float)max_exp);
    if (progress < 0.05 && progress != 0)
        progress = 0.05;
    rQuad.h = rQuad.h * progress;
    expBar.render(BAR_X,BAR_Y,&clip,&rQuad);
}
