#ifndef __SPYDER_H__
#define __SPYDER_H__

#include <SDL2/SDL.h>
#include "NPC.h"

#define SPYDER_PATH "img/spyder.png"
#define SPYDER_HEIGHT 20
#define SPYDER_WIDTH 26
#define SPYDER_VERT_SPRITES 4
#define SPYDER_HOR_SPRITES 4
#define SPYDER_SPEED 6

class Spyder : public NPC {
    public:
        Spyder(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY);
        ~Spyder();

        Spyder(const Spyder& copy) = delete;
        Spyder(Spyder &&other);
        Spyder& operator=(Spyder&& other);
};

#endif
