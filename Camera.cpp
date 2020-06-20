#include "Camera.h"

Camera::Camera(uint16_t posX, uint16_t posY) {
    this->height = SCREEN_HEIGHT;
    this->width = SCREEN_WIDTH;
    this->x = (posX + playerWidth / 2) - width / 2;
    this->y = (posY + playerHeight / 2) - height / 2;

    if (this->x < 0) {
        this->x = 0;
    }
    if (this->y < 0) {
        this->y = 0;
    }
    if (this->x > LEVEL_WIDTH - this->width) {
        this->x = LEVEL_WIDTH - this->width;
    }
    if (this->y > LEVEL_HEIGHT - this->height) {
        this->y = LEVEL_HEIGHT - this->height;
    }
}

Camera::~Camera() {}

void Camera::refresh(uint16_t posX, uint16_t posY) {
    if ((posX + playerWidth / 2) < width / 2) this->x = 0;
    else this->x = (posX + playerWidth / 2) - width / 2;

    if (this->x > LEVEL_WIDTH - this->width) {
        this->x = LEVEL_WIDTH - this->width;
    }

    if ((posY + playerHeight / 2) < height / 2) this->y = 0;
    else this->y = (posY + playerHeight / 2) - height / 2;
    
    if (this->y > LEVEL_HEIGHT - this->height) {
        this->y = LEVEL_HEIGHT - this->height;
    }
}

uint16_t Camera::getX() {
    return this->x;
}

uint16_t Camera::getY() {
    return this->y;
}

uint16_t Camera::getHeight() {
    return this->height;
}

uint16_t Camera::getWidth() {
    return this->width;
}
