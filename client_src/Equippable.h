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

#define EQUIPPABLE_ANIMATION_FRAMES 5
#define EQUIPPABLE_ANIMATION_STATES 4

enum EquipType {NONE, EQUIP_ESPADA, EQUIP_HACHA, EQUIP_MARTILLO,
               EQUIP_VARA_FRESNO, EQUIP_FLAUTA_ELFICA, EQUIP_BACULO_NUDOSO,
               EQUIP_BACULO_ENGARZADO, EQUIP_ARCO_SIMPLE, EQUIP_ARCO_COMPUESTO,
               EQUIP_ARMADURA_CUERO, EQUIP_ARMADURA_PLACAS, EQUIP_TUNICA_AZUL,
               EQUIP_CAPUCHA, EQUIP_CASCO_HIERRO, EQUIP_ESCUDO_TORTUGA,
               EQUIP_ESCUDO_HIERRO, EQUIP_SOMBRERO_MAGICO};

class Equippable {
    private:
        FilteredImage image;
        EquipType type;
        uint8_t horFrame;
        uint8_t verFrame;
        std::vector<SDL_Rect> clips;
        SDL_Rect quad;
        
    public:
        Equippable(SDL_Renderer *renderer, EquipType equipType);
        ~Equippable();

        Equippable(const Equippable &copy) = delete;
        Equippable(Equippable&& other);
        Equippable& operator=(Equippable&& other);

        void updateEquipment(EquipType equipType);
        void updateFrame(uint8_t aHorFrame, uint8_t aVerFrame);
        void render(uint16_t posX, uint16_t posY);
};

#endif
