#include "LoginScreen.h"
#define FONT_SIZE 50

LoginScreen::LoginScreen(SDL_Renderer* mainRenderer) : 
mainRenderer(mainRenderer),background(NULL),text_input(NULL),
text1(NULL),text2(NULL), error(NULL){
    Image background(mainRenderer);
    background.loadFromFile("Layout_graphics/Login/back_log_fix.png");
    this->background = std::move(background);
    this->gFont = TTF_OpenFont("Fonts/OpenSans.ttf", FONT_SIZE);

    Image text_input(mainRenderer);
    text_input.loadFromFile("Layout_graphics/Login/text_input_2.png");
    this->text_input = std::move(text_input);

    Text text1(mainRenderer);
    text1.loadText("Host",gFont);
    this->text1 = std::move(text1);

    Text text2(mainRenderer);
    text2.loadText("Puerto",gFont);
    this->text2 = std::move(text2);
}

void LoginScreen::changeToUserInput(){
    Text text1(mainRenderer);
    text1.loadText("Usuario",gFont);
    this->text1 = std::move(text1);

    Text text2(mainRenderer);
    text2.loadText("Contraseña",gFont);
    this->text2 = std::move(text2);
}

void LoginScreen::showError(std::string error){
    Text err(mainRenderer);
    err.loadText(error,gFont);
    this->error = std::move(err);
}

void LoginScreen::render(int screen_w,int screen_h){
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rq = {0,0,screen_w,screen_h};
    background.render(0,0,&clip,&rq);
    rq = {0,0,screen_w * 2 / 5, screen_h / 10};
    text_input.render(screen_w * 3 / 10, screen_h * 3/ 10,&clip,&rq);
    text_input.render(screen_w * 3 / 10, screen_h * 7/ 10,&clip,&rq);
    text1.render(screen_w * 3 / 10,screen_h * 2/ 10,&clip,&rq);
    text2.render(screen_w * 3 / 10,screen_h * 6/ 10,&clip,&rq);
}

