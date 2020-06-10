#ifndef __FILTERED_IMAGE_H__
#define __FILTERED_IMAGE_H__

#include "Texture.h"

/*
 * Clase Imagen Filtrada.
*/
class FilteredImage : public Texture {
    private:
        Uint8 keyRed;
        Uint8 keyGreen;
        Uint8 keyBlue;
    
    public:
        FilteredImage(SDL_Renderer *aRenderer, Uint8 keyRed, Uint8 keyGreen, 
                      Uint8 keyBlue);
        ~FilteredImage();

        FilteredImage(FilteredImage &copy) = delete;

        FilteredImage(FilteredImage&& other);
        FilteredImage& operator=(FilteredImage&& other);

        void loadFromFile(std::string path);
};

#endif
