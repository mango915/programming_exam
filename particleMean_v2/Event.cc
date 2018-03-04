#include "Event.h"

Event::Event( int n, float x, float y, float z ):
 // initializations
 ... {
  // allocate a buffer for particle pointers
  ...
}


Event::~Event() {
  // delete all the particle pointers
  ...
  // delete the pointers array
  ...
}


void Event::add( float px, float py, float pz, int charge ) {

  // check for the number of particles, if maximum reached do nothing
  // and return
  ...

  // create the new particle and fill with data
  ...

  // store the new particle pointer in the array and increase counter
  ...

  return;

}


// get event id.
int Event::eventNumber() const {
  ...
}


// get decay point coordinates
...


// get number of particles
...


// get particle
const Event::Particle* Event::particle( unsigned int i ) const {
  ...
}

