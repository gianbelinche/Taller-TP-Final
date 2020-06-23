#ifndef CLASS_IMAGE
#define CLASS_IMAGE

#include "Texture.h"
#include "SDLError.h"

class Image : public Texture {
    public:    
        Image(SDL_Renderer *aRenderer);
        Image(SDL_Renderer *aRenderer, std::string path);

        Image(const Image &copy) = delete;

        Image(Image&& other);
        Image& operator=(Image&& other);

        void loadFromFile(std::string path);
};

#endif
