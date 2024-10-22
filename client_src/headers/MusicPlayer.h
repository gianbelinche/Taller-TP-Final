#ifndef CLASS_MUSIC_PLAYER
#define CLASS_MUSIC_PLAYER

#include <string>
#include <map>
#include "Music.h"

class MusicPlayer {
private:
    std::map<int,Music> songs;
public:
    MusicPlayer();
    MusicPlayer(const MusicPlayer& copy) = delete;
    MusicPlayer& operator=(const MusicPlayer& copy) = delete;
    //Añade una cancion al reproductor
    void add(const int id,std::string song);
    //Comienza a reproducir la canción con clave id
    void play(const int id);
    //Deja de reproducir la canción actual
    void stop();    

};

#endif