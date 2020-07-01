#ifndef __EQUIPPABLE_H__
#define __EQUIPPABLE_H__

#include "FilteredImage.h"
#include <vector>

#define GIF_ESPADA_PATH "img/espadagif.png"
#define GIF_HACHA_PATH "img/hachagif.png"
#define GIF_MARTILLO_PATH "img/martillogif.png"
#define GIF_VARA_FRESNO_PATH "img/varafresnogif.png"
#define GIF_FLAUTA_ELFICA_PATH "img/flautaelficagif.png"
#define GIF_BACULO_NUDOSO_PATH "img/baculonudosogif.png"
#define GIF_BACULO_ENGARZADO_PATH "img/baculoengarzadogif.png"
#define GIF_ARCO_SIMPLE_PATH "img/arcosimplegif.png"
#define GIF_ARCO_COMPUESTO_PATH "img/arcocompuestogif.png"
#define GIF_ARMADURA_CUERO_PATH "img/armaduracuerogif.png"
#define GIF_ARMADURA_PLACAS_PATH "img/armaduraplacasgif.png"
#define GIF_TUNICA_AZUL_PATH "img/tunicaazulgif.png"
#define GIF_CAPUCHA_PATH "img/capuchagif.png"
#define GIF_CASCO_HIERRO_PATH "img/cascohierrogif.png"
#define GIF_ESCUDO_TORTUGA_PATH "img/escudotortugagif.png"
#define GIF_ESCUDO_HIERRO_PATH "img/escudohierrogif.png"
#define GIF_SOMBRERO_MAGICO_PATH "img/sombreromagicogif.png"

#define EQUIPPABLE_HEIGHT 45
#define EQUIPPABLE_WIDTH 25

enum EquipType {NONE, ESPADA, HACHA, MARTILLO, VARA_FRESNO, FLAUTA_ELFICA, 
               BACULO_NUDOSO, BACULO_ENGARZADO, ARCO_SIMPLE, ARCO_COMPUESTO, 
               ARMADURA_CUERO, ARMADURA_PLACAS, TUNICA_AZUL, CAPUCHA, 
               CASCO_HIERRO, ESCUDO_TORTUGA, ESCUDO_HIERRO, SOMBRERO_MAGICO};

class Equippable {
    private:
        FilteredImage image;
        uint8_t horFrame;
        uint8_t verFrame;
        std::vector<SDL_Rect> clips;
        
    public:
        Equippable(SDL_Renderer *renderer, EquipType equipType, uint8_t aHorFrame, uint8_t aVerFrame);
        ~Equippable();

        void updateFrame(uint8_t aHorFrame, uint8_t aVerFrame);
        void render(uint16_t posX, uint16_t posY);
};

#endif
