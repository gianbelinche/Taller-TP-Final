#ifndef ARMOR_H
#define ARMOR_H

#include "Wearable.h"

class Armor : public Wearable {
private:

public:
  Armor(int id, int minDef, int maxDef);

  ~Armor();
};

#endif // ARMOR_H
