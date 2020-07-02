#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player;

#include <vector>
#include "SDL2/SDL_events.h"
#include "FilteredImage.h"
#include "SpriteClipCreator.h"
#include "Camera.h"
#include "Entity.h"

/* VELOCIDAD DEL JUGADOR */
#define PLAYER_SPEED 6

/* RUTA A LA IMAGEN DEL JUGADOR */
#define HUMAN_BODY_PATH "img/humanbody.png"
#define HUMAN_HEAD_PATH "img/humanhead.png"
#define ELF_BODY_PATH   "img/elfbody.png"
#define ELF_HEAD_PATH   "img/elfhead.png"
#define DWARF_BODY_PATH "img/dwarfbody.png"
#define DWARF_HEAD_PATH "img/dwarfhead.png"
#define GNOME_BODY_PATH "img/gnomebody.png"
#define GNOME_HEAD_PATH "img/gnomehead.png"

#define GHOST_PATH      "img/ghost.png"

/* MEDIDAS DEL JUGADOR */
#define PLAYER_BODY_WIDTH 25
#define PLAYER_BODY_HEIGHT 45
#define PLAYER_HEAD_WIDTH 17
#define PLAYER_HEAD_HEIGHT 17

#define GHOST_WIDTH 29
#define GHOST_HEIGHT 32

/* CANTIDAD DE CUADROS POR ANIMACIÓN */
#define BODY_ANIMATION_FRAMES 5
#define BODY_ANIMATION_STATES 4
#define HEAD_ANIMATION_FRAMES 4
#define HEAD_ANIMATION_STATES 1
#define GHOST_ANIMATION_FRAMES 3
#define GHOST_ANIMATION_STATES 4

enum PlayerRace {HUMAN, ELF, DWARF, GNOME};

class Player : public Entity {
    private:
        uint8_t speed;
        uint16_t bodyWidth;
        uint16_t bodyHeight;
        uint16_t headWidth;
        uint16_t headHeight;
        uint16_t ghostWidth;
        uint16_t ghostHeight;
        uint8_t bodyFrameX;
        uint8_t bodyFrameY;
        uint8_t headFrameX;
        uint8_t state;
        Equippable weapon;
        Equippable armor;
        Equippable shield;
        Equippable helmet;
        FilteredImage bodyImage;
        FilteredImage headImage;
        FilteredImage ghostImage;

        std::vector <SDL_Rect> bodyClips;
        std::vector <SDL_Rect> headClips;
        std::vector <SDL_Rect> ghostClips;
        void renderGhost(Camera &camera);
        void renderPlayer(Camera &camera);

    public:
        Player(SDL_Renderer *aRenderer, PlayerRace aRace, uint32_t anID, 
               uint16_t aPosX, uint16_t aPosY, uint8_t aState, 
               EquipType aWeapon, EquipType anArmor, EquipType aShield, 
               EquipType aHelmet);
        ~Player();

        Player(const Player &copy) = delete;
        Player(Player&& other);
        Player& operator=(Player&& other);

        virtual void refreshPosition(MovementType move) override;
        virtual void render(Camera &camera) override;
        virtual bool collision(uint16_t x, uint16_t y) override;
        virtual void changeState(uint8_t aState) override;
        virtual void changeEquipment(EquipType equipType, uint8_t what) override;

        uint16_t getHeight();
        uint16_t getWidth();
};

#endif
