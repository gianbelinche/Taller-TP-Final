#include "Equippable.h"
#include "SpriteClipCreator.h"

Equippable::Equippable(SDL_Renderer *renderer, EquipType equipType,
                       uint8_t aHorFrame, uint8_t aVerFrame) : 
                                                    image(renderer, 0, 0, 0),
                                                    horFrame(aHorFrame),
                                                    verFrame(aVerFrame) {
    switch (equipType) {
        case NONE:
            break;

        case ESPADA:
            image.loadFromFile(GIF_ESPADA_PATH);
            break;
        
        case HACHA:
            image.loadFromFile(GIF_HACHA_PATH);
            break;

        case MARTILLO:
            image.loadFromFile(GIF_MARTILLO_PATH);
            break;

        case VARA_FRESNO:
            image.loadFromFile(GIF_VARA_FRESNO_PATH);
            break;

        case FLAUTA_ELFICA:
            image.loadFromFile(GIF_FLAUTA_ELFICA_PATH);
            break;

        case BACULO_NUDOSO:
            image.loadFromFile(GIF_BACULO_NUDOSO_PATH);
            break;

        case BACULO_ENGARZADO:
            image.loadFromFile(GIF_BACULO_ENGARZADO_PATH);
            break;

        case ARCO_SIMPLE:
            image.loadFromFile(GIF_ARCO_SIMPLE_PATH);
            break;

        case ARCO_COMPUESTO:
            image.loadFromFile(GIF_ARCO_COMPUESTO_PATH);
            break;

        case ARMADURA_CUERO:
            image.loadFromFile(GIF_ARMADURA_CUERO_PATH);
            break;

        case ARMADURA_PLACAS:
            image.loadFromFile(GIF_ARMADURA_PLACAS_PATH);
            break;

        case TUNICA_AZUL:
            image.loadFromFile(GIF_TUNICA_AZUL_PATH);
            break;

        case CAPUCHA:
            image.loadFromFile(GIF_CAPUCHA_PATH);
            break;

        case CASCO_HIERRO:
            image.loadFromFile(GIF_CASCO_HIERRO_PATH);
            break;

        case ESCUDO_TORTUGA:
            image.loadFromFile(GIF_ESCUDO_TORTUGA_PATH);
            break;

        case ESCUDO_HIERRO:
            image.loadFromFile(GIF_ESCUDO_HIERRO_PATH);
            break;
        
        case SOMBRERO_MAGICO:
            image.loadFromFile(GIF_SOMBRERO_MAGICO_PATH);
            break;
        
        default:
            break;
    }


}

Equippable::~Equippable() {}

void Equippable::updateFrame(uint8_t aHorFrame, uint8_t aVerFrame) {
    horFrame = aHorFrame;
    verFrame = aVerFrame;
}

void Equippable::render(uint16_t posX, uint16_t posY) {
    
}
