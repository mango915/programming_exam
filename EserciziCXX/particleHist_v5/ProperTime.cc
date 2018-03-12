#include "Constants.h"
//#include "Event.h"
#include "ParticleReco.h"
#include "ProperTime.h"
#include "Utilities.h"
#include <iostream>
#include <math.h>

static ProperTime *intime = ProperTime::instance();
static ParticleReco *reco = ParticleReco::instance();
static Constants *constants = Constants::instance();

using namespace std;

double distance3(double x, double y, double z) {
  return sqrt(x * x + y * y + z * z);
}
ProperTime::ProperTime() {}

ProperTime::~ProperTime() {}

// recompute tag informations for new event
void ProperTime::update(const Event &event) {

  // set default quantities
  time = -1.0;

  double d = distance3(event.x(), event.y(), event.z());
  double inv_mass = reco->invariantMass();
  double tot_energy = reco->totalEnergy();
  if (inv_mass == -1 || tot_energy == -1) {
    return;
  }
  double momentum = sqrt(pow(tot_energy, 2) - pow(inv_mass, 2));
  double time_temp = d * inv_mass / (momentum * constants->get_lightVelocity());
  time = time_temp;
  return;
}

ProperTime *ProperTime::instance() {
  static ProperTime *data = new ProperTime;
  return data;
}

double ProperTime::decayTime() {
  intime->check();
  return time;
}
