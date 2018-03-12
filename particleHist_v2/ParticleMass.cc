#include "Event.h"
#include "MassMean.h"
#include "ParticleMass.h"
#include "TFile.h"
#include "TH1F.h"
#include <iostream>
#include <math.h>

using namespace std;

double mass(const Event *ev);

ParticleMass::ParticleMass() {}

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
  TFile *file = new TFile("hist.root", "CREATE");

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
void ParticleMass::process(const Event &ev) {
  unsigned int n = pList.size();
  unsigned int i;
  for (i = 0; i < n; ++i) {
    if (pList[i]->mMean->add(ev))
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
