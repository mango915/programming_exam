#include "EventReadFromFile.h"
//#include "EventSource.h"

//#include "Event.h"

#include <fstream>
//#include <iostream>
//#include <string>

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile(const string &name) {
  file = new ifstream(name.c_str(), ios::binary);
}

EventReadFromFile::~EventReadFromFile() { delete file; }

// get an event
const Event *EventReadFromFile::get() { return readFile(); }

// read an event
const Event *EventReadFromFile::readFile() {

  int id_temp;
  float decay_x_temp, decay_y_temp, decay_z_temp;
  int no_particles;
  if (!(*file >> id_temp)) {
    return 0;
  }

  *file >> decay_x_temp >> decay_y_temp >> decay_z_temp >> no_particles;
  Event *event = new Event(id_temp, decay_x_temp, decay_y_temp, decay_z_temp);

  for (int i = 0; i < no_particles; i++) {
    int charge;
    float mom_x_temp, mom_y_temp, mom_z_temp;
    *file >> charge >> mom_x_temp >> mom_y_temp >> mom_z_temp;
    event->add(mom_x_temp, mom_y_temp, mom_z_temp, charge);
  }

  return event;
}
