#ifndef CLASS_MUSIC
#define CLASS_MUSIC
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class Music {
private:
    Mix_Music* gMusic;
public:
    Music(std::string path);
    ~Music();
    Music(const Music& copy) = delete;
    Music& operator=(const Music& copy) = delete;
    Music(Music&& other);
    Music& operator=(Music&& other);

    void play(); 
};

#endif
