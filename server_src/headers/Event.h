#ifndef EVENT_H
#define EVENT_H

class Event {
 protected:
  int originUserId;

 public:
  Event(int id);

  virtual ~Event();

  int getUser();
};

#endif  // EVENT_H
