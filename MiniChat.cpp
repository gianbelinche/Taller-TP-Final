#include "MiniChat.h"
#include "Text.h"

MiniChat::MiniChat(SDL_Renderer* mainRenderer) : mainRenderer(mainRenderer){}

void MiniChat::render(int screen_w, int screen_h,TTF_Font* gFont){
    if (writing_word.length() > 0){
        Text word(mainRenderer);
        std::string to_render_word = writing_word;
        if (writing_word.length() > 21){
            to_render_word = writing_word.substr(writing_word.length() - 21);
        }
        word.loadText(to_render_word,gFont);
        SDL_Rect clip = {0,0,screen_w,screen_h};
        int width = screen_w * to_render_word.length() / 80;
        SDL_Rect rQuad = {0,0,width,screen_h / 20};
        word.render(screen_w * 205 / 300,screen_h * 18 / 20,&clip,&rQuad);
    }
}


void MiniChat::putCharacter(std::string c){
    writing_word += c;
}


void MiniChat::deleteCharacter(){
    if (writing_word != ""){
        writing_word.pop_back();
    }
}