#include "AnalysisFactory.h"
#include "AnalysisInfo.h"
#include "Event.h"
#include "MassMean.h"
#include "ParticleMass.h"
#include "TFile.h"
#include "TH1F.h"
#include <math.h>

using namespace std;

double mass(const Event *ev);

// concrete factory to create an ElementReco analyzer
class ElementRecoFactory : public AnalysisFactory::AbsFactory {
public:
  // assign "plot" as name for this analyzer and factory
  ElementRecoFactory() : AnalysisFactory::AbsFactory("plot") {}
  // create an ElementReco when builder is run
  virtual AnalysisSteering *create(const AnalysisInfo *info) {
    return new ParticleMass(info);
  }
};
// create a global ElementRecoFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ElementRecoFactory will be available with name "plot".
static ElementRecoFactory er;

ParticleMass::ParticleMass(const AnalysisInfo *info) : AnalysisSteering(info) {}

ParticleMass::~ParticleMass() {}

void ParticleMass::beginJob() {
  pList.reserve(10);
  // note that now MassMean objects creation is delegate to pCreate
  pCreate("K0", 0.490, 0.505);
  pCreate("Lambda0", 1.115, 1.116);
  return;
}

void ParticleMass::endJob() {

  // ROOT file handling
  TDirectory *currentDir = gDirectory;
  TFile *file = new TFile(aInfo->value("plot").c_str(), "CREATE");

  // histo filled and statistic done
  int n = pList.size();
  for (int i = 0; i < n; ++i) {
    MassMean *mMean = pList[i]->mMean;
    TH1F *hMean = pList[i]->hMean;
    mMean->compute();
    double mean = mMean->mMean();
    double rms = mMean->mRMS();
    hMean->Fill(mean, rms);
    hMean->Write();
  }

  // more ROOT file handling
  file->Close();
  delete file;
  currentDir->cd();

  return;
}

// loop over energy distributions and pass event to each of them
void ParticleMass::process(const Event &ev) {
  unsigned int n = pList.size();
  unsigned int i;
  for (i = 0; i < n; ++i) {
    pList[i]->mMean->add(ev);
    pList[i]->hMean->Fill(mass(&ev));
  }
  return;
}

// create energy distribution for events with total energy in given range
void ParticleMass::pCreate(const string &name, float min, float max) {

  // create name for TH1F object
  const char *hName = name.c_str();

  // bin number equal to point number
  int nBinD = 100;

  // create TH1F and statistic objects and store their pointers
  Particle *bc = new Particle;
  bc->name = name;
  bc->mMean = new MassMean(min, max);
  bc->hMean = new TH1F(hName, hName, nBinD, min, max);
  pList.push_back(bc);

  return;
}
