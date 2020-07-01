#include "Skeleton.h"
#include "SpriteClipCreator.h"

Skeleton::Skeleton(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
                   uint16_t posY) : NPC(renderer, anID, posX, posY) {
    image.loadFromFile(SKELETON_PATH);
    height = SKELETON_HEIGHT;
    width = SKELETON_WIDTH;
    horClips = SKELETON_HOR_SPRITES;
    vertClips = SKELETON_VERT_SPRITES;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Skeleton::~Skeleton() {}
