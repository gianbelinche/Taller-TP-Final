#include "Item.h"
#include "SpriteClipCreator.h"
#include "OSError.h"

Item::Item(SDL_Renderer *renderer, ItemType type, uint32_t anID, uint16_t aPosX, 
           uint16_t aPosY) : Entity(anID, aPosX, aPosY), 
                             image(renderer, 0, 0, 0) {
    switch (type) {
        case ESPADA:
            image.loadFromFile(ESPADA_PATH);
            break;
        
        case HACHA:
            image.loadFromFile(HACHA_PATH);
            break;

        case MARTILLO:
            image.loadFromFile(MARTILLO_PATH);
            break;

        case VARA_FRESNO:
            image.loadFromFile(VARA_FRESNO_PATH);
            break;

        case FLAUTA_ELFICA:
            image.loadFromFile(FLAUTA_ELFICA_PATH);
            break;

        case BACULO_NUDOSO:
            image.loadFromFile(BACULO_NUDOSO_PATH);
            break;

        case BACULO_ENGARZADO:
            image.loadFromFile(BACULO_ENGARZADO_PATH);
            break;

        case ARCO_SIMPLE:
            image.loadFromFile(ARCO_SIMPLE_PATH);
            break;

        case ARCO_COMPUESTO:
            image.loadFromFile(ARCO_COMPUESTO_PATH);
            break;

        case ARMADURA_CUERO:
            image.loadFromFile(ARMADURA_CUERO_PATH);
            break;

        case ARMADURA_PLACAS:
            image.loadFromFile(ARMADURA_PLACAS_PATH);
            break;

        case TUNICA_AZUL:
            image.loadFromFile(TUNICA_AZUL_PATH);
            break;

        case CAPUCHA:
            image.loadFromFile(CAPUCHA_PATH);
            break;

        case CASCO_HIERRO:
            image.loadFromFile(CASCO_HIERRO_PATH);
            break;

        case ESCUDO_TORTUGA:
            image.loadFromFile(ESCUDO_TORTUGA_PATH);
            break;

        case ESCUDO_HIERRO:
            image.loadFromFile(ESCUDO_HIERRO_PATH);
            break;

        case SOMBRERO_MAGICO:
            image.loadFromFile(SOMBRERO_MAGICO_PATH);
            break;

        case POCION_MANA:
            image.loadFromFile(POCION_MANA_PATH);
            break;

        case POCION_VIDA:
            image.loadFromFile(POCION_VIDA_PATH);
            break;

        default:
            throw OSError("Error Item Constructor: ItemType invalido.");
            break;
    }
}

Item::~Item() {}

void Item::refreshPosition(MovementType move) {}

void Item::render(Camera &camera) {
    image.render(posX - camera.getX(), posY - camera.getY(), NULL, NULL);
}

bool Item::collision(uint16_t x, uint16_t y) {
    return false;
}

void Item::changeState(uint8_t aState) {}

void Item::changeEquipment(EquipType equipType, uint8_t what) {}

void Item::teleportTo(uint16_t posX, uint16_t posY) {}
