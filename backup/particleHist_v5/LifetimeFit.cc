//#include "Constants.h"
//#include "Event.h"
#include "LifetimeFit.h"
#include "ParticleReco.h"
//#include <iostream>
#include <math.h>
using namespace std;
// double mass(const Event *ev);

LifetimeFit::LifetimeFit(float min, float max)
    : min_mass(min), max_mass(max), no_accepted_events(0) {}

LifetimeFit::~LifetimeFit() {}

// add data from a new event
bool LifetimeFit::add(const Event &ev) {
  static ParticleReco *data = ParticleReco::instance();
  // data->update(ev);
  double temp_mass = (data->invariantMass());
  // check for mass being in range
  if ((temp_mass <= max_mass) && (temp_mass >= min_mass)) {
    // update number of events
    no_accepted_events++;
    return true;
  } else {
    return false;
  }
}

// compute mean and rms
void LifetimeFit::compute() { return; }

int LifetimeFit::nEvents() const { return no_accepted_events; }
