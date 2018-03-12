#ifndef Composite_h
#define Composite_h

// single Particle
struct Particle {
  int charge;
  float mom_x, mom_y, mom_z;
};

// whole Event
struct Event {
  int id;
  float decay_x, decay_y, decay_z;
  int no_particles;
  Particle **particles;
};

#endif
