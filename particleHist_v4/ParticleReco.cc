#include "ParticleReco.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include <iostream>
#include <math.h>

using namespace std;


ParticleReco::ParticleReco() {
}


ParticleReco::~ParticleReco() {
}


// recompute tag informations for new event
void ParticleReco::update( const Event& ev ) {

  // set default quantities
  type   = unknown;
  energy = -1.0;
  mass   = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products
  ...

  // compare invariant masses with known values and set final values
  // ( type, energy and mass )
  ...

  return;

}


float ParticleReco::totalEnergy() {
  // check for new event and return result
  ...
}


float ParticleReco::invariantMass() {
  // check for new event and return result
  ...
}


ParticleReco::ParticleType ParticleReco::particleType() {
  // check for new event and return result
  ...
}

