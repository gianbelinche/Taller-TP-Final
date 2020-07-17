#include "../headers/Attack.h"
#include "../headers/SpriteClipCreator.h"

Attack::Attack(SDL_Renderer *renderer, AttackType type, uint16_t aPosX, 
               uint16_t aPosY) : frame(0), image(renderer, 0, 0, 0), 
                                 ended(false) {
    switch (type) {
        case SWORD_ATTACK:
            height = SWORD_ATTACK_HEIGHT;
            width = SWORD_ATTACK_WIDTH;
            vertClips = SWORD_ATTACK_VERT_SPRITES;
            horClips = SWORD_ATTACK_HOR_SPRITES;
            maxFrame = vertClips * horClips;
            image.loadFromFile(SWORD_ATTACK_PATH);
            break;
        
        case AXE_ATTACK:
            height = AXE_ATTACK_HEIGHT;
            width = AXE_ATTACK_WIDTH;
            vertClips = AXE_ATTACK_VERT_SPRITES;
            horClips = AXE_ATTACK_HOR_SPRITES;
            maxFrame = vertClips * horClips;
            image.loadFromFile(AXE_ATTACK_PATH);
            break;

        case HAMMER_ATTACK:
            height = HAMMER_ATTACK_HEIGHT;
            width = HAMMER_ATTACK_WIDTH;
            vertClips = HAMMER_ATTACK_VERT_SPRITES;
            horClips = HAMMER_ATTACK_HOR_SPRITES;
            maxFrame = vertClips * horClips;
            image.loadFromFile(HAMMER_ATTACK_PATH);
            break;

        case FRESNO_BAR_ATTACK:
            height = FRESNO_BAR_ATTACK_HEIGHT;
            width = FRESNO_BAR_ATTACK_WIDTH;
            vertClips = FRESNO_BAR_ATTACK_VERT_SPRITES;
            horClips = FRESNO_BAR_ATTACK_HOR_SPRITES;
            maxFrame = vertClips * horClips;
            image.loadFromFile(FRESNO_BAR_ATTACK_PATH);
            break;

        case ELFIC_FLUTE_ATTACK:
            height = ELFIC_FLUTE_ATTACK_HEIGHT;
            width = ELFIC_FLUTE_ATTACK_WIDTH;
            vertClips = ELFIC_FLUTE_ATTACK_VERT_SPRITES;
            horClips = ELFIC_FLUTE_ATTACK_HOR_SPRITES;
            maxFrame = vertClips * horClips;
            image.loadFromFile(ELFIC_FLUTE_ATTACK_PATH);
            break;

        case BACULO_NUDOSO_ATTACK:
            height = BACULO_NUDOSO_ATTACK_HEIGHT;
            width = BACULO_NUDOSO_ATTACK_WIDTH;
            vertClips = BACULO_NUDOSO_ATTACK_VERT_SPRITES;
            horClips = BACULO_NUDOSO_ATTACK_HOR_SPRITES;
            maxFrame = vertClips * horClips;
            image.loadFromFile(BACULO_NUDOSO_ATTACK_PATH);
            break;

        case BACULO_ENGARZADO_ATTACK:
            height = BACULO_ENGARZADO_ATTACK_HEIGHT;
            width = BACULO_ENGARZADO_ATTACK_WIDTH;
            vertClips = BACULO_ENGARZADO_ATTACK_VERT_SPRITES;
            horClips = BACULO_ENGARZADO_ATTACK_HOR_SPRITES;
            maxFrame = vertClips * horClips;
            image.loadFromFile(BACULO_ENGARZADO_ATTACK_PATH);
            break;

        case SIMPLE_BOW_ATTACK:
            height = SIMPLE_BOW_ATTACK_HEIGHT;
            width = SIMPLE_BOW_ATTACK_WIDTH;
            vertClips = SIMPLE_BOW_ATTACK_VERT_SPRITES;
            horClips = SIMPLE_BOW_ATTACK_HOR_SPRITES;
            maxFrame = vertClips * horClips;
            image.loadFromFile(SIMPLE_BOW_ATTACK_PATH);
            break;

        case COMPOSED_BOW_ATTACK:
            height = COMPOSED_BOW_ATTACK_HEIGHT;
            width = COMPOSED_BOW_ATTACK_WIDTH;
            vertClips = COMPOSED_BOW_ATTACK_VERT_SPRITES;
            horClips = COMPOSED_BOW_ATTACK_HOR_SPRITES;
            maxFrame = vertClips * horClips;
            image.loadFromFile(COMPOSED_BOW_ATTACK_PATH);
            break;

        default:
            break;
    }

    posX = aPosX - width / 3;
    posY = aPosY - height / 3;
    quad = {0, 0, width, height};
    SpriteClipCreator(height * vertClips, width * horClips, height, width,
                      clips);
}

Attack::Attack(Attack &&other) : frame(other.frame), 
                                 maxFrame(other.maxFrame),
                                 image(std::move(other.image)), 
                                 height(other.height),
                                 width(other.width),
                                 vertClips(other.vertClips),
                                 horClips(other.horClips),
                                 posX(other.posX),
                                 posY(other.posY),
                                 clips(std::move(other.clips)), 
                                 quad(std::move(other.quad)),
                                 ended(other.ended) {}

Attack& Attack::operator=(Attack &&other) {
    if (this == &other) {
        return *this;
    }
    
    this->frame = other.frame;
    this->maxFrame = other.maxFrame;
    this->image = std::move(other.image);
    this->height = other.height;
    this->width = other.width;
    this->vertClips = other.vertClips;
    this->horClips = other.horClips;
    this->posX = other.posX;
    this->posY = other.posY;
    this->clips = std::move(other.clips);
    this->quad = std::move(other.quad);
    this->ended = other.ended;

    return *this;
}

Attack::~Attack() {}

void Attack::render(Camera &camera) {
    quad.x = posX - camera.getX();
    quad.y = posY - camera.getY();

    SDL_Rect actClip = clips[frame];
    image.render(quad.x, quad.y, &actClip, &quad);

    frame++;
    if (frame >= maxFrame) ended = true;
}

bool Attack::isEnded() {
    return ended;
}
