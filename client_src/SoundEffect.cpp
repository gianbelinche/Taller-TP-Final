#include "SoundEffect.h"
#include "SDLError.h"

SoundEffect::SoundEffect(std::string path){
    gSoundEffect = Mix_LoadWAV(path.c_str());
    if (gSoundEffect == NULL){
        throw SDLError("Error al crear SoundEffect: %s\n",Mix_GetError());
    }
}

SoundEffect::~SoundEffect(){
    if (gSoundEffect != NULL){
        Mix_FreeChunk(gSoundEffect);
    }
}

void SoundEffect::play(){
    Mix_PlayChannel(-1, gSoundEffect, 0);
}

SoundEffect::SoundEffect(SoundEffect&& other){
    this->gSoundEffect = other.gSoundEffect;
    other.gSoundEffect = NULL;

}

SoundEffect& SoundEffect::operator=(SoundEffect&& other){
    if (this == &other) {
        return *this;
    }

    this->gSoundEffect = other.gSoundEffect;
    other.gSoundEffect = NULL;
    
    return *this;
}