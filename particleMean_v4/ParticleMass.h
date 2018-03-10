#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <vector>

class MassMean;

// class for handling various decay hypothesis
class ParticleMass : public AnalysisSteering {

public:
  ParticleMass();
  virtual ~ParticleMass();

  // function to be called at execution start
  virtual void beginJob();
  // function to be called at execution end
  virtual void endJob();
  // function to be called for each event
  virtual void process(const Event &ev);

private:
  // container for decay hypothesis
  std::vector<MassMean *> pList;
};

#endif
