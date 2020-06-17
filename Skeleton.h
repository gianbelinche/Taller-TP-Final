#ifndef __SKELETON_H__
#define __SKELETON_H__

#include <SDL2/SDL.h>
#include "Entity.h"

#define SKELETON_PATH "img/skeleton.png"
#define SKELETON_HEIGHT 1 //cambiar
#define SKELETON_WIDTH 1 //cambiar
#define SKELETON_VERT_SPRITES 1 //cambiar
#define SKELETON_HOR_SPRITES 1 //cambiar
#define SKELETON_SPEED 1 //cambiar

class Skeleton : public Entity {
    public:
        Skeleton(SDL_Renderer *renderer, int anID, int posX, int posY, View aView);
        ~Skeleton();
};

#endif
