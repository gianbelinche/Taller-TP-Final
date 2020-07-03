#include <string>

#include "../headers/ClosedQueueException.h"

ClosedQueueException::ClosedQueueException(const std::string& message) : 
                                msg_(message) {}
