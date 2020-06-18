#include "Item.h"
#include "SpriteClipCreator.h"

/* CHEQUEAR QUE EL VIEW SEA EL QUE ES IGUAL A CERO!! */
Item::Item(SDL_Renderer *renderer, int anID, int posX, int posY, 
           ItemType type) : Entity(renderer, anID, posX, posY, UP) {
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

        default:
            //ERROR
            break;
    }

    height = ITEM_HEIGHT;
    width = ITEM_WIDTH;
    horClips = ITEM_HOR_SPRITES;
    vertClips = ITEM_VERT_SPRITES;
    quad = {0, 0, height, width};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Item::~Item() {}
