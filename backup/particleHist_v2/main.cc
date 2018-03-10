#include "AnalysisInfo.h"
#include "Event.h"
#include "EventDump.h"
#include "EventReadFromFile.h"
#include "ParticleMass.h"
#include "SourceFactory.h"
#include <iostream>
using namespace std;

double mass(const Event *event);

int main(int argc, char *argv[]) {
  AnalysisInfo *info = new AnalysisInfo(argc, argv);
  EventSource *event_source = SourceFactory::create(info);

  vector<AnalysisSteering *> aList;
  aList.push_back(new EventDump);
  aList.push_back(new ParticleMass);
  int l = aList.size();
  int i;

  for (i = 0; i < l; ++i)
    aList[i]->beginJob();

  const Event *event;

  while ((event = event_source->get()) != 0) {
    for (i = 0; i < l; ++i) {
      aList[i]->process(*event);
    }
    delete event;
  }

  for (i = 0; i < l; ++i)
    aList[i]->endJob();

  return 0;
}
