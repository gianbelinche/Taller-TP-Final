#include <string>

#include "common_SocketExcept.h"

SocketException::SocketException(const std::string& message) : msg_(message) {}
