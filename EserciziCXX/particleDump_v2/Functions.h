#ifndef Functions_h
#define Functions_h

#include <fstream>
struct Event;

// read the Event characteristics from a file
const Event *read(std::ifstream &file);

// dump Event characteristics to the screen
void dump(const Event *event);

// delete the composite objects
void clear(const Event *event);

#endif
