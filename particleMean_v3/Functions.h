#ifndef Functions_h
#define Functions_h

#include <fstream>

class Event;

// return the most likehood invariant mass of the original decaying particle
double mass(const Event *event);

// read the Event characteristics from a file
const Event *read(std::ifstream &file);

// dump Event characteristics to the screen
void dump(const Event *event);

#endif
