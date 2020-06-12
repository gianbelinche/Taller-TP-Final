#include "Player.h"

Player::Player(SDL_Renderer *aRenderer) : speed(SPEED), posX(0), posY(0),
                                          frameX(0), frameY(0),
                                          plImage(aRenderer, 0, 0, 0) {
    this->plImage.loadFromFile(PLAYER_PATH);

    for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
        this->spriteClips[i].x = i * PLAYER_WIDTH;
        this->spriteClips[i].y = 0;
        this->spriteClips[i].w = PLAYER_WIDTH;
        this->spriteClips[i].h = PLAYER_HEIGHT;
    }
}

Player::Player(Player&& other) : speed(other.speed), posX(other.posX),
                                 posY(other.posY), frameX(other.frameX),
                                 frameY(other.frameY),
                                 plImage(std::move(other.plImage)) {
    for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
        this->spriteClips[i].x = other.spriteClips[i].x;
        this->spriteClips[i].y = other.spriteClips[i].y;
        this->spriteClips[i].w = other.spriteClips[i].w;
        this->spriteClips[i].h = other.spriteClips[i].h;
    }
}

Player& Player::operator=(Player&& other) {
    if (this == &other) {
        return *this;
    }

    this->speed = other.speed;
    this->posX = other.posX;
    this->posY = other.posY;
    this->frameX = other.frameX;
    this->frameY = other.frameY;
    this->plImage = std::move(other.plImage);

    for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
        this->spriteClips[i].x = other.spriteClips[i].x;
        this->spriteClips[i].y = other.spriteClips[i].y;
        this->spriteClips[i].w = other.spriteClips[i].w;
        this->spriteClips[i].h = other.spriteClips[i].h;
    }
}

Player::~Player() {}

void Player::move(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                this->posY -= this->speed;
                this->frameX++;
                if (this->frameX >= WALKING_ANIMATION_FRAMES) frameX = 0;
                frameY = PLAYER_HEIGHT;
                this->spriteClips[frameX].y = frameY;
                // chequear que no se vaya del mapa
                break;

            case SDLK_a:
                this->posX -= this->speed;
                this->frameX++;
                if (this->frameX >= WALKING_ANIMATION_FRAMES) frameX = 0;
                frameY = PLAYER_HEIGHT * 2;
                this->spriteClips[frameX].y = frameY;
                // chequear que no se vaya del mapa
                break;

            case SDLK_s:
                this->posY += this->speed;
                this->frameX++;
                if (this->frameX >= WALKING_ANIMATION_FRAMES) frameX = 0;
                frameY = 0;
                this->spriteClips[frameX].y = frameY;
                // chequear que no se vaya del mapa
                break;

            case SDLK_d:
                this->posX += this->speed;
                this->frameX++;
                if (this->frameX >= WALKING_ANIMATION_FRAMES) frameX = 0;
                frameY = PLAYER_HEIGHT * 3;
                this->spriteClips[frameX].y = frameY;
                // chequear que no se vaya del mapa
                break;
            
            default:
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_a:
            case SDLK_s:
            case SDLK_d:
                this->frameX = 0;
                break;
            
            default:
                break;
        }
    }
}

void Player::render(int camX, int camY) {
    SDL_Rect* currentClip = &(this->spriteClips[frameX]);
    SDL_Rect renderQuad = {this->posX - camX, this->posY - camY, PLAYER_WIDTH, PLAYER_HEIGHT}; // chequear
    this->plImage.render(this->posX - camX, this->posY - camY, currentClip, &renderQuad); //chequear
}

int Player::getPosX() {
    return this->posX;
}

int Player::getPosY() {
    return this->posY;
}
