#include <iostream>

#include "Spider.h"

Spider::Spider() : frame(0) {
}

Spider::~Spider() {
}

void Spider::update(){
  // Probablemente convenga delegar la logica del update en el "estado" de la
  // entidad
  frame += 1;
  if (frame == 100) {
    std::cout << "Se movio la arañita" << std::endl;
    frame = 0;
  }
}