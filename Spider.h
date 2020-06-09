#ifndef SPIDER_H
#define SPIDER_H

#include "Entity.h"

class Spider : public Entity {
private:
  int frame;
public:
  Spider();

  ~Spider();

  void update() override;
};
#endif // SPIDER_H
