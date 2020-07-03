#ifndef __BANKER_H__
#define __BANKER_H__

#include <SDL2/SDL.h>
#include "NPC.h"

#define BANKER_PATH "img/banker.png"
#define BANKER_HEIGHT 59
#define BANKER_WIDTH 25
#define BANKER_VERT_SPRITES 4
#define BANKER_HOR_SPRITES 1
#define BANKER_SPEED 0

class Banker : public NPC {
    public:
        Banker(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
               uint16_t posY);
        ~Banker();

        Banker(const Banker& copy) = delete;
        Banker(Banker &&other);
        Banker& operator=(Banker&& other);
};

#endif