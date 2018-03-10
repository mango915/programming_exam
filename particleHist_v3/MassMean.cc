#include "Event.h"
#include "Functions.h"
#include "MassMean.h"
#include <math.h>

using namespace std;

MassMean::MassMean(float min, float max)
    : min_mass(min), max_mass(max), no_accepted_events(0), sum_of_masses(0),
      sum_of_squares(0), mean(0), rms(0) {}

MassMean::~MassMean() {}

// add data from a new event
bool MassMean::add(const Event &ev) {
  double temp_mass = mass(&ev);
  // check for mass being in range
  if ((temp_mass <= max_mass) && (temp_mass >= min_mass)) {
    // update number of events and sums
    no_accepted_events++;
    sum_of_masses += temp_mass;
    sum_of_squares += (temp_mass * temp_mass);
    return true;
  } else {
    return false;
  }
}

// compute mean and rms
void MassMean::compute() {
  mean = sum_of_masses / no_accepted_events;
  rms = sqrt((sum_of_squares / no_accepted_events) - pow(mean, 2));
  return;
}

int MassMean::nEvents() const { return no_accepted_events; }
double MassMean::mMean() const { return mean; }
double MassMean::mRMS() const { return rms; }
