#include "Player.h"

Player::Player(SDL_Renderer *aRenderer) : speed(SPEED), posX(4640), posY(1408),
                                          bodyFrameX(0), bodyFrameY(0),
                                          bodyImage(aRenderer, 0, 0, 0),
                                          headImage(aRenderer, 0, 0, 0) { /*cambiar 0,0,0 por BLACK, BLACK, BLACK O ALGO ASI*/
    this->bodyImage.loadFromFile(PLAYER_BODY_PATH);
    this->headImage.loadFromFile(PLAYER_HEAD_PATH);

    SpriteClipCreator(BODY_HEIGHT * BODY_ANIMATION_STATES, BODY_WIDTH * 
                      BODY_ANIMATION_FRAMES, BODY_HEIGHT, BODY_WIDTH, bodyClips);

    SpriteClipCreator(HEAD_HEIGHT, HEAD_WIDTH * HEAD_ANIMATION_FRAMES, HEAD_HEIGHT, HEAD_WIDTH, headClips);
}

Player::Player(Player&& other) : speed(other.speed), posX(other.posX),
                                 posY(other.posY), bodyFrameX(other.bodyFrameX),
                                 bodyFrameY(other.bodyFrameY), 
                                 headFrameX(other.headFrameX),
                                 bodyImage(std::move(other.bodyImage)),
                                 headImage(std::move(other.headImage)),
                                 bodyClips(std::move(bodyClips)), 
                                 headClips(std::move(headClips)) {}

Player& Player::operator=(Player&& other) {
    if (this == &other) {
        return *this;
    }

    this->speed = other.speed;
    this->posX = other.posX;
    this->posY = other.posY;
    this->bodyFrameX = other.bodyFrameX;
    this->bodyFrameY = other.bodyFrameY;
    this->headFrameX = other.headFrameX;
    this->bodyImage = std::move(other.bodyImage);
    this->headImage = std::move(other.headImage);
    this->bodyClips = std::move(other.bodyClips);
    this->headClips = std::move(other.headClips);
}

Player::~Player() {}

void Player::move(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                this->posY -= this->speed;
                this->bodyFrameX++;
                if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
                this->bodyFrameY = 1;
                this->headFrameX = 3;
                break;

            case SDLK_a:
                this->posX -= this->speed;
                this->bodyFrameX++;
                if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
                this->bodyFrameY =  2;
                this->bodyClips[bodyFrameX].y = this->bodyFrameY;
                this->headFrameX = 2;
                break;

            case SDLK_s:
                this->posY += this->speed;
                this->bodyFrameX++;
                if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
                this->bodyFrameY = 0;
                this->bodyClips[bodyFrameX].y = this->bodyFrameY;
                this->headFrameX = 0;
                break;

            case SDLK_d:
                this->posX += this->speed;
                this->bodyFrameX++;
                if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
                this->bodyFrameY = 3;
                this->bodyClips[bodyFrameX].y = this->bodyFrameY;
                this->headFrameX = 1;
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
                break;
            
            default:
                break;
        }
    }
}

void Player::render(SDL_Rect &camera) {
    SDL_Rect *currentBodyClip = &(this->bodyClips[bodyFrameX + bodyFrameY * BODY_ANIMATION_FRAMES]);
    SDL_Rect *currentHeadClip = &(this->headClips[headFrameX]);
    SDL_Rect bodyQuad = {this->posX - camera.x, this->posY - camera.y, BODY_WIDTH, BODY_HEIGHT}; // chequear
    SDL_Rect headQuad = {this->posX - camera.x + HEAD_WIDTH / 4, this->posY - camera.y - HEAD_HEIGHT / 2 + 1, HEAD_WIDTH, HEAD_HEIGHT}; // chequear
    this->bodyImage.render(bodyQuad.x, bodyQuad.y, currentBodyClip, &bodyQuad); //chequear
    this->headImage.render(headQuad.x, headQuad.y, currentHeadClip, &headQuad); //chequear
}

int Player::getPosX() {
    return this->posX;
}

int Player::getPosY() {
    return this->posY;
}
