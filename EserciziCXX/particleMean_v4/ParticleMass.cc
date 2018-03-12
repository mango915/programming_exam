#include "MassMean.h"
#include "ParticleMass.h"
#include <iostream>
#include <math.h>

using namespace std;

ParticleMass::ParticleMass() {}

ParticleMass::~ParticleMass() {}

void ParticleMass::beginJob() {
  pList.reserve(10);
  pList.push_back(new MassMean(0.490, 0.505));
  pList.push_back(new MassMean(1.114, 1.118));
  return;
}

void ParticleMass::endJob() {

  // statistic and dump results
  int n = pList.size();
  for (int i = 0; i < n; ++i) {
    MassMean *massmean = pList[i];
    massmean->compute();
    cout << massmean->nEvents() << " " << massmean->mMean() << " "
         << massmean->mRMS() << endl;
  }

  return;
}

// loop over energy distributions and pass event to each of them
void ParticleMass::process(const Event &ev) {
  unsigned int n = pList.size();
  unsigned int i;
  for (i = 0; i < n; ++i)
    pList[i]->add(ev);
  return;
}
