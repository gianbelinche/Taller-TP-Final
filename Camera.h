#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera;

#include "stdint.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define LEVEL_WIDTH 9056
#define LEVEL_HEIGHT 7392

class Camera {
    private:
        uint16_t x;
        uint16_t y;
        uint16_t height;
        uint16_t width;
        uint16_t playerHeight;
        uint16_t playerWidth;

    public:
        Camera(uint16_t posX, uint16_t posY);
        ~Camera();

        void refresh(uint16_t posX, uint16_t posY);

        uint16_t getX();
        uint16_t getY();
        uint16_t getHeight();
        uint16_t getWidth();
};

#endif
