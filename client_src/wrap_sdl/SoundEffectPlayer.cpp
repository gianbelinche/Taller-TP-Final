#include "../headers/SoundEffectPlayer.h"
#include "../headers/paths.h"

enum sounds{
    FIST,
    SWORD,
    AXE,
    HAMMER,
    FRESNO_BAR,
    ELFIC_FLUTE,
    BACULO_NUDOSO,
    BACULO_ENGARZADO,
    SIMPLE_BOW,
    COMPOSED_BOW,
    POTION
};

SoundEffectPlayer::SoundEffectPlayer() : sounds() {
    this->add(SWORD,SWORD_SOUND_EFFECT_PATH);
    this->add(HAMMER,HAMMER_SOUND_EFFECT_PATH);
    this->add(POTION,POTION_SOUND_EFFECT_PATH);
    this->add(AXE,AXE_SOUND_EFFECT_PATH);
    this->add(FRESNO_BAR,FRESNO_BAR_SOUND_EFFECT_PATH);
    this->add(ELFIC_FLUTE,ELFIC_FLUTE_SOUND_EFFECT_PATH);
    this->add(BACULO_NUDOSO,BACULO_NUDOSO_SOUND_EFFECT_PATH);
    this->add(BACULO_ENGARZADO,BACULO_ENGARZADO_SOUND_EFFECT_PATH);
    this->add(SIMPLE_BOW,SIMPLE_BOW_SOUND_EFFECT_PATH);
    this->add(COMPOSED_BOW,COMPOSED_BOW_SOUND_EFFECT_PATH);
    this->add(FIST,FIST_SOUND_EFFECT_PATH);
}

void SoundEffectPlayer::add(const int id,std::string sound){
    SoundEffect sound_effect(sound);
    sounds.insert(std::pair<int,SoundEffect>(id,std::move(sound_effect)));
}

void SoundEffectPlayer::play(const int id){
    sounds.at(id).play();
}
