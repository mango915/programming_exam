#include <fstream>
#include <iostream>
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

const double massPion = 0.1395706;   // GeV/c^2
const double massProton = 0.938272;  // GeV/c^2
const double massK0 = 0.497611;      // GeV/c^2
const double massLambda0 = 1.115683; // GeV/c^2

struct Particle {
  int charge;
  double mom_x, mom_y, mom_z;
};

struct Event {
  int id;
  double decay_x, decay_y, decay_z;
  int no_particles;
  Particle **particles;
};

double mass(const Event *event);
bool add(const Event *event, double min_mass, double max_mass,
         double *sum_inv_mass, double *sum_squares);
const Event *read(ifstream &file);
void dump(const Event *event);
void clear(const Event *event);

int main(int argc, char const *argv[]) {
  ifstream file(argv[1]);

  const Event *event;
  int no_accepted_events = 0;
  double sum_inv_masses = 0, sum_squares_inv_masses = 0;
  double mean_inv_mass, rms_inv_mass;

  while ((event = read(file)) != 0) {
    if (add(event, 0.490, 0.505, &sum_inv_masses, &sum_squares_inv_masses)) {
      no_accepted_events++;
    }
    // dump(event);
    clear(event);
  }

  mean_inv_mass = sum_inv_masses / no_accepted_events;
  rms_inv_mass = sqrt((sum_squares_inv_masses / no_accepted_events) -
                      pow(mean_inv_mass, 2));
  cout << "La media computata è: " << mean_inv_mass << endl;
  cout << "L'rms computato è: " << rms_inv_mass << endl;

  return 0;
}

double mass(const Event *event) {
  int no_positive = 0, no_negative = 0;
  double mom_x_sum = 0, mom_y_sum = 0, mom_z_sum = 0;
  double energy_sum_K0 = 0, energy_sum_Lambda0 = 0;
  double inv_mass_K0 = 0, inv_mass_Lambda0 = 0;
  typedef const Particle *part_ptr;
  const part_ptr *particles = event->particles;

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

  if ((no_positive != 1) || (no_negative != 1)) {
    return -1;
  }

  inv_mass_K0 = inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_K0);
  inv_mass_Lambda0 =
      inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_Lambda0);

  if (fabs(inv_mass_K0 - massK0) < fabs(inv_mass_Lambda0 - massLambda0)) {
    return inv_mass_K0;
  } else if (fabs(inv_mass_K0 - massK0) >
             fabs(inv_mass_Lambda0 - massLambda0)) {
    return inv_mass_Lambda0;
  } else {
    return -1;
  }
}

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

void clear(const Event *event) {
  for (int i = 0; i < event->no_particles; i++) {
    delete event->particles[i];
  }
  delete[] event->particles;
  delete event;
  return;
}
