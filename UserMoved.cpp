

#include "UserMoved.h"

UserMoved::UserMoved(int originUser, char direction) : 
            Event(originUser), direction(direction) {
}

UserMoved::~UserMoved() {
}