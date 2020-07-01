#ifndef __SKELETON_H__
#define __SKELETON_H__

#include <SDL2/SDL.h>
#include "NPC.h"

#define SKELETON_PATH "img/skeleton.png"
#define SKELETON_HEIGHT 52
#define SKELETON_WIDTH 25
#define SKELETON_VERT_SPRITES 4
#define SKELETON_HOR_SPRITES 5
#define SKELETON_SPEED 5 //cambiar

class Skeleton : public NPC {
    public:
        Skeleton(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
                 uint16_t posY);
        ~Skeleton();
};

#endif
