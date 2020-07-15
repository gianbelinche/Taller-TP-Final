#include "../headers/MusicPlayer.h"
#include "../headers/paths.h"

enum SONGS{
    CITY,
    DESERT,
    FOREST,
    CAVE
};

MusicPlayer::MusicPlayer() : songs(){
    this->add(CAVE,CAVE_MUSIC_PATH);
    this->add(CITY,CITY_MUSIC_PATH);
    this->add(FOREST,FOREST_MUSIC_PATH);
    this->add(DESERT,DESERT_MUSIC_PATH);
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