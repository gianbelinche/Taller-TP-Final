#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera;

#include "Player.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define LEVEL_WIDTH 9056
#define LEVEL_HEIGHT 7392

class Camera {
    private:
        Player &player;
        int x;
        int y;
        int height;
        int width;

    public:
        Camera(Player &aPlayer);
        ~Camera();

        void refresh();

        int getX();
        int getY();
        int getHeight();
        int getWidth();
};

#endif
