#ifndef ParticleMass_h
#define ParticleMass_h

#include "AnalysisSteering.h"
#include <string>
#include <vector>

class TH1F;
class MassMean;

class ParticleMass : public AnalysisSteering {

public:
  ParticleMass();
  virtual ~ParticleMass();

  virtual void beginJob();
  virtual void endJob();
  virtual void process(const Event &ev);

private:
  struct Particle {
    std::string name;
    MassMean *mMean;
    TH1F *hMean;
  };

  std::vector<Particle *> pList;
  void pCreate(const std::string &name, float min, float max);
};

#endif
