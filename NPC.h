#ifndef __NPC_H__
#define __NPC_H__ 

#include <vector>

#include "FilteredImage.h"
#include "Camera.h"
#include "Entity.h"

enum NPCType {SPYDER, SKELETON, GOBLIN, ZOMBIE, BANKER, MERCHANT, HEALER};

class NPC : public Entity {
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
        NPC(SDL_Renderer *renderer, uint32_t anID, uint16_t aPosX,
            uint16_t aPosY);
        ~NPC();

        NPC(const NPC &copy) = delete;
        NPC(NPC&& other);
        NPC& operator=(NPC&& other);

        virtual void refreshPosition(MovementType move) override;
        virtual void render(Camera &camera) override;
        virtual bool collision(uint16_t x, uint16_t y) override;
        virtual void kill() override;
};

#endif
