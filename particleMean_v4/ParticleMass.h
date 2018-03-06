#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include "MassMean.h"
#include <vector>

class ParticleMass : public AnalysisSteering {

public:
  ParticleMass();
  virtual ~ParticleMass();

  virtual void beginJob();
  virtual void endJob();
  virtual void process(const Event &ev);

private:
  std::vector<MassMean *> pList;
};

#endif
