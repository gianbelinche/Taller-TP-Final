#ifndef __NPC_H__
#define __NPC_H__ 

#include <vector>

#include "FilteredImage.h"
#include "Camera.h"

enum View {UP, DOWN, LEFT, RIGHT}; //chequear

enum MovementType {MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, STOP};
/* CHEQUEAR SI CAMBIAR EL VALOR O NO (por protocolo), LA IDEA DEL STOP ES PARA DECIR QUE 
DEJO DE MOVERSE Y ASI VOLVER AL FRAME 0 */

class Entity {
    protected:
        FilteredImage image;
        /*se pueden cambiar los ints por otros tipos
        por ej, uint32 o uint16 o uint8*/
        int ID;
        int posX;
        int posY;
        int height;
        int width;
        int speed;
        View view;
        int frame;
        int vertClips;
        int horClips;
        std::vector<SDL_Rect> clips;
        SDL_Rect quad;
        bool destroyed;

    public:
        Entity(SDL_Renderer *renderer, int anID, int aPosX, int aPosY, View aView);
        ~Entity();

        Entity(const Entity &copy) = delete;
        Entity(Entity&& other);
        Entity& operator=(Entity&& other);

        void refreshPosition(MovementType move);
        virtual void render(Camera &camera);

        bool isDestroyed();
        void destroy();
};

#endif
