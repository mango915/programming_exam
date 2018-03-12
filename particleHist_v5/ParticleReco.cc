#include "Constants.h"
//#include "Event.h"
#include "ParticleReco.h"
#include "Utilities.h"
#include <iostream>
#include <math.h>

static ParticleReco *reco = ParticleReco::instance();
static Constants *constants = Constants::instance();

using namespace std;

ParticleReco::ParticleReco() {}

ParticleReco::~ParticleReco() {}

// recompute tag informations for new event
void ParticleReco::update(const Event &event) {

  // set default quantities
  type = unknown;
  energy = -1.0;
  mass = -1.0;

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products
  int no_positive = 0, no_negative = 0;
  double mom_x_sum = 0, mom_y_sum = 0, mom_z_sum = 0;
  double energy_sum_K0 = 0, energy_sum_Lambda0 = 0;
  double inv_mass_K0 = 0, inv_mass_Lambda0 = 0;

  // computational economy
  if (event.nParticles() != 2) {
    return;
  }
  for (int i = 0; i < event.nParticles(); i++) {
    if (event.particle(i)->charge == +1) {
      ++no_positive;
    } else if (event.particle(i)->charge == -1) {
      ++no_negative;
    } else {
      return;
    }
    mom_x_sum += event.particle(i)->mom_x;
    mom_y_sum += event.particle(i)->mom_y;
    mom_z_sum += event.particle(i)->mom_z;
    energy_sum_K0 +=
        Utilities::energy(event.particle(i)->mom_x, event.particle(i)->mom_y,
                          event.particle(i)->mom_z, constants->get_massPion());
    if (event.particle(i)->charge == -1) {
      energy_sum_Lambda0 += Utilities::energy(
          event.particle(i)->mom_x, event.particle(i)->mom_y,
          event.particle(i)->mom_z, constants->get_massPion());
    } else if (event.particle(i)->charge == +1) {
      energy_sum_Lambda0 += Utilities::energy(
          event.particle(i)->mom_x, event.particle(i)->mom_y,
          event.particle(i)->mom_z, constants->get_massProton());
    } else {
      return;
    }
  }

  // check charges
  if ((no_positive != 1) || (no_negative != 1)) {
    return;
  }
  inv_mass_K0 =
      Utilities::inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_K0);
  inv_mass_Lambda0 =
      Utilities::inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_Lambda0);

  // return the more likehood invariant mass
  if (fabs(inv_mass_K0 - constants->get_massK0()) <
      fabs(inv_mass_Lambda0 - constants->get_massLambda0())) {
    mass = inv_mass_K0;
    energy = energy_sum_K0;
    type = K0;
  } else if (fabs(inv_mass_K0 - constants->get_massK0()) >
             fabs(inv_mass_Lambda0 - constants->get_massLambda0())) {
    mass = inv_mass_Lambda0;
    energy = energy_sum_Lambda0;
    type = Lambda0;
  }
  return;
}

double ParticleReco::totalEnergy() {
  // check for new event and return result
  reco->check();
  return energy;
}

double ParticleReco::invariantMass() {
  // check for new event and return result
  reco->check();
  return mass;
}

ParticleReco *ParticleReco::instance() {
  static ParticleReco *data = new ParticleReco;
  return data;
}

ParticleReco::ParticleType ParticleReco::particleType() {
  // check for new event and return result
  reco->check();
  return type;
}
