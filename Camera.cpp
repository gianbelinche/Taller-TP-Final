#include "Camera.h"

Camera::Camera(Player &aPlayer) : player(aPlayer) {
    this->x = (player.getPosX() + player.getWidth() / 2) - SCREEN_WIDTH / 2;
    this->y = (player.getPosY() + player.getHeight() / 2) - SCREEN_HEIGHT / 2;
    this->height = SCREEN_HEIGHT;
    this->width = SCREEN_WIDTH;

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

void Camera::refresh() {
    this->x = (player.getPosX() + player.getWidth() / 2) - SCREEN_WIDTH / 2;
    this->y = (player.getPosY() + player.getHeight() / 2) - SCREEN_HEIGHT / 2;
    this->height = SCREEN_HEIGHT;
    this->width = SCREEN_WIDTH;

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

int Camera::getX() {
    return this->x;
}

int Camera::getY() {
    return this->y;
}

int Camera::getHeight() {
    return this->height;
}

int Camera::getWidth() {
    return this->width;
}
