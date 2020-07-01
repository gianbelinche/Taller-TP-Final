#ifndef CLASS_MUSIC_PLAYER
#define CLASS_MUSIC_PLAYER
#include <string>
#include <map>
#include "Music.h"

class MusicPlayer {
private:
    std::map<int,Music> songs;
public:
    MusicPlayer() : songs() {}
    void add(const int id,std::string song);
    void play(const int id);
    void stop();    

};

#endif