#ifndef __MOB_H__
#define __MOB_H__ 

#include <vector>
#include "FilteredImage.h"
#include "Camera.h"
#include "Entity.h"
#include "paths.h"

#define GOBLIN_HEIGHT 32
#define GOBLIN_WIDTH 24
#define GOBLIN_VERT_SPRITES 4
#define GOBLIN_HOR_SPRITES 8
#define GOBLIN_SPEED 7
#define SKELETON_HEIGHT 52
#define SKELETON_WIDTH 25
#define SKELETON_VERT_SPRITES 4
#define SKELETON_HOR_SPRITES 5
#define SKELETON_SPEED 4
#define SPYDER_HEIGHT 20
#define SPYDER_WIDTH 26
#define SPYDER_VERT_SPRITES 4
#define SPYDER_HOR_SPRITES 4
#define SPYDER_SPEED 6
#define ZOMBIE_HEIGHT 45
#define ZOMBIE_WIDTH 25
#define ZOMBIE_VERT_SPRITES 4
#define ZOMBIE_HOR_SPRITES 5
#define ZOMBIE_SPEED 3

enum MobType {GOBLIN, SKELETON, SPYDER, ZOMBIE};

class Mob : public Entity {
    protected:
        FilteredImage image;
        uint16_t height;
        uint16_t width;
        uint8_t speed;
        View view;
        uint16_t frame;
        uint16_t vertClips;
        uint16_t horClips;
        std::vector<SDL_Rect> clips;
        SDL_Rect quad;

    public:
        Mob(SDL_Renderer *renderer, MobType type, uint32_t anID, uint16_t aPosX,
            uint16_t aPosY);
        ~Mob();

        Mob(const Mob &copy) = delete;
        Mob(Mob&& other);
        Mob& operator=(Mob&& other);

        virtual void refreshPosition(MovementType move) override;
        virtual void render(Camera &camera) override;
        virtual bool collision(uint16_t x, uint16_t y) override;
        virtual void changeState(uint8_t aState) override;
        virtual void changeEquipment(EquipType equipType, uint8_t what) override;
        virtual void teleportTo(uint16_t posX, uint16_t posY) override;
};

#endif
