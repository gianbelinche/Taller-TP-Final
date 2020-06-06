#include "Player.h"

Player::Player(SDL_Renderer *aRenderer) : speed(SPEED), posX(0), posY(0),
                                          frameX(0), frameY(0),
                                          plTexture(aRenderer) {
    this->plTexture.loadFromFile(PLAYER_PATH);

    this->spriteClips[0].x = 0;
    this->spriteClips[0].y = 0;
    this->spriteClips[0].w = PLAYER_WIDTH;
    this->spriteClips[0].h = PLAYER_HEIGHT;

    this->spriteClips[1].x = PLAYER_WIDTH;
    this->spriteClips[1].y = 0;
    this->spriteClips[1].w = PLAYER_WIDTH;
    this->spriteClips[1].h = PLAYER_HEIGHT;

    this->spriteClips[2].x = PLAYER_WIDTH * 2;
    this->spriteClips[2].y = 0;
    this->spriteClips[2].w = PLAYER_WIDTH;
    this->spriteClips[2].h = PLAYER_HEIGHT;

    this->spriteClips[3].x = PLAYER_WIDTH * 3;
    this->spriteClips[3].y = 0;
    this->spriteClips[3].w = PLAYER_WIDTH;
    this->spriteClips[3].h = PLAYER_HEIGHT;

    this->spriteClips[4].x = PLAYER_WIDTH * 4;
    this->spriteClips[4].y = 0;
    this->spriteClips[4].w = PLAYER_WIDTH;
    this->spriteClips[4].h = PLAYER_HEIGHT;
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
    SDL_Rect* currentClip = &(this->spriteClips[frameX / 4]);
    this->plTexture.render(this->posX - camX, this->posY - camY, currentClip);
}

int Player::getPosX() {
    return this->posX;
}

int Player::getPosY() {
    return this->posY;
}
