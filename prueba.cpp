#include "Socket.h"
#include <thread>
#include <vector>
#include <iostream>
#include <arpa/inet.h>
#include <msgpack.hpp>
#include "json/json.h"
#include <map>
#include <fstream>

void receive(Socket &l) {
    while (true) {
        //recibe largo
        std::vector<char> lenBuff(4);
        l.recv(&lenBuff[0], 4);
        uint32_t len = (lenBuff[3] << 24) + (lenBuff[2] << 16) +
                        (lenBuff[1] << 8) + lenBuff[0];

        len = ntohl(len);

        //recibe paquete
        std::vector<char> msgBuff(len);
        l.recv(&msgBuff[0], len);
        std::string ss(msgBuff.begin(), msgBuff.end());

        //desempaqueta
        std::vector<uint32_t> event;
        msgpack::object_handle oh = msgpack::unpack(ss.data(), ss.size());
        oh.get().convert(event);
        std::cout << "{";
        for (auto &m : event) {
            std::cout << m << ", ";
        }
        std::cout << "}" << '\n';
        
        //empaquetar
        std::cout << "Re-empaqueto" << '\n';
        std::stringstream buffer;
        msgpack::pack(buffer, event);
        std::string sbuffer = buffer.str();

        std::vector<char> msg(sbuffer.begin(), sbuffer.end());

        uint32_t len2 = msg.size();
        len2 = htonl(len2);

        char *lenBuff2 = (char*)&len2;
        std::vector<char> msgLen(4);

        for (int i = 0; i < 4; i++) {
            msgLen[i] = lenBuff2[i];
        }

        std::cout << "Envio largo: " << len2 << '\n';

        //enviar largo
        l.send(&msgLen[0], 4);

        std::cout << "Envio msg" << '\n';

        //enviar paquete
        l.send(&msg[0], msg.size());
    }
}

void pruebaprotocolo(int i, Socket &l) {
    std::vector<uint32_t> entidad;
    entidad.emplace_back(1);
    entidad.emplace_back(50+i);
    entidad.emplace_back(i);
    entidad.emplace_back(2500 + i*200);
    entidad.emplace_back(2500 + i*200);
    //empaquetar
    std::stringstream bufferEnt;
    msgpack::pack(bufferEnt, entidad);
    std::string sbufferEnt = bufferEnt.str();

    std::vector<char> msgEnt(sbufferEnt.begin(), sbufferEnt.end());

    uint32_t lenEnt = msgEnt.size();
    lenEnt = htonl(lenEnt);

    char *lenBuffEnt = (char*)&lenEnt;
    std::vector<char> msgLenEnt(4);

    for (int i = 0; i < 4; i++) {
        msgLenEnt[i] = lenBuffEnt[i];
    }

    //enviar largo
    l.send(&msgLenEnt[0], 4);
    //enviar paquete
    l.send(&msgEnt[0], msgEnt.size());
}

void enviarprueba(Socket &l) {
    /* CREACION JUGADOR */

    std::vector<uint32_t> jugadorProtocolo;
    jugadorProtocolo.emplace_back(2);
    jugadorProtocolo.emplace_back(1550);
    jugadorProtocolo.emplace_back(1);
    jugadorProtocolo.emplace_back(2500);
    jugadorProtocolo.emplace_back(2500);
    jugadorProtocolo.emplace_back(0);

    //empaquetar
    std::stringstream buffer3;
    msgpack::pack(buffer3, jugadorProtocolo);
    std::string sbuffer3 = buffer3.str();

    std::vector<char> msg3(sbuffer3.begin(), sbuffer3.end());

    uint32_t len3 = msg3.size();
    len3 = htonl(len3);

    char *lenBuff3 = (char*)&len3;
    std::vector<char> msgLen3(4);

    for (int i = 0; i < 4; i++) {
        msgLen3[i] = lenBuff3[i];
    }

    //enviar largo
    l.send(&msgLen3[0], 4);
    //enviar paquete
    l.send(&msg3[0], msg3.size());


    /* LECTURA DEL MAPA.JSON */


    std::ifstream mapFile("map.json");
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

    //tiles
    //empaquetar
    std::stringstream buffer;
    msgpack::pack(buffer, tiles);
    std::string sbuffer = buffer.str();

    std::vector<char> msg(sbuffer.begin(), sbuffer.end());

    uint32_t len = msg.size();
    len = htonl(len);

    char *lenBuff = (char*)&len;
    std::vector<char> msgLen(4);

    for (int i = 0; i < 4; i++) {
        msgLen[i] = lenBuff[i];
    }

    //enviar largo
    l.send(&msgLen[0], 4);
    //enviar paquete
    l.send(&msg[0], msg.size());

    //matriz0
    //empaquetar
    std::stringstream buffer1;
    msgpack::pack(buffer1, matrixLayer0);
    std::string sbuffer1 = buffer1.str();

    std::vector<char> msg1(sbuffer1.begin(), sbuffer1.end());

    uint32_t len1 = msg1.size();
    len1 = htonl(len1);

    char *lenBuff1 = (char*)&len1;
    std::vector<char> msgLen1(4);

    for (int i = 0; i < 4; i++) {
        msgLen1[i] = lenBuff1[i];
    }

    //enviar largo
    l.send(&msgLen1[0], 4);
    //enviar paquete
    l.send(&msg1[0], msg1.size());

    //matriz1
    //empaquetar
    std::stringstream buffer2;
    msgpack::pack(buffer2, matrixLayer1);
    std::string sbuffer2 = buffer2.str();

    std::vector<char> msg2(sbuffer2.begin(), sbuffer2.end());

    uint32_t len2 = msg2.size();
    len2 = htonl(len2);

    char *lenBuff2 = (char*)&len2;
    std::vector<char> msgLen2(4);

    for (int i = 0; i < 4; i++) {
        msgLen2[i] = lenBuff2[i];
    }

    //enviar largo
    l.send(&msgLen2[0], 4);
    //enviar paquete
    l.send(&msg2[0], msg2.size());

    //////////////////////////////////////////////////////////////////
    /////////////////////// ENVIO DE PROTOCOLO ///////////////////////
    //////////////////////////////////////////////////////////////////

    /*for (size_t i = 0; i < 5; i++) {
        pruebaprotocolo(i, l);
    }*/

    std::vector<uint32_t> entidad;
    entidad.emplace_back(1);
    entidad.emplace_back(50);
    entidad.emplace_back(1);
    entidad.emplace_back(2500 + 200);
    entidad.emplace_back(2500 + 200);
    //empaquetar
    std::stringstream bufferEnt;
    msgpack::pack(bufferEnt, entidad);
    std::string sbufferEnt = bufferEnt.str();

    std::vector<char> msgEnt(sbufferEnt.begin(), sbufferEnt.end());

    uint32_t lenEnt = msgEnt.size();
    lenEnt = htonl(lenEnt);

    char *lenBuffEnt = (char*)&lenEnt;
    std::vector<char> msgLenEnt(4);

    for (int i = 0; i < 4; i++) {
        msgLenEnt[i] = lenBuffEnt[i];
    }

    //enviar largo
    l.send(&msgLenEnt[0], 4);
    //enviar paquete
    l.send(&msgEnt[0], msgEnt.size());
}

int main(int argc, char const *argv[])
{
    Socket s;
    s.bind(argv[1]);
    s.listen();
    Socket l = s.accept();

    //std::thread recibir(receive, l);
    enviarprueba(l);
    receive(l);
    getc(stdin);

    //recibir.join();
    //enviar.join();

    return 0;
}
