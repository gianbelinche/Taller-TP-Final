#ifndef __ITEM_H__
#define __ITEM_H__

#include <SDL2/SDL.h>
#include "Entity.h"
#include "paths.h"

enum ItemType {ESPADA = 1, HACHA, MARTILLO, VARA_FRESNO, FLAUTA_ELFICA, BACULO_NUDOSO,
               BACULO_ENGARZADO, ARCO_SIMPLE, ARCO_COMPUESTO, ARMADURA_CUERO, 
               ARMADURA_PLACAS, TUNICA_AZUL, CAPUCHA, CASCO_HIERRO, ESCUDO_TORTUGA, 
               ESCUDO_HIERRO, SOMBRERO_MAGICO, POCION_MANA, POCION_VIDA, ORO};

class Item : public Entity {
    protected:
        FilteredImage image;

    public:
        Item(SDL_Renderer *renderer, ItemType type, uint32_t anID, 
             uint16_t aPosX, uint16_t aPosY);
        ~Item();

        Item(const Item &copy) = delete;
        Item(Item&& other);
        Item& operator=(Item&& other);

        virtual void refreshPosition(MovementType move) override;
        virtual void render(Camera &camera) override;
        virtual bool collision(uint16_t x, uint16_t y) override;
        virtual void changeState(uint8_t aState) override;
        virtual void changeEquipment(EquipType equipType, uint8_t what) override;
        virtual void teleportTo(uint16_t posX, uint16_t posY) override;
};

#endif
