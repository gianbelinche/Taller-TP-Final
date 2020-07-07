#ifndef PRIEST_H
#define PRIEST_H

#include "NPC.h"

class MasterFactory;
class Priest : public NPC {
 private:
 public:
  Priest(int id, int x, int y, ServerEventListener& eventListener,
           MasterFactory& factory);

  ~Priest();

  void heal(PlayerNet* player) override;

  void resurrect(PlayerNet* player) override;
};

#endif // PRIEST_H
