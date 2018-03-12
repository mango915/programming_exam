#ifndef ProperTime_h
#define ProperTime_h

#include "Event.h"

#include "LazyObserver.h"
#include "Singleton.h"

class ProperTime : public Singleton<ProperTime>, public LazyObserver<Event> {

  friend class Singleton<ProperTime>;

public:
  // recompute informations for new event
  virtual void update(const Event &event);

  static ProperTime *instance();
  double decayTime();

private:
  // private constructor and destructor for singleton
  ProperTime();
  ~ProperTime();

  // dummy copy constructor and assignment to prevent unadvertent copy
  ProperTime(const ProperTime &x);
  ProperTime &operator=(const ProperTime &x);

  // decay proper time
  float time;
};

#endif
