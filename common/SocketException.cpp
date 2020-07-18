#include <string>

#include "headers/SocketException.h"

SocketException::SocketException(const std::string& message) : msg_(message) {}
