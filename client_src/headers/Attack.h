#ifndef __ATTACK_H__
#define __ATTACK_H__

#include "FilteredImage.h"
#include "Camera.h"
#include <vector>
#include "paths.h"

#define SWORD_ATTACK_HEIGHT 64
#define SWORD_ATTACK_WIDTH 100
#define SWORD_ATTACK_VERT_SPRITES 1
#define SWORD_ATTACK_HOR_SPRITES 8
#define AXE_ATTACK_HEIGHT 64
#define AXE_ATTACK_WIDTH 100
#define AXE_ATTACK_VERT_SPRITES 1
#define AXE_ATTACK_HOR_SPRITES 8
#define HAMMER_ATTACK_HEIGHT 64
#define HAMMER_ATTACK_WIDTH 100
#define HAMMER_ATTACK_VERT_SPRITES 1
#define HAMMER_ATTACK_HOR_SPRITES 8
#define FRESNO_BAR_ATTACK_HEIGHT 92
#define FRESNO_BAR_ATTACK_WIDTH 84
#define FRESNO_BAR_ATTACK_VERT_SPRITES 1
#define FRESNO_BAR_ATTACK_HOR_SPRITES 7
#define ELFIC_FLUTE_ATTACK_HEIGHT 76
#define ELFIC_FLUTE_ATTACK_WIDTH 76
#define ELFIC_FLUTE_ATTACK_VERT_SPRITES 6
#define ELFIC_FLUTE_ATTACK_HOR_SPRITES 5
#define BACULO_NUDOSO_ATTACK_HEIGHT 100
#define BACULO_NUDOSO_ATTACK_WIDTH 96
#define BACULO_NUDOSO_ATTACK_VERT_SPRITES 4
#define BACULO_NUDOSO_ATTACK_HOR_SPRITES 6
#define BACULO_ENGARZADO_ATTACK_HEIGHT 64
#define BACULO_ENGARZADO_ATTACK_WIDTH 64
#define BACULO_ENGARZADO_ATTACK_VERT_SPRITES 2
#define BACULO_ENGARZADO_ATTACK_HOR_SPRITES 5
#define SIMPLE_BOW_ATTACK_HEIGHT 16
#define SIMPLE_BOW_ATTACK_WIDTH 16
#define SIMPLE_BOW_ATTACK_VERT_SPRITES 1
#define SIMPLE_BOW_ATTACK_HOR_SPRITES 8
#define COMPOSED_BOW_ATTACK_HEIGHT 16
#define COMPOSED_BOW_ATTACK_WIDTH 16
#define COMPOSED_BOW_ATTACK_VERT_SPRITES 1
#define COMPOSED_BOW_ATTACK_HOR_SPRITES 8

enum AttackType { 
                SWORD_ATTACK = 1, 
                AXE_ATTACK, 
                HAMMER_ATTACK, 
                FRESNO_BAR_ATTACK,
                ELFIC_FLUTE_ATTACK, 
                BACULO_NUDOSO_ATTACK, 
                BACULO_ENGARZADO_ATTACK, 
                SIMPLE_BOW_ATTACK,
                COMPOSED_BOW_ATTACK 
                };

class Attack {
    private:
        uint8_t frame;
        uint8_t maxFrame;
        FilteredImage image;
        uint16_t height;
        uint16_t width;
        uint8_t vertClips;
        uint8_t horClips;
        uint16_t posX;
        uint16_t posY;
        std::vector<SDL_Rect> clips;
        SDL_Rect quad;
        bool ended;

    public:
        Attack(SDL_Renderer *renderer, AttackType type, uint16_t aPosX, 
               uint16_t aPosY);
        ~Attack();

        Attack(const Attack &copy) = delete;
        Attack(Attack &&other);
        Attack& operator=(Attack &&other);

        void render(Camera &camera);
        bool isEnded();
};

#endif
