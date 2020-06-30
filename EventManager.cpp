#include "EventManager.h"
#include "QuitException.h"
#include "SDLError.h"
#include <vector>
#include <iostream>

#define MOVE_CHAR 0

EventManager::EventManager(EntityManager &anEntityManager, uint32_t aPlayerID, 
                           BlockingMsgQueue &aMsgQueue, Camera &aCamera, 
                           ClientProtocol &aClProtocol) : 
                                                entityManager(anEntityManager),
                                                playerID(aPlayerID), 
                                                msgQueue(aMsgQueue),
                                                camera(aCamera),
                                                clProtocol(aClProtocol) {}

EventManager::~EventManager() {}

void EventManager::run() {
    try {
        while (SDL_WaitEvent(&event) != 0) {
            this->handle(event);
        }
        throw SDLError("Error en WaitEvent.");
    } catch(const QuitException &e) {
        msgQueue.close();
    } catch (std::exception &e) {
        std::cerr << "EventManager: ";
        std::cerr << e.what() << '\n';
        msgQueue.close();
    } catch (...) {
        std::cerr << "EventManager: ";
        std::cerr << "Error EventManager: unknown." << '\n';
        msgQueue.close();
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
            throw QuitException("Salida del programa\n");
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
                clProtocol.makeMsgMove(playerID, MOVE_UP, msg);
                msgQueue.push(msg);
                break;

            case SDLK_a:
                clProtocol.makeMsgMove(playerID, MOVE_LEFT, msg);
                msgQueue.push(msg);
                break;

            case SDLK_s:
                clProtocol.makeMsgMove(playerID, MOVE_DOWN, msg);
                msgQueue.push(msg);
                break;

            case SDLK_d:
                clProtocol.makeMsgMove(playerID, MOVE_RIGHT, msg);
                msgQueue.push(msg);
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
    if (!writing && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_a:
            case SDLK_s:
            case SDLK_d:
                clProtocol.makeMsgMove(playerID, STOP, msg);
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
        std::vector<uint32_t> msg;
        clProtocol.makeMsgClickInventory(playerID, 1/*SLOT*/, msg);
    } else {
        uint32_t IDClicked = entityManager.checkClickEntities(camera, 
                                                              event.button.x, 
                                                              event.button.y);
        if (IDClicked) {
            std::vector<uint32_t> msg;
            clProtocol.makeMsgClickEntity(IDClicked, msg);
        }
    }
}
