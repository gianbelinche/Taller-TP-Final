#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include <SDL2/SDL.h>
#include "Entity.h"

#define MERCHANT_PATH "img/merchant.png"
#define MERCHANT_HEIGHT 1 //cambiar
#define MERCHANT_WIDTH 1 //cambiar
#define MERCHANT_VERT_SPRITES 4
#define MERCHANT_HOR_SPRITES 1
#define MERCHANT_SPEED 0

class Merchant : public Entity {
    public:
        Merchant(SDL_Renderer *renderer, int anID, int posX, int posY, View aView);
        ~Merchant();
};

#endif
