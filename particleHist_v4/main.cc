#include "AnalysisFactory.h" // abstract factory for create analyzers
#include "AnalysisInfo.h"    // handling input arguments
#include "Event.h"           // Event objects

#include "EventSource.h" //handle EventReadFromFile and EventSim derivated classes
#include "SourceFactory.h" //create a proper instance of EventSource derivates

#include "EventDump.h" // dump on the screen at endJob, inherit from AnalysisSteering
#include "ParticleMass.h" // make statistical operations, handling MassMean class and inherit from AnalysisSteering

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

  // store command line parameters
  AnalysisInfo *info = new AnalysisInfo(argc, argv);

  // create data source
  EventSource *event_source = SourceFactory::create(info);

  // create a list of analyzers
  vector<AnalysisSteering *> aList = AnalysisFactory::create(info);

  // variables to loop over analyzers
  int l = aList.size();
  int i;

  // initialize all analyzers
  for (i = 0; i < l; ++i)
    aList[i]->beginJob();

  event_source->run();

  // finalize all analyzers
  for (i = 0; i < l; ++i)
    aList[i]->endJob();

  return 0;
}
