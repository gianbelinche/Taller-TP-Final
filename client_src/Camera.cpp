#include "Camera.h"

Camera::Camera(uint16_t posX, uint16_t posY, uint16_t aPlayerHeight,
        uint16_t aPlayerWidth,uint16_t height,uint16_t width) : 
                                playerHeight(aPlayerHeight), 
                                playerWidth(aPlayerWidth),
                                height(height),
                                width(width) {
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

Camera::Camera(Camera&& other) : x(other.x), y(other.y), 
                                 height(other.height),
                                 width(other.width), 
                                 playerHeight(other.playerHeight),
                                 playerWidth(other.playerWidth) {}

Camera& Camera::operator=(Camera&& other) {
    if (this == &other) {
        return *this;
    }

    this->x = other.x;
    this->y = other.y;
    this->height = other.height;
    this->width = other.width; 
    this->playerHeight = other.playerHeight;
    this->playerWidth = other.playerWidth;
    
    return *this;
}

Camera::~Camera() {}

void Camera::refresh(uint16_t posX, uint16_t posY) {
    if ((posX + playerWidth / 2) < width / 2) {
        this->x = 0;
    } else {
        this->x = (posX + playerWidth / 2) - width / 3;
    }

    if (this->x > LEVEL_WIDTH - this->width) {
        this->x = LEVEL_WIDTH - this->width;
    }

    if ((posY + playerHeight / 2) < height / 2) {
        this->y = 0;
    } else {
        this->y = (posY + playerHeight / 2) - height / 2;
    }
    
    if (this->y > LEVEL_HEIGHT - this->height) {
        this->y = LEVEL_HEIGHT - this->height;
    }
}

uint16_t Camera::getX() const{
    return this->x;
}

uint16_t Camera::getY() const{
    return this->y;
}

uint16_t Camera::getHeight() const{
    return this->height;
}

uint16_t Camera::getWidth() const{
    return this->width;
}
