#ifndef Functions_h
#define Functions_h

#include <fstream>

class Event;

// return the most likehood invariant mass of the original decaying particle
double mass(const Event *event);

#endif
