#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <SDL2/SDL.h>

class EventManager {
    private:
        bool writing;
        void checkKeyDown(SDL_Event &event);
        void checkKeyUp(SDL_Event &event);
        void checkClick(SDL_Event &event);
        
    public:
        EventManager();
        ~EventManager();
        void handle(SDL_Event &event);
};

#endif
