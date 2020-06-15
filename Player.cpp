#include "Player.h"

Player::Player(SDL_Renderer *aRenderer) : speed(SPEED), posX(4640), posY(1408),
                                          bodyFrameX(0), bodyFrameY(0),
                                          bodyImage(aRenderer, 0, 0, 0),
                                          headImage(aRenderer, 0, 0, 0) { /*cambiar 0,0,0 por BLACK, BLACK, BLACK O ALGO ASI*/
    this->bodyImage.loadFromFile(PLAYER_BODY_PATH);
    this->headImage.loadFromFile(PLAYER_HEAD_PATH);

    for (int i = 0; i < BODY_ANIMATION_FRAMES; i++) {
        this->bodyClips[i].x = i * BODY_WIDTH;
        this->bodyClips[i].y = 0;
        this->bodyClips[i].w = BODY_WIDTH;
        this->bodyClips[i].h = BODY_HEIGHT;
    }

    for (int i = 0; i < HEAD_ANIMATION_FRAMES; i++) {
        this->headClips[i].x = i * HEAD_WIDTH;
        this->headClips[i].y = 0;
        this->headClips[i].w = HEAD_WIDTH;
        this->headClips[i].h = HEAD_HEIGHT;
    }
}

Player::Player(Player&& other) : speed(other.speed), posX(other.posX),
                                 posY(other.posY), bodyFrameX(other.bodyFrameX),
                                 bodyFrameY(other.bodyFrameY),
                                 bodyImage(std::move(other.bodyImage)),
                                 headImage(std::move(other.headImage)) {
    for (int i = 0; i < BODY_ANIMATION_FRAMES; i++) {
        this->bodyClips[i].x = other.bodyClips[i].x;
        this->bodyClips[i].y = other.bodyClips[i].y;
        this->bodyClips[i].w = other.bodyClips[i].w;
        this->bodyClips[i].h = other.bodyClips[i].h;
    }

    for (int i = 0; i < HEAD_ANIMATION_FRAMES; i++) {
        this->headClips[i].x = other.headClips[i].x;
        this->headClips[i].y = other.headClips[i].y;
        this->headClips[i].w = other.headClips[i].w;
        this->headClips[i].h = other.headClips[i].h;
    }
}

Player& Player::operator=(Player&& other) {
    if (this == &other) {
        return *this;
    }

    this->speed = other.speed;
    this->posX = other.posX;
    this->posY = other.posY;
    this->bodyFrameX = other.bodyFrameX;
    this->bodyFrameY = other.bodyFrameY;
    this->headImage = std::move(other.headImage);
    this->bodyImage = std::move(other.bodyImage);

    for (int i = 0; i < BODY_ANIMATION_FRAMES; i++) {
        this->bodyClips[i].x = other.bodyClips[i].x;
        this->bodyClips[i].y = other.bodyClips[i].y;
        this->bodyClips[i].w = other.bodyClips[i].w;
        this->bodyClips[i].h = other.bodyClips[i].h;
    }

    for (int i = 0; i < HEAD_ANIMATION_FRAMES; i++) {
        this->headClips[i].x = other.headClips[i].x;
        this->headClips[i].y = other.headClips[i].y;
        this->headClips[i].w = other.headClips[i].w;
        this->headClips[i].h = other.headClips[i].h;
    }
}

Player::~Player() {}

void Player::move(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                this->posY -= this->speed;
                this->bodyFrameX++;
                if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
                this->bodyFrameY = BODY_HEIGHT;
                this->bodyClips[bodyFrameX].y = this->bodyFrameY;
                this->headFrameX = 3;
                // chequear que no se vaya del mapa
                break;

            case SDLK_a:
                this->posX -= this->speed;
                this->bodyFrameX++;
                if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
                this->bodyFrameY = BODY_HEIGHT * 2;
                this->bodyClips[bodyFrameX].y = this->bodyFrameY;
                this->headFrameX = 2;
                // chequear que no se vaya del mapa
                break;

            case SDLK_s:
                this->posY += this->speed;
                this->bodyFrameX++;
                if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
                this->bodyFrameY = 0;
                this->bodyClips[bodyFrameX].y = this->bodyFrameY;
                this->headFrameX = 0;
                // chequear que no se vaya del mapa
                break;

            case SDLK_d:
                this->posX += this->speed;
                this->bodyFrameX++;
                if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
                this->bodyFrameY = BODY_HEIGHT * 3;
                this->bodyClips[bodyFrameX].y = this->bodyFrameY;
                this->headFrameX = 1;
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
                this->bodyFrameX = 0;
                bodyClips[bodyFrameX].y = this->bodyFrameY;
                break;
            
            default:
                break;
        }
    }
}

void Player::render(int camX, int camY) {
    SDL_Rect* currentBodyClip = &(this->bodyClips[bodyFrameX]);
    SDL_Rect* currentHeadClip = &(this->headClips[headFrameX]);
    SDL_Rect bodyQuad = {this->posX - camX, this->posY - camY, BODY_WIDTH, BODY_HEIGHT}; // chequear
    SDL_Rect headQuad = {this->posX - camX + HEAD_WIDTH / 4, this->posY - camY - HEAD_HEIGHT / 2 + 1, HEAD_WIDTH, HEAD_HEIGHT}; // chequear
    this->bodyImage.render(bodyQuad.x, bodyQuad.y, currentBodyClip, &bodyQuad); //chequear
    this->headImage.render(headQuad.x, headQuad.y, currentHeadClip, &headQuad); //chequear
}

int Player::getPosX() {
    return this->posX;
}

int Player::getPosY() {
    return this->posY;
}
