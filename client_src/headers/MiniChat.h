#ifndef CLASS_MINI_CHAT
#define CLASS_MINI_CHAT

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include "Camera.h"

class MiniChat{
private:
    SDL_Renderer* mainRenderer;
    TTF_Font* gFont;
    std::string writing_word;
    std::vector<std::string> messages;
    void renderWord(std::string to_render_word,int x, int y, int screen_w,int screen_h);
    //Devuelve un vector con sub strings, donde cada una tiene un largo de n, excepto la ultima que tiene el largo restante
    std::vector<std::string> getPartialString(std::string string,int n);
public:
    MiniChat(SDL_Renderer* mainRenderer);
    MiniChat(const MiniChat& copy) = delete;
    MiniChat& operator=(const MiniChat& copy) = delete;
    void render(const Camera& camera);
    //Agrega el caracter c al mensaje actual
    void putCharacter(std::string c);
    //Borra el ultimo caracter del mensaje actual
    void deleteCharacter();
    //Añade un mensaje al historial de mensajes    
    void addMessage(std::string message);
    //Añade el mensaje actual al historial de mensajes y lo vacia
    std::string sendMessage();
    ~MiniChat();

};

#endif

