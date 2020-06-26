#include "EventManager.h"
#include "QuitException.h"
#include "SDLError.h"
#include <vector>
#include <iostream>

#define MOVE_CHAR 0

EventManager::EventManager(EntityManager &anEntityManager, uint32_t aPlayerID, 
                           MessageQueue &aMsgQueue) : 
                                                entityManager(anEntityManager),
                                                playerID(aPlayerID), 
                                                msgQueue(aMsgQueue) {}

EventManager::~EventManager() {}

void EventManager::run() {
    try {
        while (SDL_WaitEvent(&event) != 0) {
            this->handle(event);
        }
        throw SDLError("Error en WaitEvent.");
    } catch(const QuitException &e) {
        std::cerr << e.what() << '\n';
    }
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

        case SDL_KEYDOWN:
            checkKeyDown(event);

        case SDL_KEYUP:
            checkKeyUp(event);

        case SDL_MOUSEBUTTONDOWN:
            checkClick(event);

        case SDL_TEXTINPUT:
        //Aca habria que hacer esto
        //chat.putCharacter(event.text.text);
        default:
            break;
    }
}

void EventManager::checkKeyDown(SDL_Event &event) {
    std::vector<uint32_t> msg;
    if (!writing) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                msg.emplace_back(MOVE_CHAR);
                msg.emplace_back(playerID);
                msg.emplace_back(MOVE_UP);
                break;

            case SDLK_a:
                msg.emplace_back(MOVE_CHAR);
                msg.emplace_back(playerID);
                msg.emplace_back(MOVE_LEFT);
                break;

            case SDLK_s:
                msg.emplace_back(MOVE_CHAR);
                msg.emplace_back(playerID);
                msg.emplace_back(MOVE_DOWN);
                break;

            case SDLK_d:
                msg.emplace_back(MOVE_CHAR);
                msg.emplace_back(playerID);
                msg.emplace_back(MOVE_RIGHT);
                break;

            case SDLK_KP_ENTER:
            case SDLK_RETURN:
                //aca iria un
                //SDL_StartTextInput();
                //writing = true;
                break;
            
            default:
                break;
        }
        msgQueue.push(msg);
    } else {
        switch (event.key.keysym.sym) {
            case SDLK_KP_ENTER:
            case SDLK_RETURN:
                //chat.sendMessage();
                //SDL_StopTextInput();
                break;

            case SDLK_BACKSPACE:
                //chat.deleteCharacter();
                break;

            default:
                break;
        }
    }
}

void EventManager::checkKeyUp(SDL_Event &event) {
    std::vector<uint32_t> msg;
    if (!writing) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_a:
            case SDLK_s:
            case SDLK_d:
                msg.emplace_back(MOVE_CHAR);
                msg.emplace_back(playerID);
                msg.emplace_back(STOP);
                msgQueue.push(msg);
                break;
            
            default:
                break;
        }
    }
}

void EventManager::checkClick(SDL_Event &event) {
    //Esto aun no lo tengo bien decidido pero, lo que tengo es esto
    /*std::string selected = inventory.select(event.button.x,event.button.y,SCREEN_WIDTH,SCREEN_HEIGHT);
    if (selected != "")
    std::cout << selected << std::endl;*/
    //es decir, le digo al inventario que seleccione el objeto de la pos x,y y devuelva el objeto de esa pos, si no hay ningun objeto
    //o si clickeo afuera del inventario devuelve "", habria que diferenciar si clickeo afuera o en una casilla vacia, tal vez podria hacer que
    //devuelva la casilla, eso lo resolveria, ya vere que hacer
    if (0/*Click en inventario*/) {

    } else {
        //else entitymanager.checkClickEntities(camera, x, y);
    }
}
