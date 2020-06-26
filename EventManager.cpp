#include "EventManager.h"
#include "QuitException.h"
#include <vector>

#define MOVE_CHAR 0

EventManager::EventManager(EntityManager &anEntityManager, uint32_t aPlayerID, 
                           MessageQueue &aMsgQueue) : 
                                                entityManager(anEntityManager),
                                                playerID(aPlayerID), 
                                                msgQueue(aMsgQueue) {}

EventManager::~EventManager() {}

void EventManager::handle(SDL_Event &event) {
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
            // GIAN
        
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
                //Gian, haz lo tuyo
                break;
            
            default:
                break;
        }
        msgQueue.push(msg);
    } else {
        switch (event.key.keysym.sym) {
            case SDLK_KP_ENTER:
            case SDLK_RETURN:
            case SDLK_BACKSPACE:
                //Gian, haz lo tuyo
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
    if (/*Click en inventario*/) {

    } else {
        //else entitymanager.checkClickEntities(camera, x, y);
    }
}
