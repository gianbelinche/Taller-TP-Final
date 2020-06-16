#include "MiniChat.h"
#include "Text.h"
#define MESSAGES_MAX_SIZE 10

MiniChat::MiniChat(SDL_Renderer* mainRenderer) : mainRenderer(mainRenderer){}

std::vector<std::string> MiniChat::getPartialString(std::string string,int n){
    std::vector<std::string> partial_strings;
    for (int i = 0; i < string.length(); i += n){
        partial_strings.push_back(string.substr(i,n));
    }
    return std::move(partial_strings);
}

void MiniChat::renderWord(std::string to_render_word,TTF_Font* gFont,int x, int y, int screen_w,int screen_h){
    Text word(mainRenderer);
    word.loadText(to_render_word,gFont);
    SDL_Rect clip = {0,0,screen_w,screen_h};
    int width = screen_w * to_render_word.length() / 80;
    SDL_Rect rQuad = {0,0,width,screen_h / 20};
    word.render(x,y,&clip,&rQuad);
}

void MiniChat::render(int screen_w, int screen_h,TTF_Font* gFont){
    int lines = 0;
    int x = screen_w * 205 / 300;
    int y = screen_h * 17 / 20;
    for (int i = messages.size() - 1; i >= 0; i--){
        std::vector<std::string> partial_strings = this->getPartialString(messages[i],21);
        for (int j = partial_strings.size() - 1; j >= 0;j--){
            this->renderWord(partial_strings[j],gFont,x,y,screen_w,screen_h);
            lines++;
            y -= screen_h / 20;
            if (lines > MESSAGES_MAX_SIZE) break;
        }
        if (lines > MESSAGES_MAX_SIZE) break;
    }


    if (writing_word.length() > 0){
        std::string to_render_word = writing_word;
        if (writing_word.length() > 21){
            to_render_word = writing_word.substr(writing_word.length() - 21);
        }
        this->renderWord(to_render_word,gFont,screen_w * 205 / 300,screen_h * 18 / 20,screen_w,screen_h);
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

void MiniChat::addMessage(std::string message){
    messages.push_back(message);
    if (messages.size() > MESSAGES_MAX_SIZE){
        messages.erase(messages.begin());
    }
}

void MiniChat::sendMessage(){
    this->addMessage(writing_word);
    writing_word.clear();
}