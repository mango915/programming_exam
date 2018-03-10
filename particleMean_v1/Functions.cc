#include "Composite.h"
#include "Constants.h"
#include "Functions.h"
#include "iostream"
#include <fstream>
#include <math.h>

using namespace std;

// compute energy from momentum x,y,z components and invariant mass
double energy(double p_x, double p_y, double p_z, double invariant_mass) {
  return sqrt(pow(p_x, 2) + pow(p_y, 2) + pow(p_z, 2) + pow(invariant_mass, 2));
}
// compute invariant mass from momentum x,y,z components and energy
double inv_mass(double p_x, double p_y, double p_z, double energy) {
  return sqrt(pow(energy, 2) - pow(p_x, 2) - pow(p_y, 2) - pow(p_z, 2));
}

// return the most likehood invariant mass of the original decaying particle
double mass(const Event *event) {
  int no_positive = 0, no_negative = 0;
  double mom_x_sum = 0, mom_y_sum = 0, mom_z_sum = 0;
  double energy_sum_K0 = 0, energy_sum_Lambda0 = 0;
  double inv_mass_K0 = 0, inv_mass_Lambda0 = 0;
  typedef const Particle *part_ptr;
  const part_ptr *particles = event->particles;

  // computational economy
  if (event->no_particles != 2) {
    return -1;
  }

  for (int i = 0; i < event->no_particles; i++) {
    if (particles[i]->charge == +1) {
      ++no_positive;
    } else if (particles[i]->charge == -1) {
      ++no_negative;
    } else {
      return -1;
    }
    mom_x_sum += particles[i]->mom_x;
    mom_y_sum += particles[i]->mom_y;
    mom_z_sum += particles[i]->mom_z;
    energy_sum_K0 += energy(particles[i]->mom_x, particles[i]->mom_y,
                            particles[i]->mom_z, massPion);
    if (particles[i]->charge == -1) {
      energy_sum_Lambda0 += energy(particles[i]->mom_x, particles[i]->mom_y,
                                   particles[i]->mom_z, massPion);
    } else if (particles[i]->charge == +1) {
      energy_sum_Lambda0 += energy(particles[i]->mom_x, particles[i]->mom_y,
                                   particles[i]->mom_z, massProton);
    } else {
      return -1;
    }
  }

  // check charges
  if ((no_positive != 1) || (no_negative != 1)) {
    return -1;
  }

  inv_mass_K0 = inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_K0);
  inv_mass_Lambda0 =
      inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_Lambda0);

  // return the more likehood invariant mass
  if (fabs(inv_mass_K0 - massK0) < fabs(inv_mass_Lambda0 - massLambda0)) {
    return inv_mass_K0;
  } else if (fabs(inv_mass_K0 - massK0) >
             fabs(inv_mass_Lambda0 - massLambda0)) {
    return inv_mass_Lambda0;
  } else {
    return -1;
  }
}

// update partial data for statistics
bool add(const Event *event, double min_mass, double max_mass,
         double *sum_inv_mass, double *sum_squares) {
  double temp_mass = 0;
  temp_mass = mass(event);

  if (temp_mass == -1)
    return false;

  if ((temp_mass <= max_mass) && (temp_mass >= min_mass)) {
    *sum_inv_mass += temp_mass;
    *sum_squares += pow(temp_mass, 2);
    return true;
  } else {
    return false;
  }
}

// read the Event characteristics from a file
const Event *read(ifstream &file) {
  Event *temp_event = new Event;

  if (file >> temp_event->id) {
    file >> temp_event->decay_x >> temp_event->decay_y >> temp_event->decay_z >>
        temp_event->no_particles;
    temp_event->particles = new Particle *[temp_event->no_particles];

    for (int i = 0; i < temp_event->no_particles; i++) {
      Particle *temp_particle = new Particle;
      file >> temp_particle->charge >> temp_particle->mom_x >>
          temp_particle->mom_y >> temp_particle->mom_z;
      temp_event->particles[i] = temp_particle;
    }
  } else {
    return 0;
  }
  return temp_event;
}

// dump Event characteristics to the screen
void dump(const Event *event) {
  cout << event->id << endl;
  cout << event->decay_x << " " << event->decay_y << " " << event->decay_z
       << endl;
  cout << event->no_particles << endl;

  for (int i = 0; i < event->no_particles; i++) {
    cout << event->particles[i]->charge << " " << event->particles[i]->mom_x
         << " " << event->particles[i]->mom_y << " "
         << event->particles[i]->mom_z << endl;
  }

  return;
}

// delete composite objects
void clear(const Event *event) {
  for (int i = 0; i < event->no_particles; i++) {
    delete event->particles[i];
  }
  delete[] event->particles;
  delete event;
  return;
}
