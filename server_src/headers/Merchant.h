#ifndef MERCHANT_H
#define MERCHANT_H

#include "NPC.h"

class MasterFactory;

class Merchant : public NPC {
 private:
 public:
  Merchant(int id, int x, int y, ServerEventListener& eventListener,
           MasterFactory& factory);

  ~Merchant();
};

#endif // MERCHANT_H
