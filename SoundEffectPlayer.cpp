#include "SoundEffectPlayer.h"

void SoundEffectPlayer::add(const int id,std::string sound){
    SoundEffect sound_effect(sound);
    sounds.insert(std::pair<int,SoundEffect>(id,std::move(sound_effect)));
}

void SoundEffectPlayer::play(const int id){
    sounds.at(id).play();
}
