#include "EventDump.h"
#include "Event.h"
#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

EventDump::EventDump() {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  return;
}


// function to be called for each event
void EventDump::process( const Event& ev ) {

  // write event number and number of points
  unsigned int n = ev.dataSize();
  cout << ev.eventNumber() << ' '
       << n;

  // write all points
  unsigned int i;
  for ( i = 0; i < n; ++i ) cout << ' ' << ev.energy( i );
  cout << endl;

  return;

}

