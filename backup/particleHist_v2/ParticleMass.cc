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
  pCreate("K0", 0.490, 0.505);
  pCreate("Lambda0", 1.115, 1.116);
  return;
}

void ParticleMass::endJob() {
  TDirectory *currentDir = gDirectory;
  TFile *file = new TFile("hist.root", "CREATE");
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
  file->Close();
  delete file;
  currentDir->cd();
  return;
}

void ParticleMass::process(const Event &ev) {
  // loop over energy distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;
  for (i = 0; i < n; ++i) {
    pList[i]->mMean->add(ev);
    pList[i]->hMean->Fill(mass(&ev));
  }
  return;
}

void ParticleMass::pCreate(const string &name, float min, float max) {

  // create energy distribution for events with total energy in given range

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
