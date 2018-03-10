#include "../util/include/Dispatcher.h"
#include "Event.h"
#include "EventSource.h"

EventSource::EventSource() {}

EventSource::~EventSource() {}

void EventSource::run() {
  const Event *event;
  while ((event = get()) != 0) {
    Dispatcher<Event>::notify(*event);
    delete event;
  }
  return;
}
