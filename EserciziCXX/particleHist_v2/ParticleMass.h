#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <string>
#include <vector>

class TH1F;
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
  struct Particle {
    std::string name;
    MassMean *mMean;
    TH1F *hMean;
  };

  // container for decay hypothesis
  std::vector<Particle *> pList;
  void pCreate(const std::string &name, float min, float max);
};

#endif
