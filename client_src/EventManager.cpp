#include "EventManager.h"
#include "QuitException.h"
#include "SDLError.h"
#include <vector>
#include <iostream>

#define MOVE_CHAR 0

EventManager::EventManager(EntityManager &anEntityManager, uint32_t aPlayerID, 
                           BlockingMsgQueue &aMsgQueue, Camera &aCamera, 
                           ClientProtocol &aClProtocol, MiniChat &chat,
                           GraphicInventory &inventory) : 
                                                entityManager(anEntityManager),
                                                playerID(aPlayerID), 
                                                msgQueue(aMsgQueue),
                                                camera(aCamera),
                                                clProtocol(aClProtocol),
                                                chat(chat),
                                                inventory(inventory) {}

EventManager::~EventManager() {}

void EventManager::run() {
    SDL_StopTextInput();
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
    //SDL_StopTextInput(); //Habria que hacer esto al salir del login
    //Porque por default el text input esta activado
    // ver si tiene que ser bloqueante o no
    switch (event.type) {
        case SDL_QUIT:
            throw QuitException("Salida del programa\n"); 
            break;

        case SDL_KEYDOWN:
            checkKeyDown(event);
            break;

        case SDL_KEYUP:
            checkKeyUp(event);
            break;

        case SDL_MOUSEBUTTONDOWN:
            checkClick(event);
            break;

        case SDL_TEXTINPUT:
            chat.putCharacter(event.text.text);
            break;
        default:
            break;
    }
}

void EventManager::checkKeyDown(SDL_Event &event) {
    std::vector<uint32_t> msg;
    std::string command = "";
    if (!writing) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                msg = clProtocol.makeMsgMove(playerID,MOVE_UP);
                msgQueue.push(msg);
                break;

            case SDLK_a:
                msg = clProtocol.makeMsgMove(playerID, MOVE_LEFT);
                msgQueue.push(msg);
                break;

            case SDLK_s:
                msg = clProtocol.makeMsgMove(playerID, MOVE_DOWN);
                msgQueue.push(msg);
                break;

            case SDLK_d:
                msg = clProtocol.makeMsgMove(playerID, MOVE_RIGHT);
                msgQueue.push(msg);
                break;

            case SDLK_KP_ENTER:
            case SDLK_RETURN:
                SDL_StartTextInput();
                writing = true;
                break;
            
            default:
                break;
        }
    } else {
        switch (event.key.keysym.sym) {
            case SDLK_KP_ENTER:
            case SDLK_RETURN:
                command = chat.sendMessage();
                SDL_StopTextInput();
                writing = false;
                msg = clProtocol.makeMsgSendCommand(playerID,command);
                msgQueue.push(msg);
                break;

            case SDLK_BACKSPACE:
                chat.deleteCharacter();
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
                msg = clProtocol.makeMsgMove(playerID, STOP);
                msgQueue.push(msg);
                break;
            
            default:
                break;
        }
    }
}

void EventManager::checkClick(SDL_Event &event) {
    uint32_t slot = inventory.select(event.button.x,event.button.y,camera);
    if (slot  != -1) {
        std::vector<uint32_t> msg = 
        clProtocol.makeMsgClickInventory(playerID, slot);
        msgQueue.push(msg);
    } else {
        uint32_t IDClicked = entityManager.checkClickEntities(camera, 
                                                              event.button.x, 
                                                              event.button.y);
        if (IDClicked) {
            std::vector<uint32_t> msg =
            clProtocol.makeMsgClickEntity(IDClicked);
            msgQueue.push(msg);
        }
    }
}
