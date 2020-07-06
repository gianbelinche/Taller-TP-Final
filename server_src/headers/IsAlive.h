#ifndef ISALIVE_H
#define ISALIVE_H

#include "Condition.h"

class IsAlive : public Condition {
 private:
 public:
  IsAlive();

  ~IsAlive();

  bool evaluate(PlayerNet* player) override;
};

#endif // ISALIVE_H
