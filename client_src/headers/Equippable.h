#ifndef __EQUIPPABLE_H__
#define __EQUIPPABLE_H__

#include "FilteredImage.h"
#include <vector>
#include "paths.h"

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
        void render(int posX, int posY);
};

#endif
