#include "EventManager.h"
#include "QuitException.h"

EventManager::EventManager() {
}

EventManager::~EventManager() {
}

void EventManager::handle(SDL_Event &event) {
    // ver si tiene que ser bloqueante o no
    switch (event.type) {
        case SDL_QUIT:
            throw QuitException("Salida del programa.\n");
            break;

        case SDL_KEYDOWN: //apreto una tecla
            checkKeyDown(event);
        case SDL_KEYUP: //solto la tecla
            if (!writing) //dejar de caminar si es wasd
        /*
        SI NO ESTA ACTIVADO EL CHAT, ENVIAR AL SERVIDOR LA ACCION DE
        DEJAR DE MOVER AL PERSONAJE. esto hay que mandarlo para
        que todos los usuarios se enteren que un pj se dejo de mover

        SI ESTA ACTIVADO EL CHAT, NO HACER NADA EN PRINCIPIO
        */
        case SDL_MOUSEBUTTONDOWN: //hizo un click
        /*
        CHEQUEAR SI EL CLICK FUE EN EL INVENTARIO

        SI HIZO CLICK EN EL INVENTARIO ENVIAR AL SERVIDOR ESO

        SI NO FUE EN EL INVENTARIO CHEQUEAR SI CLICKEO ALGUNA ENTIDAD

        SI CLICKEO EN ALGUNA ENTIDAD ENVIAR AL SERVIDOR EL ID DE LA IDENTIDAD
        CLICKEADA
        */
        case SDL_TEXTINPUT:
        
        default:
            break;
    }
}

void EventManager::checkKeyDown(SDL_Event &event) {
    if (!writing) {
        switch (event.key.keysym.sym) {
            case SDLK_w: //arriba
                //generar codigo protocolo
                //enviar
                break;

            case SDLK_a: //izquierda
                //generar codigo protocolo
                //enviar
                break;

            case SDLK_s: //abajo
                //generar codigo protocolo
                //enviar
                break;

            case SDLK_d: //derecha
                //generar codigo protocolo
                //enviar
                break;

            case SDLK_KP_ENTER:
            case SDLK_RETURN:
                //hola gian, te hablo a vos
                //no se si lo queres chequear aca o en otro lado
                //aca iria el writing = true
                break;
            
            default:
                break;
        }
    } //gian, te vuelvo a hablar a vos, no se si queres poner aca un else
    //y chequear si es enter o backspace o lo haces en otro lado
}

void EventManager::checkKeyUp(SDL_Event &event) {
    if (!writing) {
        switch (event.key.keysym.sym) {
            case SDLK_w: //parar
            case SDLK_a: //parar
            case SDLK_s: //parar
            case SDLK_d: //parar
                //generar codigo protocolo
                //enviar
                break;
            
            default:
                break;
        }
    } //hola gian del futuro, te vuelvo a preguntar si pasa algo 
    //cuando el usuario suelta una tecla, avisame asi lo agrego
    //al else
}

void EventManager::checkClick(SDL_Event &event) {
    //chequear si clickeo inventario
    //si no chequeo inventario chequear si clickeo alguna entidad
}
