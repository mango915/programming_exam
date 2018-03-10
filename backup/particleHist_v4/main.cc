//#include "AnalysisFactory.h"
//#include "AnalysisInfo.h"
//#include "Event.h"
#include "EventDump.h"
#include "EventReadFromFile.h"
///#include "ParticleMass.h"
#include "SourceFactory.h"
#include <iostream>
#include <vector>
using namespace std;

double mass(const Event *event);

int main(int argc, char *argv[]) {

  // store command line parameters
  AnalysisInfo *info = new AnalysisInfo(argc, argv);
  // create data source
  EventSource *event_source = SourceFactory::create(info);

  vector<AnalysisSteering *> aList;
  aList.push_back(new EventDump(info));
  aList.push_back(new ParticleMass(info));
  int l = aList.size();
  int i;
  // initialize all analyzers
  for (i = 0; i < l; ++i)
    aList[i]->beginJob();
  // loop over events

  event_source->run();

  // finalize all analyzers
  for (i = 0; i < l; ++i)
    aList[i]->endJob();

  return 0;
}
