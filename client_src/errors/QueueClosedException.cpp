#include "../headers/QueueClosedException.h"

QueueClosedException::QueueClosedException() noexcept {}

QueueClosedException::~QueueClosedException() noexcept {}

const char* QueueClosedException::what() const noexcept {
    return "Cola cerrada";
}
