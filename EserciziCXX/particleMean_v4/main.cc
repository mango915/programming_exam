#include "Event.h" //Event objects

#include "EventReadFromFile.h" // inherit from EventSource
#include "EventSim.h"          // simulation of events, inherit from EventSource

#include "EventDump.h" // dump on the screen at endJob, inherit from AnalysisSteering
#include "ParticleMass.h" // make statistical operations, handling MassMean class and inherit from AnalysisSteering

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {

  EventSource *es;
  const string first_argument = argv[1];

  // simulation
  if (first_argument == "input") {
    const string file_input = argv[2];
    es = new EventReadFromFile(file_input);
  } else if (first_argument == "sim") {
    const string nevt = argv[2];
    const string seed = (argc > 3 ? argv[3] : "1");
    stringstream sstr;
    unsigned int n;
    sstr.str(nevt);
    sstr >> n;
    sstr.clear();
    unsigned int s;
    sstr.str(seed);
    sstr >> s;
    es = new EventSim(n, s);
  } else {
    cout << "invalid keyword" << endl;
    return 0;
  }

  vector<AnalysisSteering *> aList;
  aList.push_back(new EventDump);
  aList.push_back(new ParticleMass);
  int l = aList.size();
  int i;

  // inizialize decay hypothesis
  for (i = 0; i < l; ++i)
    aList[i]->beginJob();

  const Event *ev;

  // update decay hypothesis with data
  while ((ev = es->get()) != 0) {
    for (i = 0; i < l; ++i) {
      aList[i]->process(*ev);
    }
    delete ev;
  }

  // process results and dump them on screen
  for (i = 0; i < l; ++i)
    aList[i]->endJob();

  return 0;
}
