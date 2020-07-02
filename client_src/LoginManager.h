#ifndef CLASS_LOGIN_MANAGER
#define CLASS_LOGIN_MANAGER

#include "LoginScreen.h"
#include "SDL2/SDL.h"
#include "Camera.h"
#include <vector>
#include <string>

class LoginManager{
private:
    LoginScreen& login;
    int screen_w;
    int screen_h;    
    SDL_Renderer *mainRenderer;
    Camera camera;
public:
    LoginManager(LoginScreen& login,SDL_Renderer *mainRenderer);
    std::vector<std::string> run();
};

#endif
