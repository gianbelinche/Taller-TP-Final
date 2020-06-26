#ifndef CLASS_EXP_BAR
#define CLASS_EXP_BAR
#include "Image.h"

class ExpBar{
private:
    SDL_Renderer* mainRenderer;    
    Image emptyBar;
    Image expBar;
    int exp;
    int max_exp;
public:
    ExpBar(SDL_Renderer* mainRenderer);
    void render(int screen_w,int screen_h);
    void changeExp(int exp, int max_exp);
};

#endif
