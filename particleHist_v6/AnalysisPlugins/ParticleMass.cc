#include "../AnalysisFramework/AnalysisFactory.h"
#include "../AnalysisFramework/AnalysisInfo.h"
#include "../AnalysisFramework/Event.h"
#include "../AnalysisObjects/MassMean.h"
#include "../AnalysisObjects/ParticleReco.h"
#include "ActiveObserver.h"
#include "ParticleMass.h"
#include "TFileProxy.h"
#include "TH1F.h"
#include <fstream>
#include <math.h>
#include <string>
using namespace std;

// concrete factory to create an ElementReco analyzer
class ElementRecoFactory : public AnalysisFactory::AbsFactory {
public:
  // assign "plot" as name for this analyzer and factory
  ElementRecoFactory() : AnalysisFactory::AbsFactory("mass") {}
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
  ifstream *ranges = new ifstream(aInfo->value("range_file").c_str());
  string type;
  float begin, end;
  while (*ranges >> type) {
    *ranges >> begin >> end;
    pCreate(type, begin, end);
  }
  return;
}

void ParticleMass::endJob() {

  // ROOT file handling
  TDirectory *currentDir = gDirectory;
  TFileProxy *file = new TFileProxy(aInfo->value("plot").c_str(), "CREATE");

  // histo filled and statistic done
  int n = pList.size();
  for (int i = 0; i < n; ++i) {
    MassMean *mMean = pList[i]->mMean;
    TH1F *hMean = pList[i]->hMean;
    mMean->compute();
    cout << mMean->nEvents() << "  " << mMean->mMean() << "  " << mMean->mRMS()
         << endl;
    hMean->Write();
  }

  // more ROOT file handling
  file->Close();
  delete file;
  currentDir->cd();

  return;
}

// loop over energy distributions and pass event to each of them
void ParticleMass::update(const Event &ev) {
  static ParticleReco *data = ParticleReco::instance();
  unsigned int n = pList.size();
  unsigned int i;
  for (i = 0; i < n; ++i) {
    data->update(ev);
    if (pList[i]->mMean->add(ev))
      pList[i]->hMean->Fill(data->invariantMass());
  }
  return;
}

// create energy distribution for events with total energy in given range
void ParticleMass::pCreate(const string &name, float min, float max) {

  // create name for TH1F object
  string title = "mass " + name;
  const char *hName = title.c_str();

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
