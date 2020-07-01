#include "MusicPlayer.h"

void MusicPlayer::add(const int id,std::string song){
    Music music(song);
    songs.insert(std::pair<int,Music>(id,std::move(music)));
}

void MusicPlayer::play(const int id){
    songs.at(id).play();
}

void MusicPlayer::stop(){
    Mix_HaltMusic();
}