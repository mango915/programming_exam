#ifndef ParticleLifetime_h
#define ParticleLifetime_h

#include "../AnalysisFramework/AnalysisSteering.h"
#include "ActiveObserver.h"
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
    LifetimeFit *tFit;
    TH1F *hFit;
  };
  // set of particles
  std::vector<Particle *> pList;

  void pCreate(const std::string &name, double min, double max, double timeMin,
               double timeMax, double scanMin, double scanMax, double scanStep);
};

#endif
