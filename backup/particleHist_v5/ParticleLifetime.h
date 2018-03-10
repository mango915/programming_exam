#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include "../util/include/ActiveObserver.h"
#include "AnalysisSteering.h"
#include <string>
#include <vector>

class TH1F;
class LifetimeFit;

class ParticleLifetime : public AnalysisSteering, public ActiveObserver<Event> {

public:
  ParticleLifetime(const AnalysisInfo *info);
  virtual ~ParticleLifetime();

  // functions to be called at execution start, end and flor each event,
  // respectively
  virtual void beginJob();
  virtual void endJob();
  virtual void update(const Event &ev);

private:
  // Particle informations
  struct Particle {
    std::string name;
    LifetimeFit *mMean;
    TH1F *hMean;
  };
  // set of particles
  std::vector<Particle *> pList;

  void pCreate(const std::string &name, float min, float max, float timeMin,
               float timeMax);
};

#endif
