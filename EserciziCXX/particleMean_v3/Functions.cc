#include "Constants.h"
#include "Event.h"
#include "Functions.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

// singleton for constants using
Constants *constants = Constants::instance();

// return the most likehood invariant mass of the original decaying particle
double mass(const Event *event) {

  int no_positive = 0, no_negative = 0;
  double mom_x_sum = 0, mom_y_sum = 0, mom_z_sum = 0;
  double energy_sum_K0 = 0, energy_sum_Lambda0 = 0;
  double inv_mass_K0 = 0, inv_mass_Lambda0 = 0;

  // computational economy
  if (event->nParticles() != 2) {
    return -1;
  }
  for (int i = 0; i < event->nParticles(); i++) {
    if (event->particle(i)->charge == +1) {
      ++no_positive;
    } else if (event->particle(i)->charge == -1) {
      ++no_negative;
    } else {
      return -1;
    }
    mom_x_sum += event->particle(i)->mom_x;
    mom_y_sum += event->particle(i)->mom_y;
    mom_z_sum += event->particle(i)->mom_z;
    energy_sum_K0 +=
        Utilities::energy(event->particle(i)->mom_x, event->particle(i)->mom_y,
                          event->particle(i)->mom_z, constants->get_massPion());
    if (event->particle(i)->charge == -1) {
      energy_sum_Lambda0 += Utilities::energy(
          event->particle(i)->mom_x, event->particle(i)->mom_y,
          event->particle(i)->mom_z, constants->get_massPion());
    } else if (event->particle(i)->charge == +1) {
      energy_sum_Lambda0 += Utilities::energy(
          event->particle(i)->mom_x, event->particle(i)->mom_y,
          event->particle(i)->mom_z, constants->get_massProton());
    } else {
      return -1;
    }
  }

  // check charges
  if ((no_positive != 1) || (no_negative != 1)) {
    return -1;
  }
  inv_mass_K0 =
      Utilities::inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_K0);
  inv_mass_Lambda0 =
      Utilities::inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_Lambda0);

  // return the more likehood invariant mass
  if (fabs(inv_mass_K0 - constants->get_massK0()) <
      fabs(inv_mass_Lambda0 - constants->get_massLambda0())) {
    return inv_mass_K0;
  } else if (fabs(inv_mass_K0 - constants->get_massK0()) >
             fabs(inv_mass_Lambda0 - constants->get_massLambda0())) {
    return inv_mass_Lambda0;
  } else {
    return -1;
  }
}

// read the Event characteristics from a file
const Event *read(ifstream &file) {
  int id_temp;
  float decay_x_temp, decay_y_temp, decay_z_temp;
  int no_particles;
  if (!(file >> id_temp)) {
    return 0;
  }

  file >> decay_x_temp >> decay_y_temp >> decay_z_temp >> no_particles;
  Event *event = new Event(id_temp, decay_x_temp, decay_y_temp, decay_z_temp);

  for (int i = 0; i < no_particles; i++) {
    int charge;
    float mom_x_temp, mom_y_temp, mom_z_temp;
    file >> charge >> mom_x_temp >> mom_y_temp >> mom_z_temp;
    event->add(mom_x_temp, mom_y_temp, mom_z_temp, charge);
  }

  return event;
}

// dump Event characteristics to the screen
void dump(const Event *event) {

  cout << event->eventNumber() << endl;
  cout << event->x() << " " << event->y() << " " << event->z() << endl;
  cout << event->nParticles() << endl;

  for (int i = 0; i < event->eventNumber(); i++) {
    cout << event->particle(i)->charge << " " << event->particle(i)->mom_x
         << " " << event->particle(i)->mom_y << " " << event->particle(i)->mom_z
         << endl;
  }

  return;
}
