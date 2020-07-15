#include "../headers/Music.h"
#include "../headers/SDLError.h"

Music::Music(std::string path){
    gMusic = Mix_LoadMUS(path.c_str());
    if (gMusic == NULL){
        throw SDLError("Error al crear musica: %s\n",Mix_GetError());
    }
}

Music::~Music(){
    if (gMusic != NULL){
        Mix_FreeMusic(gMusic);
    }
}

void Music::play(){
    Mix_PlayMusic(gMusic, -1);
}

Music::Music(Music&& other){
    this->gMusic = other.gMusic;
    other.gMusic = NULL;

}

Music& Music::operator=(Music&& other){
    if (this == &other) {
        return *this;
    }

    this->gMusic = other.gMusic;
    other.gMusic = NULL;
    
    return *this;
}