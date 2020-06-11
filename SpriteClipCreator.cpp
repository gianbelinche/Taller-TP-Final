#include "SpriteClipCreator.h"

SpriteClipCreator::SpriteClipCreator(int imgHeight, int imgWidth, int tileHeight, int tileWidth) {
    int files = imgHeight / tileHeight;
    int columns = imgWidth / tileWidth;

    for (int i = 0; i < files; i++) {
        for (int j = 0; j < columns; j++) {
            //CREAR MATRIZ DEL RECTANGULO
        }
    }
}

SpriteClipCreator::~SpriteClipCreator() {
}

