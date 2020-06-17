#include "Banker.h"
#include "SpriteClipCreator.h"

Banker::Banker(SDL_Renderer *renderer, int anID, int posX, int posY, 
               View aView) : Entity(renderer, anID, posX, posY, aView) {
    image.loadFromFile(BANKER_PATH);
    height = BANKER_HEIGHT;
    width = BANKER_WIDTH;
    horClips = BANKER_HOR_SPRITES;
    vertClips = BANKER_VERT_SPRITES;
    quad = {0, 0, height, width};
    SpriteClipCreator(height * vertClips, width * horClips, height, width, clips);
}

Banker::~Banker() {
}
