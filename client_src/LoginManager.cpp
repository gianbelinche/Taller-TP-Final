#include "LoginManager.h"
#include <vector>
#include <string>
#include "QuitException.h"

LoginManager::LoginManager(LoginScreen& login,SDL_Renderer *mainRenderer) : 
login(login), mainRenderer(mainRenderer), camera(0,0,0,0) {}

std::vector<std::string> LoginManager::run(){
    SDL_StartTextInput();
    bool quit = false;
    SDL_Event event;
    std::vector<std::string> server;
    while (!quit){
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type){
                case SDL_QUIT:
                    throw QuitException("Salida del programa\n");
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN){
                        server = login.send(); 
                        quit = true;
                    }
                    if (event.key.keysym.sym == SDLK_BACKSPACE){
                        login.deleteCharacter();
                    }
                    break;

                case SDL_TEXTINPUT:
                    login.write(event.text.text);    
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    login.select(event.button.x,event.button.y,camera);
                    break;          
            }
        }
        SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(mainRenderer);
        login.render(camera);
        SDL_RenderPresent(mainRenderer);
    }
    SDL_StopTextInput();
    return std::move(server);
}