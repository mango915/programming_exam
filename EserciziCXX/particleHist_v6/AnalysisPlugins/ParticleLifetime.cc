#include "../AnalysisFramework/AnalysisFactory.h"
#include "../AnalysisFramework/AnalysisInfo.h"
#include "../AnalysisObjects/LifetimeFit.h"
#include "../AnalysisObjects/ProperTime.h"
#include "ActiveObserver.h"
#include "ParticleLifetime.h"
#include "TFileProxy.h"
#include "TH1F.h"
#include <fstream>
#include <string>

using namespace std;

// concrete factory to create an ElementReco analyzer
class ElementTimeFactory : public AnalysisFactory::AbsFactory {
public:
  // assign "plot" as name for this analyzer and factory
  ElementTimeFactory() : AnalysisFactory::AbsFactory("time") {}
  // create an ElementReco when builder is run
  virtual AnalysisSteering *create(const AnalysisInfo *info) {
    return new ParticleLifetime(info);
  }
};
// create a global ElementRecoFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ElementRecoFactory will be available with name "plot".
static ElementTimeFactory plt;

ParticleLifetime::ParticleLifetime(const AnalysisInfo *info)
    : AnalysisSteering(info) {}

ParticleLifetime::~ParticleLifetime() {}

void ParticleLifetime::beginJob() {
  pList.reserve(10);
  ifstream *ranges = new ifstream(aInfo->value("fit_file").c_str());
  string type;
  double begin, end, timemin, timemax, scanmin, scanmax, scanstep;
  while (*ranges >> type) {
    *ranges >> begin >> end >> timemin >> timemax >> scanmin >> scanmax >>
        scanstep;
    pCreate(type, begin, end, timemin, timemax, scanmin, scanmax, scanstep);
  }
  return;
}

void ParticleLifetime::endJob() {
  TDirectory *currentDir = gDirectory;
  TFileProxy *file = new TFileProxy(aInfo->value("plot").c_str(), "CREATE");
  int n = pList.size();

  for (int i = 0; i < n; ++i) {
    LifetimeFit *tFit = pList[i]->tFit;
    TH1F *hFit = pList[i]->hFit;
    tFit->compute();
    cout << tFit->nEvents() << "  " << tFit->lifeTime() << "  "
         << tFit->lifeTimeError() << endl;
    hFit->Write();
  }
  file->Close();
  delete file;
  currentDir->cd();
  return;
}

void ParticleLifetime::update(const Event &ev) {
  static ProperTime *data = ProperTime::instance();
  // loop over energy distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;
  for (i = 0; i < n; ++i) {
    data->update(ev);
    if (pList[i]->tFit->add(ev)) {
      double time_temp = data->decayTime();
      if (time_temp != -1)
        pList[i]->hFit->Fill(time_temp);
    }
  }
  return;
}

void ParticleLifetime::pCreate(const string &name, double min, double max,
                               double timeMin, double timeMax, double scanMin,
                               double scanMax, double scanStep) {

  // create energy distribution for events with total energy in given range

  // create name for TH1F object
  string title = "time " + name;
  const char *hName = title.c_str();

  // bin number equal to point number
  int nBinD = 100;

  // create TH1F and statistic objects and store their pointers
  Particle *bc = new Particle;
  bc->name = name;
  bc->tFit =
      new LifetimeFit(min, max, timeMin, timeMax, scanMin, scanMax, scanStep);
  bc->hFit = new TH1F(hName, hName, nBinD, timeMin, timeMax);
  pList.push_back(bc);
  return;
}
