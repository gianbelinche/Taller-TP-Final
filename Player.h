#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player;

#include <vector>
#include "SDL2/SDL_events.h"
#include "FilteredImage.h"
#include "SpriteClipCreator.h"
#include "Camera.h"

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
#define HUMAN_BODY_WIDTH 25
#define HUMAN_BODY_HEIGHT 45
#define HUMAN_HEAD_WIDTH 17
#define HUMAN_HEAD_HEIGHT 17
#define ELF_BODY_WIDTH 25
#define ELF_BODY_HEIGHT 45
#define ELF_HEAD_WIDTH 17
#define ELF_HEAD_HEIGHT 17
#define DWARF_BODY_WIDTH 25 //CAMBIAR MEDIDAS DE DWARF Y GNOME
#define DWARF_BODY_HEIGHT 45 //CAMBIAR MEDIDAS DE DWARF Y GNOME
#define DWARF_HEAD_WIDTH 17
#define DWARF_HEAD_HEIGHT 17
#define GNOME_BODY_WIDTH 25 //CAMBIAR MEDIDAS DE DWARF Y GNOME
#define GNOME_BODY_HEIGHT 45 //CAMBIAR MEDIDAS DE DWARF Y GNOME
#define GNOME_HEAD_WIDTH 17
#define GNOME_HEAD_HEIGHT 17

/* CANTIDAD DE CUADROS POR ANIMACIÓN */
#define BODY_ANIMATION_FRAMES 5
#define BODY_ANIMATION_STATES 4
#define HEAD_ANIMATION_FRAMES 4

enum PlayerRace {HUMAN, ELF, DWARF, GNOME};

/* AGREGAR LA POSIBILIDAD DE QUE SI ESTA MUERTO SE RENDERICE COMO GHOST, 
LA IMAGEN ES IMG/GHOST.PNG */

class Player {
    private:
        int speed;
        int posX;
        int posY;
        int bodyWidth;
        int bodyHeight;
        int headWidth;
        int headHeight;
        int bodyFrameX;
        int bodyFrameY;
        int headFrameX;
        bool dead;
        FilteredImage bodyImage;
        FilteredImage headImage;
        std::vector <SDL_Rect> bodyClips;
        std::vector <SDL_Rect> headClips;

    public:
        Player(SDL_Renderer *aRenderer, PlayerRace aRace, int aPosX, int aPosY);
        ~Player();

        Player(const Player &copy) = delete;
        Player(Player&& other);
        Player& operator=(Player&& other);

        void move(SDL_Event& event);
        void render(Camera &camera);

        int getPosX();
        int getPosY();

        int getHeight();
        int getWidth();
};

#endif
