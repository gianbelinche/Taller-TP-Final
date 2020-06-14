#ifndef CLASS_MINI_CHAT
#define CLASS_MINI_CHAT
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"


class MiniChat{
private:
    SDL_Renderer* mainRenderer;
    TTF_Font* gFont;
    std::string writing_word;
public:
    MiniChat(SDL_Renderer* mainRenderer);
    void render(int screen_w, int screen_h,TTF_Font* gFont);
    void putCharacter(std::string c);
    void deleteCharacter();    

};

#endif

