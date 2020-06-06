#ifndef CLASS_IMAGE
#define CLASS_IMAGE
#include "Texture.h"

class Image : public Texture {
public:    
    Image(SDL_Renderer *aRenderer);
    Image(SDL_Renderer *aRenderer, Uint8 aKeyRed, Uint8 aKeyGreen,
            Uint8 aKeyBlue, std::string path);

    Image(Image&& other);
    Image& operator=(Image&& other);        

    void loadFromFile(std::string path);        
};

#endif
