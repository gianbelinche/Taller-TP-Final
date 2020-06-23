#include "EventManager.h"
#include "QuitException.h"

EventManager::EventManager() {
}

EventManager::~EventManager() {
}

void EventManager::handle(SDL_Event &event) {
    //Hola guido te voy poniendo cosas que creo que vamos a necesitar
    //Al principio de todo hay que poner un
    //SDL_StopTextInput();
    //Porque por default el text input esta activado
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
        //Aca habria que hacer esto
        //chat.putCharacter(event.text.text);
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
                //hola guido, aca iria un
                //SDL_StartTextInput();
                //writing = true;
                break;
            
            default:
                break;
        }
    } //gian, te vuelvo a hablar a vos, no se si queres poner aca un else
    //y chequear si es enter o backspace o lo haces en otro lado
    //si guido, me parece buena idea, algo asi seria
    /*else {
        switch (event.key.keysym.sym){
            case SDLK_RETURN:
                chat.sendMessage();
                SDL_StopTextInput();
                break;
            case SDLK_BACKSPACE:
                chat.deleteCharacter();
                break;    
        }
    }*/
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
    //hola guido del pasado, no no pasa nada en este caso
}

void EventManager::checkClick(SDL_Event &event) {
    //chequear si clickeo inventario
    //if click_en_inventario
    //si no chequeo inventario chequear si clickeo alguna entidad
    //else entitymanager.check(xdelclick,ydelclick)
    //Esto aun no lo tengo bien decidido pero, lo que tengo es esto
    /*std::string selected = inventory.select(event.button.x,event.button.y,SCREEN_WIDTH,SCREEN_HEIGHT);
    if (selected != "")
    std::cout << selected << std::endl;*/
    //es decir, le digo al inventario que seleccione el objeto de la pos x,y y devuelva el objeto de esa pos, si no hay ningun objeto
    //o si clickeo afuera del inventario devuelve "", habria que diferenciar si clickeo afuera o en una casilla vacia, tal vez podria hacer que
    //devuelva la casilla, eso lo resolveria, ya vere que hacer
    //Saludos guido, que tengas un buen dia
    
}
