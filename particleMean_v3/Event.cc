#include "Event.h"
#include <iostream>
Event::Event(int n, float x, float y, float z)
    : id(n), decay_x(x), decay_y(y), decay_z(z) {
  particles.reserve(10);
}

Event::~Event() { particles.clear(); }

void Event::add(float px, float py, float pz, int charge) {
  if (particles.size() == 10) {
    return;
  }
  Particle *particle = new Particle;
  particle->mom_x = px;
  particle->mom_y = py;
  particle->mom_z = pz;
  particle->charge = charge;
  particles.push_back(particle);
  return;
}

int Event::eventNumber() const { return id; }
float Event::x() const { return decay_x; };
float Event::y() const { return decay_y; };
float Event::z() const { return decay_z; };
int Event::nParticles() const { return particles.size(); };

const Event::Particle *Event::particle(unsigned int i) const {
  if (i < particles.size()) {
    return particles[i];
  } else {
    return 0;
  }
}