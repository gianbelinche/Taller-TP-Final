#include "Skeleton.h"
#include "SpriteClipCreator.h"

Skeleton::Skeleton(SDL_Renderer *renderer, int anID, int posX, int posY, 
                   View aView) : Entity(renderer, anID, posX, posY, aView) {
    image.loadFromFile(SKELETON_PATH);
    height = SKELETON_HEIGHT;
    width = SKELETON_WIDTH;
    horClips = SKELETON_HOR_SPRITES;
    vertClips = SKELETON_VERT_SPRITES;
    quad = {0, 0, height, width};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Skeleton::~Skeleton() {}
