#include "headers/Mob.h"
#include "headers/SpriteClipCreator.h"

Mob::Mob(SDL_Renderer *renderer, MobType type, uint32_t anID, uint16_t aPosX, 
         uint16_t aPosY) : Entity(anID, aPosX, aPosY), image(renderer, 0, 0, 0),
                      view(DOWN), frame(0) {
    switch (type) {
        case GOBLIN:
            height = GOBLIN_HEIGHT;
            width = GOBLIN_WIDTH;
            vertClips = GOBLIN_VERT_SPRITES;
            horClips = GOBLIN_HOR_SPRITES;
            image.loadFromFile(GOBLIN_PATH);
            speed = GOBLIN_SPEED;
            break;
        
        case SKELETON:
            height = SKELETON_HEIGHT;
            width = SKELETON_WIDTH;
            vertClips = SKELETON_VERT_SPRITES;
            horClips = SKELETON_HOR_SPRITES;
            image.loadFromFile(SKELETON_PATH);
            speed = SKELETON_SPEED;
            break;

        case SPYDER:
            height = SPYDER_HEIGHT;
            width = SPYDER_WIDTH;
            vertClips = SPYDER_VERT_SPRITES;
            horClips = SPYDER_HOR_SPRITES;
            image.loadFromFile(SPYDER_PATH);
            speed = SPYDER_SPEED;
            break;

        case ZOMBIE:
            height = ZOMBIE_HEIGHT;
            width = ZOMBIE_WIDTH;
            vertClips = ZOMBIE_VERT_SPRITES;
            horClips = ZOMBIE_HOR_SPRITES;
            image.loadFromFile(ZOMBIE_PATH);
            speed = ZOMBIE_SPEED;
            break;

        default:
            break;
    }

    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, 
                      clips);
}

Mob::~Mob() {}

Mob::Mob(Mob&& other) : Entity(std::move(other)), image(std::move(other.image)),
                        height(other.height), width(other.width), 
                        speed(other.speed), view(other.view), 
                        frame(other.frame), vertClips(other.vertClips),
                        horClips(other.horClips), clips(std::move(other.clips)),
                        quad(other.quad) {}

Mob& Mob::operator=(Mob&& other) {
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

    return *this;
}

void Mob::refreshPosition(MovementType move) {
    switch (move) {
        case MOVE_UP:
            frame++;
            if (frame >= horClips) frame = 0;
            view = UP;
            posY -= speed;
            break;
        
        case MOVE_DOWN:
            frame++;
            if (frame >= horClips) frame = 0;
            view = DOWN;
            posY += speed;
            break;

        case MOVE_LEFT:
            frame++;
            if (frame >= horClips) frame = 0;
            view = LEFT;
            posX -= speed;
            break;

        case MOVE_RIGHT:
            frame++;
            if (frame >= horClips) frame = 0;
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

void Mob::render(Camera &camera) {
    quad.x = posX - camera.getX();
    quad.y = posY - camera.getY();

    SDL_Rect actClip = clips[view * horClips + frame];

    image.render(quad.x, quad.y, &actClip, &quad);
}

bool Mob::collision(uint16_t x, uint16_t y) {
    return (x > posX) && (x < posX + width) && (y > posY) && (y < posY + height);
}

void Mob::changeState(uint8_t aState) {}

void Mob::changeEquipment(EquipType equipType, uint8_t what) {}

void Mob::teleportTo(uint16_t posX, uint16_t posY) {}
