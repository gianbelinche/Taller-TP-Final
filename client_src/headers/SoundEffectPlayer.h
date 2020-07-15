#ifndef CLASS_SOUND_EFFECT_PLAYER
#define CLASS_SOUND_EFFECT_PLAYER
#include <string>
#include <map>
#include "SoundEffect.h"

class SoundEffectPlayer {
private:
    std::map<int,SoundEffect> sounds;
public:
    SoundEffectPlayer();
    SoundEffectPlayer(const SoundEffectPlayer& copy) = delete;
    SoundEffectPlayer& operator=(const SoundEffectPlayer& copy) = delete;
    //Añade un efecto de sonido
    void add(const int id,std::string sound);
    //Reproduce el efecto de sonido con clave id
    void play(const int id);
};

#endif