#include "Player.h"

Player::Player(SDL_Renderer *aRenderer, PlayerRace aRace, int aPosX, int aPosY)
                                        : bodyImage(aRenderer, 0, 0, 0),
                                          headImage(aRenderer, 0, 0, 0) { /*cambiar 0,0,0 por BLACK, BLACK, BLACK O ALGO ASI*/
    this->speed = PLAYER_SPEED;
    this->posX = aPosX;
    this->posY = aPosY;
    this->bodyFrameX = 0;   //esto debería cambiar y que pasen por parametro cómo estaba mirando el personaje
    this->bodyFrameY = 0;   //esto debería cambiar y que pasen por parametro cómo estaba mirando el personaje
    this->headFrameX = 0;   //esto debería cambiar y que pasen por parametro cómo estaba mirando el personaje
    this->dead = false;     //esto también debería cambiar, puede que el usuario se loguee y este como fantasma
    
    switch (aRace) {
        case HUMAN:
            this->bodyWidth = HUMAN_BODY_WIDTH;
            this->bodyHeight = HUMAN_BODY_HEIGHT;
            this->headWidth = HUMAN_HEAD_WIDTH;
            this->headHeight = HUMAN_HEAD_HEIGHT;
            this->bodyImage.loadFromFile(HUMAN_BODY_PATH);
            this->headImage.loadFromFile(HUMAN_HEAD_PATH);
            break;
        
        case ELF:
            this->bodyWidth = ELF_BODY_WIDTH;
            this->bodyHeight = ELF_BODY_HEIGHT;
            this->headWidth = ELF_HEAD_WIDTH;
            this->headHeight = ELF_HEAD_HEIGHT;
            this->bodyImage.loadFromFile(ELF_BODY_PATH);
            this->headImage.loadFromFile(ELF_HEAD_PATH);
            break;

        case DWARF:
            this->bodyWidth = DWARF_BODY_WIDTH;
            this->bodyHeight = DWARF_BODY_HEIGHT;
            this->headWidth = DWARF_HEAD_WIDTH;
            this->headHeight = DWARF_HEAD_HEIGHT;
            this->bodyImage.loadFromFile(DWARF_BODY_PATH);
            this->headImage.loadFromFile(DWARF_HEAD_PATH);
            break;

        case GNOME:
            this->bodyWidth = GNOME_BODY_WIDTH;
            this->bodyHeight = GNOME_BODY_HEIGHT;
            this->headWidth = GNOME_HEAD_WIDTH;
            this->headHeight = GNOME_HEAD_HEIGHT;
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

void Player::render(Camera &camera) {
    SDL_Rect *currentBodyClip = &(this->bodyClips[bodyFrameX + bodyFrameY * BODY_ANIMATION_FRAMES]);
    SDL_Rect *currentHeadClip = &(this->headClips[headFrameX]);
    SDL_Rect bodyQuad = {this->posX - camera.getX(), this->posY - camera.getY(), bodyWidth, bodyHeight}; // chequear
    SDL_Rect headQuad = {this->posX - camera.getX() + headWidth / 4, this->posY - camera.getY() - headHeight / 2 + 1, headWidth, headHeight}; // chequear
    this->bodyImage.render(bodyQuad.x, bodyQuad.y, currentBodyClip, &bodyQuad); //chequear
    this->headImage.render(headQuad.x, headQuad.y, currentHeadClip, &headQuad); //chequear
}

int Player::getPosX() {
    return this->posX;
}

int Player::getPosY() {
    return this->posY;
}

int Player::getHeight() {
    return this->bodyHeight;
}

int Player::getWidth() {
    return this->bodyWidth;
}
