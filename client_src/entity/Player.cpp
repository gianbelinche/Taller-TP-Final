#include "../headers/Player.h"

#include "../headers/OSError.h"

#define B 0

#define WEAPON  0
#define ARMOR   1
#define SHIELD  2
#define HELMET  3

#define ALIVE    0
#define DEAD     1
#define MEDITATE 2

Player::Player(SDL_Renderer *aRenderer, PlayerRace aRace, uint32_t anID, 
               uint16_t aPosX, uint16_t aPosY, uint8_t aState, 
               EquipType aWeapon, EquipType anArmor, EquipType aShield, 
               EquipType aHelmet) : Entity(anID, aPosX, aPosY),
                                    state(aState),
                                    bodyImage(aRenderer, B, B, B),
                                    headImage(aRenderer, B, B, B),
                                    ghostImage(aRenderer, B, B, B),
                                    meditateImage(aRenderer, B, B, B),
                                    weapon(aRenderer, aWeapon),
                                    armor(aRenderer, anArmor),
                                    shield(aRenderer, aShield),
                                    helmet(aRenderer, aHelmet) {
    this->speed = PLAYER_SPEED;
    this->bodyWidth = PLAYER_BODY_WIDTH;
    this->bodyHeight = PLAYER_BODY_HEIGHT;
    this->headWidth = PLAYER_HEAD_WIDTH;
    this->headHeight = PLAYER_HEAD_HEIGHT;
    this->ghostWidth = GHOST_WIDTH;
    this->ghostHeight = GHOST_HEIGHT;
    this->meditateWidth = MEDITATE_WIDTH;
    this->meditateHeight = MEDITATE_HEIGHT;
    this->bodyFrameX = 0;
    this->bodyFrameY = 0;
    this->headFrameX = 0;
    this->ghostFrameX = 0;
    this->ghostFrameY = 0;
    this->meditateFrame = 0;

    switch (aRace) {
        case HUMAN:
            this->bodyImage.loadFromFile(HUMAN_BODY_PATH);
            this->headImage.loadFromFile(HUMAN_HEAD_PATH);
            break;
        
        case ELF:
            this->bodyImage.loadFromFile(ELF_BODY_PATH);
            this->headImage.loadFromFile(ELF_HEAD_PATH);
            break;

        case DWARF:
            this->bodyImage.loadFromFile(DWARF_BODY_PATH);
            this->headImage.loadFromFile(DWARF_HEAD_PATH);
            break;

        case GNOME:
            this->bodyImage.loadFromFile(GNOME_BODY_PATH);
            this->headImage.loadFromFile(GNOME_HEAD_PATH);
            break;

        default:
            throw OSError("Error Player Constructor: PlayerRace invalido.");
            break;
    }

    this->ghostImage.loadFromFile(GHOST_PATH);
    this->meditateImage.loadFromFile(MEDITATE_PATH);
    
    SpriteClipCreator(bodyHeight * BODY_ANIMATION_STATES, bodyWidth * 
                      BODY_ANIMATION_FRAMES, bodyHeight, bodyWidth, bodyClips);

    SpriteClipCreator(headHeight * HEAD_ANIMATION_STATES, headWidth * 
                      HEAD_ANIMATION_FRAMES, headHeight, headWidth, headClips);

    SpriteClipCreator(ghostHeight * GHOST_ANIMATION_STATES, ghostWidth * 
                      GHOST_ANIMATION_FRAMES, ghostHeight, ghostWidth, 
                      ghostClips);

    SpriteClipCreator(meditateHeight * MEDITATE_ANIMATION_STATES, 
                      meditateWidth * MEDITATE_ANIMATION_FRAMES, 
                      meditateHeight, meditateWidth, meditateClips);
}

Player::Player(Player&& other) : Entity(std::move(other)), 
                                 speed(other.speed),
                                 bodyWidth(other.bodyWidth),
                                 bodyHeight(other.bodyHeight),
                                 headWidth(other.headWidth),
                                 headHeight(other.headHeight),
                                 ghostWidth(other.ghostWidth),
                                 ghostHeight(other.ghostHeight),
                                 meditateWidth(other.meditateWidth),
                                 meditateHeight(other.meditateHeight),
                                 bodyFrameX(other.bodyFrameX),
                                 bodyFrameY(other.bodyFrameY), 
                                 headFrameX(other.headFrameX),
                                 ghostFrameX(other.ghostFrameX),
                                 ghostFrameY(other.ghostFrameY),
                                 meditateFrame(other.meditateFrame),
                                 state(other.state),
                                 bodyImage(std::move(other.bodyImage)),
                                 headImage(std::move(other.headImage)),
                                 ghostImage(std::move(other.ghostImage)),
                                 meditateImage(std::move(other.meditateImage)),
                                 weapon(std::move(other.weapon)),
                                 armor(std::move(other.armor)),
                                 shield(std::move(other.shield)),
                                 helmet(std::move(other.helmet)),
                                 bodyClips(std::move(other.bodyClips)), 
                                 headClips(std::move(other.headClips)),
                                 ghostClips(std::move(other.ghostClips)),
                                 meditateClips(std::move(other.meditateClips)) 
                                 {}

Player& Player::operator=(Player&& other) {
    if (this == &other) {
        return *this;
    }

    Entity::operator=(std::move(other));
    this->speed = other.speed;
    this->bodyWidth = other.bodyWidth;
    this->bodyHeight = other.bodyHeight;
    this->headWidth = other.headWidth;
    this->headHeight = other.headHeight;
    this->ghostWidth = other.ghostWidth;
    this->ghostHeight = other.ghostHeight;
    this->meditateWidth = other.meditateWidth;
    this->meditateHeight = other.meditateHeight;
    this->bodyFrameX = other.bodyFrameX;
    this->bodyFrameY = other.bodyFrameY;
    this->headFrameX = other.headFrameX;
    this->ghostFrameX = other.ghostFrameX;
    this->ghostFrameY = other.ghostFrameY;
    this->meditateFrame = other.meditateFrame;
    this->state = other.state;
    this->bodyImage = std::move(other.bodyImage);
    this->headImage = std::move(other.headImage);
    this->ghostImage = std::move(other.ghostImage);
    this->meditateImage = std::move(other.meditateImage);
    this->weapon = std::move(other.weapon);
    this->armor = std::move(other.armor);
    this->shield = std::move(other.shield);
    this->helmet = std::move(other.helmet);
    this->bodyClips = std::move(other.bodyClips);
    this->headClips = std::move(other.headClips);
    this->ghostClips = std::move(other.ghostClips);
    this->meditateClips = std::move(other.meditateClips);

    return *this;
}

Player::~Player() {}

void Player::refreshAlivePosition(MovementType move) {
    switch (move) {
        case MOVE_UP:
            this->posY -= this->speed;
            this->bodyFrameX++;
            if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
            this->bodyFrameY = 1;
            this->headFrameX = 3;
            break;

        case MOVE_LEFT:
            this->posX -= this->speed;
            this->bodyFrameX++;
            if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
            this->bodyFrameY = 2;
            this->headFrameX = 2;
            break;

        case MOVE_DOWN:
            this->posY += this->speed;
            this->bodyFrameX++;
            if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
            this->bodyFrameY = 0;
            this->headFrameX = 0;
            break;

        case MOVE_RIGHT:
            this->posX += this->speed;
            this->bodyFrameX++;
            if (this->bodyFrameX >= BODY_ANIMATION_FRAMES) bodyFrameX = 0;
            this->bodyFrameY = 3;
            this->headFrameX = 1;
            break;

        case STOP:
            this->bodyFrameX = 0;
            break;
        
        default:
            break;
    }
    weapon.updateFrame(bodyFrameX, bodyFrameY);
    armor.updateFrame(bodyFrameX, bodyFrameY);
    shield.updateFrame(bodyFrameX, bodyFrameY);
    helmet.updateFrame(bodyFrameX, bodyFrameY);
}

void Player::refreshDeadPosition(MovementType move) {
    switch (move) {
        case MOVE_UP:
            this->posY -= this->speed;
            this->ghostFrameX++;
            if (this->ghostFrameX >= GHOST_ANIMATION_FRAMES) ghostFrameX = 0;
            this->ghostFrameY = 1;
            break;

        case MOVE_LEFT:
            this->posX -= this->speed;
            this->ghostFrameX++;
            if (this->ghostFrameX >= GHOST_ANIMATION_FRAMES) ghostFrameX = 0;
            this->ghostFrameY = 2;
            break;

        case MOVE_DOWN:
            this->posY += this->speed;
            this->ghostFrameX++;
            if (this->ghostFrameX >= GHOST_ANIMATION_FRAMES) ghostFrameX = 0;
            this->ghostFrameY = 0;
            break;

        case MOVE_RIGHT:
            this->posX += this->speed;
            this->ghostFrameX++;
            if (this->ghostFrameX >= GHOST_ANIMATION_FRAMES) ghostFrameX = 0;
            this->ghostFrameY = 3;
            break;

        case STOP:
            this->ghostFrameX = 0;
            break;
        
        default:
            break;
    }
}

void Player::refreshPosition(MovementType move) {
    if (state == ALIVE) {
        this->refreshAlivePosition(move);
    } else if (state == DEAD) {
        this->refreshDeadPosition(move);
    }
}

void Player::renderGhost(Camera &camera) {
    SDL_Rect *currentGhostClip = &(this->ghostClips[ghostFrameX + ghostFrameY * 
                                   GHOST_ANIMATION_FRAMES]);
    SDL_Rect ghostQuad = {this->posX - camera.getX(), this->posY - 
                          camera.getY(), ghostWidth, ghostHeight};
    this->ghostImage.render(ghostQuad.x, ghostQuad.y, currentGhostClip, 
                           &ghostQuad);
}

void Player::renderPlayer(Camera &camera) {
    SDL_Rect *currentBodyClip = &(this->bodyClips[bodyFrameX + bodyFrameY * 
                                                  BODY_ANIMATION_FRAMES]);
    SDL_Rect *currentHeadClip = &(this->headClips[headFrameX]);
    SDL_Rect bodyQuad = {this->posX - camera.getX(), this->posY - camera.getY(),
                         bodyWidth, bodyHeight};
    SDL_Rect headQuad = {this->posX - camera.getX() + headWidth / 4, 
                         this->posY - camera.getY() - headHeight / 2 + 1, 
                         headWidth, headHeight};
    this->bodyImage.render(bodyQuad.x, bodyQuad.y, currentBodyClip, &bodyQuad);
    this->headImage.render(headQuad.x, headQuad.y, currentHeadClip, &headQuad);
    this->weapon.render(bodyQuad.x, bodyQuad.y);
    this->armor.render(bodyQuad.x, bodyQuad.y);
    this->shield.render(bodyQuad.x, bodyQuad.y);
    this->helmet.render(headQuad.x, headQuad.y);
}

void Player::renderMeditate(Camera &camera) {
    this->renderPlayer(camera);
    SDL_Rect *currentMedClip = &(this->meditateClips[meditateFrame]);
    SDL_Rect medQuad = {this->posX - camera.getX() - bodyWidth * 5 / 4, 
                        this->posY - camera.getY() - bodyHeight * 4 / 3, 
                        meditateWidth * 4 / 5, meditateHeight};
    this->meditateImage.render(medQuad.x, medQuad.y, currentMedClip, &medQuad);
    this->meditateFrame++;
    if (this->meditateFrame >= (MEDITATE_ANIMATION_STATES *
                                MEDITATE_ANIMATION_FRAMES)) {
        this->meditateFrame = 0;
    }
}

void Player::render(Camera &camera) {
    if (state == ALIVE) {
        this->renderPlayer(camera);
    } else if (state == DEAD) {
        this->renderGhost(camera);
    } else if (state == MEDITATE) {
        this->renderMeditate(camera);
    }
}

bool Player::collision(uint16_t x, uint16_t y) {
    return (x > posX) && (x < posX + bodyWidth) && (y > posY) && 
           (y < posY + bodyHeight);
}

void Player::changeState(uint8_t aState) {
    state = aState;
    meditateFrame = 0;
}

void Player::changeEquipment(EquipType equipType, uint8_t what) {
    switch (what) {
        case WEAPON:
            weapon.updateEquipment(equipType);
            break;
        
        case ARMOR:
            armor.updateEquipment(equipType);
            break;

        case SHIELD:
            shield.updateEquipment(equipType);
            break;

        case HELMET:
            helmet.updateEquipment(equipType);
            break;

        default:
            break;
    }
}

void Player::teleportTo(uint16_t posX, uint16_t posY) {
    this->posX = posX;
    this->posY = posY;
}

uint16_t Player::getHeight() {
    return this->bodyHeight;
}

uint16_t Player::getWidth() {
    return this->bodyWidth;
}
