#include "Event.h"
#include <iostream>

Event::Event(int n, float x, float y, float z)
    : id(n), decay_x(x), decay_y(y), decay_z(z), no_particles(0) {
  particles = new const Particle *[max_particles];
}

Event::~Event() {
  for (unsigned int i = 0; i < no_particles; i++) {
    delete particles[i];
  }
  delete[] particles;
}

// add a particle to the Event
void Event::add(float px, float py, float pz, int charge) {
  if (no_particles == max_particles) {
    return;
  }
  Particle *particle = new Particle;
  particle->mom_x = px;
  particle->mom_y = py;
  particle->mom_z = pz;
  particle->charge = charge;
  particles[no_particles] = particle;
  no_particles++;
  return;
}

// getting private data
int Event::eventNumber() const { return id; }
float Event::x() const { return decay_x; };
float Event::y() const { return decay_y; };
float Event::z() const { return decay_z; };
int Event::nParticles() const { return no_particles; };

const Event::Particle *Event::particle(unsigned int i) const {
  if (i < no_particles) {
    return particles[i];
  } else {
    return 0;
  }
}
