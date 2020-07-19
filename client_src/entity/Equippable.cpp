#include "../headers/Equippable.h"

#include "../headers/SpriteClipCreator.h"
#include "../headers/OSError.h"

Equippable::Equippable(SDL_Renderer *renderer, EquipType equipType) : 
                                                    image(renderer, 0, 0, 0),
                                                    type(equipType),
                                                    horFrame(0),
                                                    verFrame(0) {
    switch (equipType) {
        case NONE:
            break;

        case EQUIP_ESPADA:
            image.loadFromFile(GIF_ESPADA_PATH);
            break;
        
        case EQUIP_HACHA:
            image.loadFromFile(GIF_HACHA_PATH);
            break;

        case EQUIP_MARTILLO:
            image.loadFromFile(GIF_MARTILLO_PATH);
            break;

        case EQUIP_VARA_FRESNO:
            image.loadFromFile(GIF_VARA_FRESNO_PATH);
            break;

        case EQUIP_FLAUTA_ELFICA:
            image.loadFromFile(GIF_FLAUTA_ELFICA_PATH);
            break;

        case EQUIP_BACULO_NUDOSO:
            image.loadFromFile(GIF_BACULO_NUDOSO_PATH);
            break;

        case EQUIP_BACULO_ENGARZADO:
            image.loadFromFile(GIF_BACULO_ENGARZADO_PATH);
            break;

        case EQUIP_ARCO_SIMPLE:
            image.loadFromFile(GIF_ARCO_SIMPLE_PATH);
            break;

        case EQUIP_ARCO_COMPUESTO:
            image.loadFromFile(GIF_ARCO_COMPUESTO_PATH);
            break;

        case EQUIP_ARMADURA_CUERO:
            image.loadFromFile(GIF_ARMADURA_CUERO_PATH);
            break;

        case EQUIP_ARMADURA_PLACAS:
            image.loadFromFile(GIF_ARMADURA_PLACAS_PATH);
            break;

        case EQUIP_TUNICA_AZUL:
            image.loadFromFile(GIF_TUNICA_AZUL_PATH);
            break;

        case EQUIP_CAPUCHA:
            image.loadFromFile(GIF_CAPUCHA_PATH);
            break;

        case EQUIP_CASCO_HIERRO:
            image.loadFromFile(GIF_CASCO_HIERRO_PATH);
            break;

        case EQUIP_ESCUDO_TORTUGA:
            image.loadFromFile(GIF_ESCUDO_TORTUGA_PATH);
            break;

        case EQUIP_ESCUDO_HIERRO:
            image.loadFromFile(GIF_ESCUDO_HIERRO_PATH);
            break;
        
        case EQUIP_SOMBRERO_MAGICO:
            image.loadFromFile(GIF_SOMBRERO_MAGICO_PATH);
            break;
        
        default:
            throw OSError("Error Equippable Constructor: EquipType invalido.");
            break;
    }

    SpriteClipCreator(EQUIPPABLE_HEIGHT * EQUIPPABLE_ANIMATION_STATES, 
                      EQUIPPABLE_WIDTH * EQUIPPABLE_ANIMATION_FRAMES, 
                      EQUIPPABLE_HEIGHT, EQUIPPABLE_WIDTH, clips);

    this->quad = {0, 0, EQUIPPABLE_WIDTH, EQUIPPABLE_HEIGHT};
}

Equippable::Equippable(Equippable&& other) : image(std::move(other.image)),
                                             type(std::move(other.type)),
                                             horFrame(std::move(other.horFrame)),
                                             verFrame(std::move(other.verFrame)),
                                             clips(std::move(other.clips)),
                                             quad(std::move(other.quad)) {}

Equippable& Equippable::operator=(Equippable&& other) {
    if (this == &other) {
        return *this;
    }

    this->image = std::move(other.image);
    this->type = std::move(other.type);
    this->horFrame = std::move(other.horFrame);
    this->verFrame = std::move(other.verFrame);
    this->clips = std::move(other.clips);
    this->quad = std::move(other.quad);

    return *this;
}

Equippable::~Equippable() {}

void Equippable::updateEquipment(EquipType equipType) {
    type = equipType;

    switch (equipType) {
        case NONE:
            break;

        case EQUIP_ESPADA:
            image.loadFromFile(GIF_ESPADA_PATH);
            break;
        
        case EQUIP_HACHA:
            image.loadFromFile(GIF_HACHA_PATH);
            break;

        case EQUIP_MARTILLO:
            image.loadFromFile(GIF_MARTILLO_PATH);
            break;

        case EQUIP_VARA_FRESNO:
            image.loadFromFile(GIF_VARA_FRESNO_PATH);
            break;

        case EQUIP_FLAUTA_ELFICA:
            image.loadFromFile(GIF_FLAUTA_ELFICA_PATH);
            break;

        case EQUIP_BACULO_NUDOSO:
            image.loadFromFile(GIF_BACULO_NUDOSO_PATH);
            break;

        case EQUIP_BACULO_ENGARZADO:
            image.loadFromFile(GIF_BACULO_ENGARZADO_PATH);
            break;

        case EQUIP_ARCO_SIMPLE:
            image.loadFromFile(GIF_ARCO_SIMPLE_PATH);
            break;

        case EQUIP_ARCO_COMPUESTO:
            image.loadFromFile(GIF_ARCO_COMPUESTO_PATH);
            break;

        case EQUIP_ARMADURA_CUERO:
            image.loadFromFile(GIF_ARMADURA_CUERO_PATH);
            break;

        case EQUIP_ARMADURA_PLACAS:
            image.loadFromFile(GIF_ARMADURA_PLACAS_PATH);
            break;

        case EQUIP_TUNICA_AZUL:
            image.loadFromFile(GIF_TUNICA_AZUL_PATH);
            break;

        case EQUIP_CAPUCHA:
            image.loadFromFile(GIF_CAPUCHA_PATH);
            break;

        case EQUIP_CASCO_HIERRO:
            image.loadFromFile(GIF_CASCO_HIERRO_PATH);
            break;

        case EQUIP_ESCUDO_TORTUGA:
            image.loadFromFile(GIF_ESCUDO_TORTUGA_PATH);
            break;

        case EQUIP_ESCUDO_HIERRO:
            image.loadFromFile(GIF_ESCUDO_HIERRO_PATH);
            break;
        
        case EQUIP_SOMBRERO_MAGICO:
            image.loadFromFile(GIF_SOMBRERO_MAGICO_PATH);
            break;
        
        default:
            break;
    }
}

void Equippable::updateFrame(uint8_t aHorFrame, uint8_t aVerFrame) {
    horFrame = aHorFrame;
    verFrame = aVerFrame;
}

void Equippable::render(int posX, int posY) {
    if (type != NONE) {
        quad.x = posX;
        quad.y = posY;
        if (type == EQUIP_SOMBRERO_MAGICO) quad.y -= 11;
        SDL_Rect *actualClip = &(clips[horFrame + verFrame * EQUIPPABLE_ANIMATION_FRAMES]);
        image.render(quad.x, quad.y, actualClip, &quad);
    }
}
