#ifndef CLASS_SOUND_EFFECT_PLAYER
#define CLASS_SOUND_EFFECT_PLAYER
#include <string>
#include <map>
#include "SoundEffect.h"

class SoundEffectPlayer {
private:
    std::map<int,SoundEffect> sounds;
public:
    SoundEffectPlayer() : sounds() {}
    void add(const int id,std::string sound);
    void play(const int id);
};

#endif