... include header files ...

// compute energy from momentum x,y,z components and invariant mass
float ...( ... ) {
  ...
} 

// compute invariant mass from momentum x,y,z components and energy
float ...( ... ) {
  ...
} 

const float massPion    = 0.1395706;   // GeV/c^2
const float massProton  = 0.938272;    // GeV/c^2
const float massK0      = 0.497611;    // GeV/c^2
const float massLambda0 = 1.115683;    // GeV/c^2

float mass( ... ) {

  // retrieve particles in the event
  typedef const Particle* part_ptr;
  const part_ptr* particles = ...

  // variables to loop over particles
  ...

  // positive / negative track counters
  ...

  // variables for momentum sums
  ...
  // variables for energy sums, for K0 and Lambda0
  ...

  // loop over particles - momenta
  ... ( ... ) {
    // get particle pointer
    ...
    // update momentum sums
    ...
    // update energy sums, for K0 and Lambda0:
    // pion mass for negative particle,
    // pion or proton mass for positive particle,
    // for K0 or Lambda0 respectively
    ...
    // update positive/negative track counters
    ...
  }
  // check for exactly one positive and one negative track
  // otherwise return negative (unphysical) invariant mass
  ...

  // invariant masses for different decay product mass hypotheses
  ...

  // compare invariant masses with known values and return the nearest one
  ...

}

