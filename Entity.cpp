#include "Entity.h"
#include "SpriteClipCreator.h"

Entity::Entity(SDL_Renderer *renderer, int anID, int aPosX, int aPosY, 
         View aView) : image(renderer, 0, 0, 0), posX(aPosX), posY(aPosY), 
         ID(anID), view(aView), frame(0), dead(false) {}

Entity::~Entity() {}

Entity::Entity(Entity&& other) : ID(other.ID), posX(other.posX), 
                                 posY(other.posY), height(other.height), 
                                 width(other.width), speed(other.speed),
                                 view(other.view), frame(other.frame),
                                 vertClips(other.vertClips),
                                 horClips(other.horClips),
                                 clips(std::move(other.clips)),
                                 quad(other.quad), image(std::move(other.image)),
                                 dead(other.dead) {}

Entity& Entity::operator=(Entity&& other) {
    ID = other.ID;
    posX = other.posX;
    posY = other.posY;
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
    dead = other.dead;
}

void Entity::refreshPosition(MovementType move) {
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

void Entity::render(Camera &camera) {
    quad.x = posX - camera.getX();
    quad.y = posY - camera.getY();

    SDL_Rect actClip;
    if (vertClips == 1) actClip = clips[frame];
    else actClip = clips[view * horClips + frame];

    image.render(quad.x, quad.y, &actClip, &quad);
}

bool Entity::isDead() {
    return dead;
}

void Entity::destroy() {
    dead = true;
}
