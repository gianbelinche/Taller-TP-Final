#include "MusicPlayer.h"

enum SONGS{
    CAVE,
    CITY,
    FOREST,
    DESERT
};

MusicPlayer::MusicPlayer() : songs(){
    this->add(CAVE,"music/cave.wav");
    this->add(CITY,"music/city.wav");
    this->add(FOREST,"music/forest.wav");
    this->add(DESERT,"music/desert.wav");
}

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