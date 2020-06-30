#include "NPC.h"
#include "SpriteClipCreator.h"

NPC::NPC(SDL_Renderer *renderer, uint32_t anID, uint16_t aPosX, uint16_t aPosY)
                    : Entity(anID, aPosX, aPosY), image(renderer, 0, 0, 0),
                      view(DOWN), frame(0) {}

NPC::~NPC() {}

NPC::NPC(NPC&& other) : Entity(std::move(other)), height(other.height), 
                        width(other.width), speed(other.speed),
                        view(other.view), frame(other.frame),
                        vertClips(other.vertClips),
                        horClips(other.horClips),
                        clips(std::move(other.clips)),
                        quad(other.quad), image(std::move(other.image)) {}

NPC& NPC::operator=(NPC&& other) {
    if (this == &other) {
        return *this;
    }
    
    Entity::operator=(std::move(other));
    height = other.height;
    width = other.width;
    speed = other.speed;
    view = other.view;
    frame = other.frame;
    vertClips = other.vertClips;
    horClips = other.horClips;
    clips = std::move(other.clips);
    quad = other.quad;
    image = std::move(other.image);
}

void NPC::refreshPosition(MovementType move) {
    switch (move) {
        case MOVE_UP:
            frame++;
            if (frame > horClips) frame = 0;
            view = UP;
            posY -= speed;
            break;
        
        case MOVE_DOWN:
            frame++;
            if (frame > horClips) frame = 0;
            view = DOWN;
            posY += speed;
            break;

        case MOVE_LEFT:
            frame++;
            if (frame > horClips) frame = 0;
            view = LEFT;
            posX -= speed;
            break;

        case MOVE_RIGHT:
            frame++;
            if (frame > horClips) frame = 0;
            view = RIGHT;
            posX += speed;
            break;

        case STOP:
            frame = 0;
            break;

        default:
            break;
    }
}

void NPC::render(Camera &camera) {
    quad.x = posX - camera.getX();
    quad.y = posY - camera.getY();

    SDL_Rect actClip;
    if (vertClips == 1) actClip = clips[frame];
    else actClip = clips[view * horClips + frame];

    image.render(quad.x, quad.y, &actClip, &quad);
}

bool NPC::collision(uint16_t x, uint16_t y) {
    return (x > posX) && (x < posX + width) && (y > posY) && (y < posY + width);
}

void NPC::kill() {}
