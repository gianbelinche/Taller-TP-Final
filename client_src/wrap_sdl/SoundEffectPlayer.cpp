#include "../headers/SoundEffectPlayer.h"

enum sounds{
    POTION,
    SWORD,
    AXE,
    HAMMER,
    FRESNO_BAR,
    ELFIC_FLUTE,
    BACULO_NUDOSO,
    BACULO_ENGARZADO,
    SIMPLE_BOW,
    COMPOSED_BOW
};

SoundEffectPlayer::SoundEffectPlayer() : sounds() {
    this->add(SWORD,"sound_effects/sword.wav");
    this->add(HAMMER,"sound_effects/hammer.wav");
    this->add(POTION,"sound_effects/potion.wav");
    this->add(AXE,"sound_effects/axe.wav");
    this->add(FRESNO_BAR,"sound_effects/fresno bar.wav");
    this->add(ELFIC_FLUTE,"sound_effects/flauta elfica.wav");
    this->add(BACULO_NUDOSO,"sound_effects/baculo nudoso.wav");
    this->add(BACULO_ENGARZADO,"sound_effects/baculo engarzado.wav");
    this->add(SIMPLE_BOW,"sound_effects/simple bow.wav");
    this->add(COMPOSED_BOW,"sound_effects/composed bow.wav");
}

void SoundEffectPlayer::add(const int id,std::string sound){
    SoundEffect sound_effect(sound);
    sounds.insert(std::pair<int,SoundEffect>(id,std::move(sound_effect)));
}

void SoundEffectPlayer::play(const int id){
    sounds.at(id).play();
}
