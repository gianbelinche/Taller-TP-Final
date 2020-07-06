#include "NPC.h"

class Merchant : public NPC {
 private:
 public:
  Merchant(int id, int x, int y, ServerEventListener& eventListener,
           MasterFactory& factory);

  ~Merchant();
};
