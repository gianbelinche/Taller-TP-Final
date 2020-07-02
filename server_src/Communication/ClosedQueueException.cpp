#include <string>

#include "ClosedQueueException.h"

ClosedQueueException::ClosedQueueException(const std::string& message) : 
                                msg_(message) {}
