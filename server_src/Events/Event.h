#ifndef EVENT_H
#define EVENT_H

class Event
{
private:
  int originUserId;
public:
  Event(int id);
  virtual ~Event();
};

#endif // EVENT_H
