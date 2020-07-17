#ifndef __NPC_H__
#define __NPC_H__ 

#include "FilteredImage.h"
#include "Camera.h"
#include "Entity.h"
#include "paths.h"

#define BANKER_HEIGHT 59
#define BANKER_WIDTH 25
#define HEALER_HEIGHT 45
#define HEALER_WIDTH 25
#define MERCHANT_HEIGHT 46
#define MERCHANT_WIDTH 25

enum NPCType {BANKER, HEALER, MERCHANT};

class NPC : public Entity {
    protected:
        FilteredImage image;
        uint16_t height;
        uint16_t width;
        SDL_Rect clip;
        SDL_Rect quad;

    public:
        NPC(SDL_Renderer *renderer, NPCType type, uint32_t anID, uint16_t aPosX,
            uint16_t aPosY);
        ~NPC();

        NPC(const NPC &copy) = delete;
        NPC(NPC&& other);
        NPC& operator=(NPC&& other);

        virtual void refreshPosition(MovementType move) override;
        virtual void render(Camera &camera) override;
        virtual bool collision(uint16_t x, uint16_t y) override;
        virtual void changeState(uint8_t aState) override;
        virtual void changeEquipment(EquipType equipType, uint8_t what) override;
        virtual void teleportTo(uint16_t posX, uint16_t posY) override;
};

#endif
