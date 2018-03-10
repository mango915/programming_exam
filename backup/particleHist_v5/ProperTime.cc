#include "Constants.h"
//#include "Event.h"
#include "ParticleReco.h"
#include "ProperTime.h"
#include "Utilities.h"
#include <iostream>
#include <math.h>
Constants constants2 = Constants::instance();
using namespace std;
double distance3(double x, double y, double z) {
  return sqrt(x * x + y * y + z * z);
}
ProperTime::ProperTime() {}

ProperTime::~ProperTime() {}

// recompute tag informations for new event
void ProperTime::update(const Event &event) {
  // set default quantities
  // type = unknown;
  // energy = -1.0;
  // mass = -1.0;
  time = -1.0;
  double d = distance3(event.x(), event.y(), event.z());
  static ParticleReco *data = ParticleReco::instance();
  double inv_mass = data->invariantMass();
  double tot_energy = data->totalEnergy();
  double momentum = sqrt(pow(tot_energy, 2) - pow(inv_mass, 2));
  double time_temp = d * inv_mass / (momentum * constants2.get_lightVelocity());
  time = time_temp;
  return;
}

ProperTime *ProperTime::instance() {
  static ProperTime *data = new ProperTime;
  return data;
}

double ProperTime::decayTime() {
  if (time != -1) {
    return time;
  } else {
    return 0;
  }
}
