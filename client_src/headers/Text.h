#ifndef CLASS_TEXT
#define CLASS_TEXT

#include "Texture.h"
#include "SDLError.h"

class Text : public Texture{
    private:
        Uint8 red;
        Uint8 green;
        Uint8 blue;

    public:
        Text(SDL_Renderer *aRenderer, Uint8 aKeyRed = 0, Uint8 aKeyGreen = 0,
                Uint8 aKeyBlue = 0);

        Text(Text&& other);
        Text& operator=(Text&& other);       

        Text(const Text& copy) = delete;
        Text& operator=(Text& copy) = delete;  

        void loadText(std::string text, TTF_Font *gFont);    
};

#endif
