#ifndef CLASS_LOGIN_SCREEN
#define CLASS_LOGIN_SCREEN
#include "Image.h"
#include "Text.h"
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class LoginScreen{
private:
    SDL_Renderer* mainRenderer;
    Image background;
    Image text_input;
    Text  text1;
    Text  text2;
    Text  error;
    TTF_Font* gFont;
public:
    LoginScreen(SDL_Renderer* mainRenderer);
    void render(int screen_w,int screen_h);
    void changeToUserInput();
    void showError(std::string error);    
};

#endif
