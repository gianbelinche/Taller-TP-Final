#ifndef __ITEM_H__
#define __ITEM_H__

#include <SDL2/SDL.h>
#include "Entity.h"

#define ESPADA_PATH "img/espada.png"
#define HACHA_PATH "img/hacha.png"
#define MARTILLO_PATH "img/martillo.png"
#define VARA_FRESNO_PATH "img/vara_fresno.png"
#define FLAUTA_ELFICA_PATH "img/flauta_elfica.png"
#define BACULO_NUDOSO_PATH "img/baculo_nudoso.png"
#define BACULO_ENGARZADO_PATH "img/baculo_engarzado.png"
#define ARCO_SIMPLE_PATH "img/arco_simple.png"
#define ARCO_COMPUESTO_PATH "img/arco_compuesto.png"
#define ARMADURA_CUERO_PATH "img/armadura_cuero.png"
#define ARMADURA_PLACAS_PATH "img/armadura_placas.png"
#define TUNICA_AZUL_PATH "img/tunica_azul.png"
#define CAPUCHA_PATH "img/capucha.png"
#define CASCO_HIERRO_PATH "img/casco_hierro.png"
#define ESCUDO_TORTUGA_PATH "img/escudo_tortuga.png"
#define ESCUDO_HIERRO_PATH "img/escudo_hierro.png"
#define SOMBRERO_MAGICO_PATH "img/sombrero_magico.png"

enum ItemType {ESPADA, HACHA, MARTILLO, VARA_FRESNO, FLAUTA_ELFICA, BACULO_NUDOSO,
               BACULO_ENGARZADO, ARCO_SIMPLE, ARCO_COMPUESTO, ARMADURA_CUERO, 
               ARMADURA_PLACAS, TUNICA_AZUL, CAPUCHA, CASCO_HIERRO, ESCUDO_TORTUGA, 
               ESCUDO_HIERRO, SOMBRERO_MAGICO};

class Item : public Entity {
    protected:
        FilteredImage image;

    public:
        Item(SDL_Renderer *renderer, uint32_t anID, uint16_t aPosX, 
             uint16_t aPosY, ItemType type);
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
