#include "AnalysisInfo.h" //handling input arguments
#include "Event.h"        //Event objects

#include "EventSource.h" //handle EventReadFromFile and EventSim derivated classes
#include "SourceFactory.h" //create a proper instance of EventSource derivates

#include "EventDump.h" // dump on the screen at endJob, inherit from AnalysisSteering
#include "ParticleMass.h" // make statistical operations, handling MassMean class and inherit from AnalysisSteering

#include <iostream>
using namespace std;

double mass(const Event *event);

int main(int argc, char *argv[]) {

  // store command line parameters
  AnalysisInfo *info = new AnalysisInfo(argc, argv);

  // create data source
  EventSource *event_source = SourceFactory::create(info);

  // analysis handling
  vector<AnalysisSteering *> aList;
  aList.push_back(new EventDump);
  aList.push_back(new ParticleMass);
  int l = aList.size();
  int i;

  // inizialize decay hypothesis
  for (i = 0; i < l; ++i)
    aList[i]->beginJob();

  const Event *event;

  // update decay hypothesis with data
  while ((event = event_source->get()) != 0) {
    for (i = 0; i < l; ++i) {
      aList[i]->process(*event);
    }
    delete event;
  }

  // process results and dump them on screen
  for (i = 0; i < l; ++i)
    aList[i]->endJob();

  return 0;
}
