#include "Skeleton.h"
#include "SpriteClipCreator.h"

Skeleton::Skeleton(SDL_Renderer *renderer, uint32_t anID, uint16_t posX, 
                   uint16_t posY) : NPC(renderer, anID, posX, posY) {
    image.loadFromFile(SKELETON_PATH);
    height = SKELETON_HEIGHT;
    width = SKELETON_WIDTH;
    horClips = SKELETON_HOR_SPRITES;
    vertClips = SKELETON_VERT_SPRITES;
    speed = SKELETON_SPEED;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Skeleton::Skeleton(Skeleton &&other) : NPC(std::move(other)) {}

Skeleton& Skeleton::operator=(Skeleton&& other) {
    if (this == &other) {
        return *this;
    }

    NPC::operator=(std::move(other));

    return *this;
}

Skeleton::~Skeleton() {}
