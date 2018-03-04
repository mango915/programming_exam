#include "MassMean.h"
#include "Event.h"

#include <math.h>

float mass( const Event& ev );


MassMean::MassMean( float min, float max ):
 // initializations
 ... {
}


MassMean::~MassMean() {
}


// add data from a new event
void MassMean::add( const Event& ev ) {

  // check for mass being in range
  ...

  // update number of events and sums
  ...

}


// compute mean and rms
void MassMean::compute() {
  ...
}


// return number of selected events
...


// return mean and rms
...

