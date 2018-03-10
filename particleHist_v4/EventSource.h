#ifndef EventSource_h
#define EventSource_h

class Event;

class EventSource { // abstract class

public:
  EventSource();
  virtual ~EventSource();
  virtual void run();

private:
  // get an event
  virtual const Event *get() = 0; // pure virtual function
  // dummy copy constructor and assignment to prevent unadvertent copy
  EventSource(const EventSource &x);
  EventSource &operator=(const EventSource &x);
};

#endif
