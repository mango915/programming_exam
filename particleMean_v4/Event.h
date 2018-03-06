#include <vector>
#ifndef Event_h
#define Event_h

class Event {

public:
  Event(int n, float x, float y, float z);
  ~Event();
  struct Particle {
    int charge;
    double mom_x, mom_y, mom_z;
  };

  // add a particle to the event
  void add(float px, float py, float pz, int charge);

  int eventNumber() const;
  float x() const;
  float y() const;
  float z() const;
  int nParticles() const;
  const Particle *particle(unsigned int i) const;

private:
  int id;
  float decay_x, decay_y, decay_z;
  // unsigned int no_particles;
  std::vector<Particle *> particles;
  // const unsigned int max_particles = 10;
};

#endif
