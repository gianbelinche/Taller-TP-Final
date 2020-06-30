#ifndef CLASS_EXP_BAR
#define CLASS_EXP_BAR
#include "Image.h"
#include "Camera.h"

class ExpBar{
private:
    SDL_Renderer* mainRenderer;    
    Image emptyBar;
    Image expBar;
    int exp;
    int max_exp;
public:
    ExpBar(SDL_Renderer* mainRenderer);
    void render(Camera& camera);
    void changeExp(int exp, int max_exp);
};

#endif
