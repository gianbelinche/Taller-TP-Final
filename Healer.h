#ifndef __HEALER_H__
#define __HEALER_H__

#include <SDL2/SDL.h>
#include "NPC.h"

#define HEALER_PATH "img/healer.png"
#define HEALER_HEIGHT 45
#define HEALER_WIDTH 25
#define HEALER_VERT_SPRITES 4
#define HEALER_HOR_SPRITES 1
#define HEALER_SPEED 0

class Healer : public NPC {
    public:
        Healer(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY, View aView);
        ~Healer();
};

#endif
