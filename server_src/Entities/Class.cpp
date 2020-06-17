#include "Class.h"

Class::Class(char class_type, int hpFac, int manaFac, int meditFac) :
             class_type(class_type), hpFactor(hpFac), manaFactor(manaFac),
             meditationFactor(meditFac) {

}

Class::~Class() {
    
}

int Class::getHpFactor() {
  return hpFactor;
}

int Class::getManaFactor() {
  return manaFactor;
}

int Class::getmeditationFactor() {
  return meditationFactor;
}
