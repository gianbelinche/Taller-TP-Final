#ifndef __CLIENT_PROTOCOL_H__
#define __CLIENT_PROTOCOL_H__

#include "MainMap.h"
#include "json/json.h"
#include <fstream>
#include <map>

/* RUTA AL ARCHIVO MAP.JSON */
#define MAP_JSON_PATH "map.json"

class ClientProtocol {
    private:
        
    public:
        ClientProtocol();
        ~ClientProtocol();

        //vector<uint32_t> makeMsg(); //cambiar
        MainMap createMainMap(SDL_Renderer *renderer);
};

#endif
