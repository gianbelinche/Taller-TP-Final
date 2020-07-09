#include "../headers/GhostState.h"

GhostState PlayerState::dead{};

void GhostState::update(PlayerNet &player) {}  // Nada

bool GhostState::isAlive(){
    return false;
}

GhostState::GhostState() {}

GhostState::~GhostState() {}
