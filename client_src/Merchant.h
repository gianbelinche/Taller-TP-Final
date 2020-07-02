#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include <SDL2/SDL.h>
#include "NPC.h"

#define MERCHANT_PATH "img/merchant.png"
#define MERCHANT_HEIGHT 46
#define MERCHANT_WIDTH 25
#define MERCHANT_VERT_SPRITES 4
#define MERCHANT_HOR_SPRITES 1
#define MERCHANT_SPEED 0

class Merchant : public NPC {
    public:
        Merchant(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
                 uint16_t posY);
        ~Merchant();

        Merchant(const Merchant& copy) = delete;
        Merchant(Merchant &&other);
        Merchant& operator=(Merchant&& other);
};

#endif
