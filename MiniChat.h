#ifndef CLASS_MINI_CHAT
#define CLASS_MINI_CHAT
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <vector>


class MiniChat{
private:
    SDL_Renderer* mainRenderer;
    TTF_Font* gFont;
    std::string writing_word;
    std::vector<std::string> messages;
    void renderWord(std::string to_render_word,TTF_Font* gFont,int x, int y, int screen_w,int screen_h);
    //Devuelve un vector con sub strings, donde cada una tiene un largo de n, excepto la ultima que tiene el largo restante
    std::vector<std::string> getPartialString(std::string string,int n);
public:
    MiniChat(SDL_Renderer* mainRenderer);
    void render(int screen_w, int screen_h,TTF_Font* gFont);
    void putCharacter(std::string c);
    void deleteCharacter();    
    void addMessage(std::string message);
    void sendMessage();

};

#endif

