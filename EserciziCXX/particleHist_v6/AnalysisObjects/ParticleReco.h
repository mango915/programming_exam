#ifndef ParticleReco_h
#define ParticleReco_h

#include "../AnalysisFramework/Event.h"

#include "LazyObserver.h"
#include "Singleton.h"

class ParticleReco : public Singleton<ParticleReco>,
                     public LazyObserver<Event> {

  friend class Singleton<ParticleReco>;

public:
  // particle types
  enum ParticleType { K0, Lambda0, unknown };

  // recompute informations for new event
  virtual void update(const Event &event);

  // return particle energy
  double totalEnergy();
  // return particle mass
  double invariantMass();
  // return particle type
  ParticleType particleType();
  static ParticleReco *instance();

private:
  // private constructor and destructor for singleton
  ParticleReco();
  ~ParticleReco();

  // dummy copy constructor and assignment to prevent unadvertent copy
  ParticleReco(const ParticleReco &x);
  ParticleReco &operator=(const ParticleReco &x);

  // particle type
  ParticleType type;
  // particle energy
  double energy;
  // particle mass
  double mass;
};

#endif
