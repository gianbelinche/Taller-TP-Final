#include "Player.h"

#define B 0

Player::Player(SDL_Renderer *aRenderer, PlayerRace aRace, uint32_t anID, 
               uint16_t aPosX, uint16_t aPosY, bool isDead) : 
                                                Entity(anID, aPosX, aPosY),
                                                bodyImage(aRenderer, B, B, B),
                                                headImage(aRenderer, B, B, B),
                                                dead(isDead) {
    this->speed = PLAYER_SPEED;
    this->bodyFrameX = 0;
    this->bodyFrameY = 0;
    this->headFrameX = 0;
    this->dead = false;     //esto también debería cambiar, puede que el usuario se loguee y este como fantasma
    this->bodyWidth = 25;   //cambiar numeros magicos
    this->bodyHeight = 45;  //cambiar numeros magicos
    this->headWidth = 17;   //cambiar numeros magicos
    this->headHeight = 17;  //cambiar numeros magicos

    switch (aRace) {
        case HUMAN:
            /*this->bodyWidth = HUMAN_BODY_WIDTH;
            this->bodyHeight = HUMAN_BODY_HEIGHT;
            this->headWidth = HUMAN_HEAD_WIDTH;
            this->headHeight = HUMAN_HEAD_HEIGHT;*/
            this->bodyImage.loadFromFile(HUMAN_BODY_PATH);
            this->headImage.loadFromFile(HUMAN_HEAD_PATH);
            break;
        
        case ELF:
            /*this->bodyWidth = ELF_BODY_WIDTH;
            this->bodyHeight = ELF_BODY_HEIGHT;
            this->headWidth = ELF_HEAD_WIDTH;
            this->headHeight = ELF_HEAD_HEIGHT;*/
            this->bodyImage.loadFromFile(ELF_BODY_PATH);
            this->headImage.loadFromFile(ELF_HEAD_PATH);
            break;

        case DWARF:
            /*this->bodyWidth = DWARF_BODY_WIDTH;
            this->bodyHeight = DWARF_BODY_HEIGHT;
            this->headWidth = DWARF_HEAD_WIDTH;
            this->headHeight = DWARF_HEAD_HEIGHT;*/
            this->bodyImage.loadFromFile(DWARF_BODY_PATH);
            this->headImage.loadFromFile(DWARF_HEAD_PATH);
            break;

        case GNOME:
            /*this->bodyWidth = GNOME_BODY_WIDTH;
            this->bodyHeight = GNOME_BODY_HEIGHT;
            this->headWidth = GNOME_HEAD_WIDTH;
            this->headHeight = GNOME_HEAD_HEIGHT;*/
            this->bodyImage.loadFromFile(GNOME_BODY_PATH);
            this->headImage.loadFromFile(GNOME_HEAD_PATH);
            break;

        default:
            break;
    }
    
    SpriteClipCreator(bodyHeight * BODY_ANIMATION_STATES, bodyWidth * 
                      BODY_ANIMATION_FRAMES, bodyHeight, bodyWidth, bodyClips);

    SpriteClipCreator(headHeight, headWidth * HEAD_ANIMATION_FRAMES, headHeight, headWidth, headClips);
}

Player::Player(Player&& other) : Entity(std::move(other)), speed(other.speed), 
                                 bodyFrameX(other.bodyFrameX),
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

    Entity::operator=(std::move(other));
    this->speed = other.speed;
    this->bodyFrameX = other.bodyFrameX;
    this->bodyFrameY = other.bodyFrameY;
    this->headFrameX = other.headFrameX;
    this->bodyImage = std::move(other.bodyImage);
    this->headImage = std::move(other.headImage);
    this->bodyClips = std::move(other.bodyClips);
    this->headClips = std::move(other.headClips);
}

Player::~Player() {}

void Player::refreshPosition(MovementType move) {
    switch (move) {
        case UP:
            this->posY -= this->speed;
            this->bodyFrameX++;
            if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
            this->bodyFrameY = 1;
            this->headFrameX = 3;
            break;

        case LEFT:
            this->posX -= this->speed;
            this->bodyFrameX++;
            if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
            this->bodyFrameY =  2;
            this->bodyClips[bodyFrameX].y = this->bodyFrameY;
            this->headFrameX = 2;
            break;

        case DOWN:
            this->posY += this->speed;
            this->bodyFrameX++;
            if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
            this->bodyFrameY = 0;
            this->bodyClips[bodyFrameX].y = this->bodyFrameY;
            this->headFrameX = 0;
            break;

        case RIGHT:
            this->posX += this->speed;
            this->bodyFrameX++;
            if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
            this->bodyFrameY = 3;
            this->bodyClips[bodyFrameX].y = this->bodyFrameY;
            this->headFrameX = 1;
            break;

        case STOP:
            this->bodyFrameX = 0;
            break;
        
        default:
            break;
    }
}

void Player::render(Camera &camera) {
    SDL_Rect *currentBodyClip = &(this->bodyClips[bodyFrameX + bodyFrameY * BODY_ANIMATION_FRAMES]);
    SDL_Rect *currentHeadClip = &(this->headClips[headFrameX]);
    SDL_Rect bodyQuad = {this->posX - camera.getX(), this->posY - camera.getY(), bodyWidth, bodyHeight}; // chequear
    SDL_Rect headQuad = {this->posX - camera.getX() + headWidth / 4, this->posY - camera.getY() - headHeight / 2 + 1, headWidth, headHeight}; // chequear
    this->bodyImage.render(bodyQuad.x, bodyQuad.y, currentBodyClip, &bodyQuad); //chequear
    this->headImage.render(headQuad.x, headQuad.y, currentHeadClip, &headQuad); //chequear
}

bool Player::collision(uint16_t x, uint16_t y) {
    //COMPLETAR CHEQUEAR CAMBIAR
}

void Player::kill() {
    dead = true;
}

uint16_t Player::getPosX() {
    return this->posX;
}

uint16_t Player::getPosY() {
    return this->posY;
}

uint16_t Player::getHeight() {
    return this->bodyHeight;
}

uint16_t Player::getWidth() {
    return this->bodyWidth;
}
