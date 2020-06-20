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

/* MEDIDAS DEL JUGADOR */
/*#define HUMAN_BODY_WIDTH 25
#define HUMAN_BODY_HEIGHT 45
#define HUMAN_HEAD_WIDTH 17
#define HUMAN_HEAD_HEIGHT 17
#define ELF_BODY_WIDTH 25
#define ELF_BODY_HEIGHT 45
#define ELF_HEAD_WIDTH 17
#define ELF_HEAD_HEIGHT 17
#define DWARF_BODY_WIDTH 25
#define DWARF_BODY_HEIGHT 45
#define DWARF_HEAD_WIDTH 17
#define DWARF_HEAD_HEIGHT 17
#define GNOME_BODY_WIDTH 25
#define GNOME_BODY_HEIGHT 45
#define GNOME_HEAD_WIDTH 17
#define GNOME_HEAD_HEIGHT 17*/

/* CANTIDAD DE CUADROS POR ANIMACIÓN */
#define BODY_ANIMATION_FRAMES 5
#define BODY_ANIMATION_STATES 4
#define HEAD_ANIMATION_FRAMES 4

enum PlayerRace {HUMAN, ELF, DWARF, GNOME};

/* AGREGAR LA POSIBILIDAD DE QUE SI ESTA MUERTO SE RENDERICE COMO GHOST, 
LA IMAGEN ES IMG/GHOST.PNG */

/* PUSE CUERPOS REPETIDOS PORQUE HACER QUE COINCIDAN LA CABEZA Y EL CUERPO
DEL ENANO Y DEL GNOMO ES MUY DIFICIL */

class Player : public Entity {
    private:
        uint8_t speed;
        uint16_t bodyWidth;
        uint16_t bodyHeight;
        uint16_t headWidth;
        uint16_t headHeight;
        uint16_t bodyFrameX;
        uint16_t bodyFrameY;
        uint16_t headFrameX;
        bool dead;
        FilteredImage bodyImage;
        FilteredImage headImage;
        std::vector <SDL_Rect> bodyClips;
        std::vector <SDL_Rect> headClips;

    public:
        Player(SDL_Renderer *aRenderer, PlayerRace aRace, uint32_t anID, 
               uint16_t aPosX, uint16_t aPosY);
        ~Player();

        Player(const Player &copy) = delete;
        Player(Player&& other);
        Player& operator=(Player&& other);

        virtual void refreshPosition(MovementType move) override;
        virtual void render(Camera &camera) override;
        virtual bool collision(uint16_t x, uint16_t y) override;

        uint16_t getPosX();
        uint16_t getPosY();

        uint16_t getHeight();
        uint16_t getWidth();
};

#endif
