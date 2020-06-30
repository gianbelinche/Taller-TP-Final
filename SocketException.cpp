#include <string>

#include "SocketException.h"

SocketException::SocketException(const std::string& message) : msg_(message) {}
