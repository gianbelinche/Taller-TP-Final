

#include "Condition.h"

class IsAlive : public Condition {
 private:
 public:
  IsAlive();

  ~IsAlive();

  bool evaluate(PlayerNet* player) override;
};
