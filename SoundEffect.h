#ifndef CLASS_SOUND_EFFECT
#define CLASS_SOUND_EFFECT
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class SoundEffect {
private:
    Mix_Chunk* gSoundEffect;
public:
    SoundEffect(std::string path);
    ~SoundEffect();
    SoundEffect(const SoundEffect& copy) = delete;
    SoundEffect& operator=(const SoundEffect& copy) = delete;
    SoundEffect(SoundEffect&& other);
    SoundEffect& operator=(SoundEffect&& other);

    void play(); 
};

#endif