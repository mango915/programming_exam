#include "Event.h"     //Event objects
#include "Functions.h" // mass, read and dump functions
#include "MassMean.h"  // statistical handling of Events
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

  // input file
  string input_file = argv[1];
  ifstream file(input_file.c_str());

  // two decays hypothesis
  MassMean *K0 = new MassMean(0.490, 0.505);
  MassMean *Lambda0 = new MassMean(1.114, 1.118);

  const Event *ev;

  // loop over events, adding them to the two hypothesis
  while ((ev = read(file)) != 0) {
    K0->add(*ev);
    Lambda0->add(*ev);
    delete ev;
  }

  // compute results
  K0->compute();
  Lambda0->compute();

  // dump the results
  cout << K0->nEvents() << " " << K0->mMean() << " " << K0->mRMS() << endl;
  cout << Lambda0->nEvents() << " " << Lambda0->mMean() << " "
       << Lambda0->mRMS() << endl;

  return 0;
}
