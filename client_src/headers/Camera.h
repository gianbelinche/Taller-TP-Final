#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera;

#include "stdint.h"
#include "paths.h"

#define LEVEL_WIDTH 9920
#define LEVEL_HEIGHT 7104

class Camera {
    private:
        uint16_t x;
        uint16_t y;
        uint16_t height;
        uint16_t width;
        uint16_t playerHeight;
        uint16_t playerWidth;

    public:
        Camera(uint16_t posX, uint16_t posY, uint16_t playerHeight,
        uint16_t playerWidth, uint16_t height, uint16_t width);
        ~Camera();

        Camera(const Camera &copy) = delete;
        Camera(Camera&& other);
        Camera& operator=(Camera&& other);

        void refresh(uint16_t posX, uint16_t posY);

        uint16_t getX() const;
        uint16_t getY() const;
        uint16_t getHeight() const;
        uint16_t getWidth() const;
};

#endif
