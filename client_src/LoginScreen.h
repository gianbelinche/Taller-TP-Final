#ifndef CLASS_LOGIN_SCREEN
#define CLASS_LOGIN_SCREEN
#include "Image.h"
#include "Text.h"
#include <string>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Camera.h"

/*
    Representa la pantalla de login, en la que primero
    se debe ingresar un host y un puerto para conectarse al servidor,
    y luego se ingresa el usuario y la contraseña para loguearse.
*/

class LoginScreen{
private:
    SDL_Renderer* mainRenderer;
    Image background;
    Image text_input;
    Text  text1;
    Text  text2;
    Text  error;
    Text  title;
    TTF_Font* gFont;
    int text1_l;
    int text2_l;
    int title_l;
    std::string input1;
    std::string input2;
    int actual;
    bool active;
    void renderWord(std::string to_render_word,int x, int y,int w,int h,int screen_w,int screen_h);
public:
    LoginScreen(SDL_Renderer* mainRenderer);
    void render(Camera& camera);
    //Cambia de modo ingresar servidor a modo ingresar usuario y contraseña
    void changeToUserInput();
    //Muestra un error en pantalla
    void showError(std::string error);
    //Selecciona uno de los dos posibles cuadros de texto para escribir
    void select(int x,int y,Camera& camera);
    //Escribe el caracter c en el cuadro de texto seleccionado
    void write(std::string c); 
    //Elimina el ultimo caracter del cuadro de texto seleccionado
    void deleteCharacter();
    //Devuelve el contenido de ambos cuadros de textos y los vacia
    std::vector<std::string> send();  
    //Desactiva la pantalla de login
    void deactivate();
    //Informa si el login esta activado
    bool is_active();
};

#endif
