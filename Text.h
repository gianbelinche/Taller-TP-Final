#ifndef CLASS_TEXT
#define CLASS_TEXT
#include "Texture.h"

class Text : public Texture{
public:
    Text(SDL_Renderer *aRenderer);
    Text(SDL_Renderer *aRenderer, Uint8 aKeyRed, Uint8 aKeyGreen,
            Uint8 aKeyBlue, std::string text,int size);
    Text(Text&& other);
    Text& operator=(Text&& other);        
    void loadText(std::string text,int size);    
};

#endif
