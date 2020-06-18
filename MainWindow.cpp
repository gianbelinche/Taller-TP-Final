#include "MainWindow.h"
#include "SDLError.h"

#include "json/json.h"
#include <fstream>
#include <map>

#include "MainMap.h"
#include "EntityManager.h"
#include "Camera.h"

/* RUTA AL ARCHIVO MAP.JSON */
#define MAP_JSON_PATH "map.json"

/* TAMAÑO DEL NIVEL */
//#define LEVEL_WIDTH 1280
//#define LEVEL_HEIGHT 960

/* NOMBRE DE LA PANTALLA */
#define WINDOW_NAME "Main"

/* FRECUENCIA DE SONIDO */
#define FRECUENCY 22050

MainWindow::MainWindow() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw SDLError("Error: SDL no pudo inicializarse. SDL_Error: %s", 
                       SDL_GetError());
    }

    if(TTF_Init() == -1){
        throw SDLError("No se pudo inicializar la Font. SDL_ttf Error: %s\n", 
                       TTF_GetError());
    }

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        // printf( "Warning: Linear texture filtering not enabled!" );
    }

    this->mainWindow = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, 
                                    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->mainWindow == NULL) {
        throw SDLError("Error: no se pudo crear ventana. SDL_Error: %s",
                        SDL_GetError());
    }

    this->mainRenderer = SDL_CreateRenderer(this->mainWindow, -1, 
                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (this->mainRenderer == NULL) {
        throw SDLError("Error: no se pudo crear render. SDL_Error: %s",
                        SDL_GetError());
    }

    SDL_SetRenderDrawColor(this->mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //CAMBIAR!!

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        throw SDLError("Error: SDL_image no pudo inicializarse. SDL_Error: %s",
                        SDL_GetError());
    }

    if(Mix_OpenAudio(FRECUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ){ //No me acuerdo que son los otros dos numeros, despues me fijo y pongo defines
		throw SDLError("No se pudo inicializar el sonido: %S\n", Mix_GetError());
	}
}

MainWindow::~MainWindow() {
    IMG_Quit();
    Mix_Quit();
  	TTF_Quit();
    SDL_Quit();
}

MainMap prueba(SDL_Renderer *mainRenderer) {
    /* LECTURA DEL MAPA.JSON */

    std::ifstream mapFile(MAP_JSON_PATH);
    Json::Reader mapReader;
    Json::Value mapValues;
    mapReader.parse(mapFile, mapValues);

    /*
     * Busco el array de capas. El mapa se separa en "capas" que permiten
     * la superposición de elementos. Nuestro mapa se divide en dos capas
     * para poder poner edificaciones, arboles, etc.
    */
    const Json::Value& layers = mapValues["layers"]; // Array de capas

    /*
     * Si algo que se buscó en el .json no se encontró se setea el
     * const Json::Value&
     * en null.
    */
    if (!layers) {
        /* Buscar cómo obtener el error que genera jsoncpp */
        //throw JsonError("Error: no se encontró layers. JsonError: %s", jsonerror);
    }

    /*
     * Ancho, alto y la data de cada capa.
    */
    const Json::Value& layer0 = layers[0]["data"];     // Array de enteros de capa 0
    const Json::Value& width0 = layers[0]["width"];    // Ancho de la capa 0
    const Json::Value& height0 = layers[0]["height"];  // Alto de la capa 0

    if (!(layer0 && height0 && width0)) {
        /* Buscar cómo obtener el error que genera jsoncpp */
        //throw JsonError("Error: no se encontró data de capa 0. JsonError: %s", jsonerror);
    }

    const Json::Value& layer1 = layers[1]["data"];     // Array de enteros de capa 1
    const Json::Value& width1 = layers[1]["width"];    // Ancho de la capa 1
    const Json::Value& height1 = layers[1]["height"];  // Alto de la capa 1

    if (!(layer1 && height1 && width1)) {
        /* Buscar cómo obtener el error que genera jsoncpp */
        //throw JsonError("Error: no se encontró data de capa 1. JsonError: %s", jsonerror);
    }

    const Json::Value& layer2 = layers[2]["data"];     // Array de enteros de capa 2
    const Json::Value& width2 = layers[2]["width"];    // Ancho de la capa 2
    const Json::Value& height2 = layers[2]["height"];  // Alto de la capa 2

    if (!(layer2 && height2 && width2)) {
        /* Buscar cómo obtener el error que genera jsoncpp */
        //throw JsonError("Error: no se encontró data de capa 1. JsonError: %s", jsonerror);
    }

    /*
     * Creo las matrices que tienen la data de las capas.
     * Estas matrices se deben guardar para enviar a los clientes
     * Además, se deben guardar los valores:
     * height0, width0, height1 y width1 (no es necesario creo)
    */

    std::vector<std::vector<uint32_t>> matrixLayer0;
    std::vector<std::vector<uint32_t>> matrixLayer1;
    std::vector<std::vector<uint32_t>> matrixLayer2;
    uint32_t cont = 0;

    /* Matriz de capa 0 */

    for (Json::Value::UInt i = 0; i < height0.asUInt(); i++) {
        std::vector<uint32_t> row;
        for (Json::Value::UInt j = 0; j < width0.asUInt(); j++) {
            row.emplace_back(layer0[cont].asUInt());
            cont++;
        }
        matrixLayer0.emplace_back(row);
    }

    /* Matriz de capa 1 */

    cont = 0;
    for (Json::Value::UInt i = 0; i < height1.asUInt(); i++) {
        std::vector<uint32_t> row;
        for (Json::Value::UInt j = 0; j < width1.asUInt(); j++) {
            row.emplace_back(layer1[cont].asUInt());
            cont++;
        }
        matrixLayer1.emplace_back(row);
    }

    /* Matriz de capa de bloqueo */

    cont = 0;
    for (Json::Value::UInt i = 0; i < height2.asUInt(); i++) {
        std::vector<uint32_t> row;
        for (Json::Value::UInt j = 0; j < width2.asUInt(); j++) {
            row.emplace_back(layer2[cont].asUInt());
            cont++;
        }
        matrixLayer2.emplace_back(row);
    }

    /* 
     * Creo el hash que contiene como: 
     *  -clave: al numero asignado al tileset.
     *  -valor: un vector de valores importantes en forma de strings.
    */

    const Json::Value& tilesets = mapValues["tilesets"];  // Array de tilesets

    /* Este hash se debe guardar para enviar a los clientes */
    std::map<uint32_t, std::vector<std::string>> tiles;
    
    for (Json::Value::ArrayIndex i = 0; i < tilesets.size(); i++) {
        std::ifstream ifsl(tilesets[i]["source"].asString());
        Json::Value vall;
        mapReader.parse(ifsl, vall);

        uint32_t key = tilesets[i]["firstgid"].asUInt();
        std::vector<std::string> v;

        v.emplace_back(vall["image"].asString());
        v.emplace_back(vall["tileheight"].asString());
        v.emplace_back(vall["tilewidth"].asString());
        
        tiles[key] = v;
    }

    MainMap mainMap(tiles, mainRenderer, matrixLayer0, matrixLayer1);
    return std::move(mainMap);
}

#include <iostream>

void MainWindow::run() {
    MainMap mainMap = std::move(prueba(mainRenderer));
    Player player(mainRenderer, ELF, 5664, 2496);
    EntityManager entMan(mainRenderer, player);
    Camera camera(player);

    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&eventHandler) != 0) {
            if (eventHandler.type == SDL_QUIT) {
                quit = true;
            }

            player.move(eventHandler); //temporal, es solo para probar el movimiento del pj
            entMan.addDrop(ESPADA, 1010, camera.getX(), camera.getY());
            entMan.addDrop(BACULO_ENGARZADO, 1010, camera.getX() + 250, camera.getY() + 250);
            entMan.addDrop(ARCO_COMPUESTO, 1010, camera.getX() + 150, camera.getY() + 150);
        }

       camera.refresh();

        //SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //creo que no hace falta
        SDL_RenderClear(mainRenderer);

        mainMap.renderTerrain(camera);
        entMan.renderEntities(camera);
        mainMap.renderStructures(camera);

        SDL_RenderPresent(mainRenderer);
    }
}
