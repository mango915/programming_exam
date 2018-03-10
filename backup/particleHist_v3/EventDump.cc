#include "AnalysisFactory.h"
#include "Event.h"
#include "EventDump.h"

#include <iostream>
//#include <math.h>
//#include <stdio.h>

using namespace std;

class EventDumpFactory : public AnalysisFactory::AbsFactory {
public:
  // assign "dump" as name for this analyzer and factory
  EventDumpFactory() : AnalysisFactory::AbsFactory("dump") {}
  // create an EventDump when builder is run
  virtual AnalysisSteering *create(const AnalysisInfo *info) {
    return new EventDump(info);
  }
};
// create a global EventDumpFactory, so that it is created and registered
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;

EventDump::EventDump(const AnalysisInfo *info) : AnalysisSteering(info) {}

EventDump::~EventDump() {}

// function to be called at execution start
void EventDump::beginJob() { return; }

// function to be called at execution end
void EventDump::endJob() { return; }

// function to be called for each event
void EventDump::process(const Event &ev) {
  cout << ev.eventNumber() << endl;
  cout << ev.x() << " " << ev.y() << " " << ev.z() << endl;
  cout << ev.nParticles() << endl;

  for (int i = 0; i < ev.nParticles(); i++) {
    cout << ev.particle(i)->charge << " " << ev.particle(i)->mom_x << " "
         << ev.particle(i)->mom_y << " " << ev.particle(i)->mom_z << endl;
  }

  return;
}
