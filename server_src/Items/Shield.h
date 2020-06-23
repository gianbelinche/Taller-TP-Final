#ifndef SHIELD_H
#define SHIELD_H

#include "Wearable.h"

class Shield : public Wearable {
private:
  
public:
  Shield(int id, int minDef, int maxDef);

  ~Shield();
};

#endif // SHIELD_H
