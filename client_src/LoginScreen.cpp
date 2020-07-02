#include "LoginScreen.h"
#define FONT_SIZE 50
#define TEXT_INPUT_W (screen_w * 2 / 5)
#define TEXT_INPUT_H (screen_h / 8)
#define TEXT_INPUT_X (screen_w * 3 / 10)
#define TEXT_INPUT_Y (screen_h * 3/ 10)
#define TEXT_INPUT_Y_2 (screen_h * 7/ 10)
#define TEXT_W (screen_w / 24)
#define TEXT_H (screen_h / 10)
#define TEXT_X (screen_w * 3 / 10)
#define TEXT1_Y (screen_h * 2/ 10)
#define TEXT2_Y (screen_h * 6/ 10)
#define ERROR_W (screen_w / 2)
#define ERROR_H (screen_h / 10)
#define ERROR_X (screen_w / 4)
#define ERROR_Y (screen_h / 2)
#define TITLE_H (screen_h / 10)
#define MAX_LETTERS_IN_A_WORD 27

LoginScreen::LoginScreen(SDL_Renderer* mainRenderer) : 
mainRenderer(mainRenderer),background(NULL),text_input(NULL),
text1(NULL),text2(NULL), error(NULL),title(NULL),active(true){
    Image background(mainRenderer);
    background.loadFromFile("Layout_graphics/Login/back_log_fix.png");
    this->background = std::move(background);
    this->gFont = TTF_OpenFont("Fonts/OpenSans.ttf", FONT_SIZE);

    Image text_input(mainRenderer);
    text_input.loadFromFile("Layout_graphics/Login/text_input_2.png");
    this->text_input = std::move(text_input);

    Text text1(mainRenderer);
    std::string host = "Host";
    text1.loadText(host,gFont);
    this->text1 = std::move(text1);
    text1_l = host.length();
    

    Text text2(mainRenderer);
    std::string port = "Puerto";
    text2.loadText(port,gFont);
    this->text2 = std::move(text2);
    text2_l = port.length();

    Text title(mainRenderer);
    std::string title_str = "Ingresar host y puerto";
    title.loadText(title_str,gFont);
    this->title = std::move(title);
    title_l = title_str.length();

    input1 = "";
    input2 = "";
    actual = 0;
}

void LoginScreen::changeToUserInput(){
    Text text1(mainRenderer);
    std::string user = "Usuario";
    text1.loadText(user,gFont);
    this->text1 = std::move(text1);
    text1_l = user.length();

    Text text2(mainRenderer);
    std::string pass = "Contrasena";
    text2.loadText(pass,gFont);
    this->text2 = std::move(text2);
    text2_l = pass.length();

    Text title(mainRenderer);
    std::string title_str = "Ingresar usuario y constrasena";
    title.loadText(title_str,gFont);
    this->title = std::move(title);
    title_l = title_str.length();

    input1 = "";
    input2 = "";

    Text error(NULL);
    this->error = std::move(error);
}

void LoginScreen::showError(std::string error){
    Text err(mainRenderer,187,9,9);
    err.loadText(error,gFont);
    this->error = std::move(err);
}

void LoginScreen::renderWord(std::string to_render_word,int x, int y,int w,int h,int screen_w,int screen_h){
    Text word(mainRenderer,255,255,255);
    word.loadText(to_render_word,gFont);
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rQuad = {0,0,w,h};
    word.render(x,y,&clip,&rQuad);
}

void LoginScreen::render(Camera& camera){
    int screen_w = camera.getWidth();
    int screen_h = camera.getHeight();
    SDL_Rect clip = {0,0,screen_w,screen_h};
    SDL_Rect rq = {0,0,screen_w,screen_h};
    background.render(0,0,&clip,&rq);
    rq = {0,0,TEXT_INPUT_W, TEXT_INPUT_H};
    text_input.render(TEXT_INPUT_X, TEXT_INPUT_Y,&clip,&rq);
    text_input.render(TEXT_INPUT_X, TEXT_INPUT_Y_2,&clip,&rq);
    rq = {0,0,TEXT_W * text1_l,TEXT_H};
    text1.render(TEXT_X,TEXT1_Y,&clip,&rq);
    rq = {0,0,TEXT_W * text2_l,TEXT_H};
    text2.render(TEXT_X,TEXT2_Y,&clip,&rq);
    rq = {0,0,ERROR_W,ERROR_H};
    error.render(ERROR_X,ERROR_Y,&clip,&rq);
    rq = {0,0,screen_w,TITLE_H};
    title.render(0,0,&clip,&rq);
    if (input1.length() > 0){
        std::string to_render_word = input1;
        if (input1.length() > MAX_LETTERS_IN_A_WORD){
            to_render_word = input1.substr(input1.length() - MAX_LETTERS_IN_A_WORD);
        }
        this->renderWord(to_render_word,TEXT_INPUT_X * 110 / 100,TEXT_INPUT_Y * 105 / 100,screen_w / 80 * to_render_word.length(),TEXT_INPUT_H * 85 / 100,screen_w,screen_h);
    }
    if (input2.length() > 0){
        std::string to_render_word = input2;
        if (input2.length() > MAX_LETTERS_IN_A_WORD){
            to_render_word = input2.substr(input2.length() - MAX_LETTERS_IN_A_WORD);
        }
        this->renderWord(to_render_word,TEXT_INPUT_X * 110 / 100,TEXT_INPUT_Y_2,screen_w / 80 * to_render_word.length(),TEXT_INPUT_H * 85 / 100,screen_w,screen_h);
    }
    
}

void LoginScreen::write(std::string c){
    if (actual == 0){
        input1 += c;
    }
    if (actual == 1){
        input2 += c;
    }
}

std::vector<std::string> LoginScreen::send(){
    std::vector<std::string> vector;
    vector.push_back(input1);
    vector.push_back(input2);
    input1 = "";
    input2 = "";
    return std::move(vector);
}

void LoginScreen::deleteCharacter(){
    if (actual == 0){
        if (input1 != "")
            input1.pop_back();
    }
    if (actual == 1){
        if (input2 != "")
            input2.pop_back();
    }
}

void LoginScreen::select(int x,int y,Camera& camera){
    int screen_w = camera.getWidth();
    int screen_h = camera.getHeight();
    if (x >= TEXT_INPUT_X && x <= TEXT_INPUT_X + TEXT_INPUT_W){
        if (y >= TEXT_INPUT_Y && y <= TEXT_INPUT_Y + TEXT_INPUT_H)
            actual = 0;
        if (y >= TEXT_INPUT_Y_2 && y <= TEXT_INPUT_Y_2 + TEXT_INPUT_H)
            actual = 1;    
    }
}

void LoginScreen::deactivate(){
    active = false;
}

bool LoginScreen::is_active(){
    return active;
} 