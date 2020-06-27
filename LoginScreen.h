#ifndef CLASS_LOGIN_SCREEN
#define CLASS_LOGIN_SCREEN
#include "Image.h"
#include "Text.h"
#include <string>
#include <vector>
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
    Text  title;
    TTF_Font* gFont;
    int text1_l;
    int text2_l;
    int title_l;
    std::string input1;
    std::string input2;
    int actual;
    void renderWord(std::string to_render_word,int x, int y,int w,int h,int screen_w,int screen_h);
public:
    LoginScreen(SDL_Renderer* mainRenderer);
    void render(int screen_w,int screen_h);
    void changeToUserInput();
    void showError(std::string error);
    void select(int x,int y,int screen_w,int screen_h);
    void write(std::string c);  
    void deleteCharacter();
    std::vector<std::string> send();  
};

#endif
