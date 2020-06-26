#include "EmptyException.h"

EmptyException::EmptyException() noexcept {}

EmptyException::~EmptyException() noexcept {}

const char* EmptyException::what() const noexcept {
    return "Contenedor vacio";
}
