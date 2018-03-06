#include "Event.h"
#include "EventDump.h"
#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

EventDump::EventDump() {}

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
