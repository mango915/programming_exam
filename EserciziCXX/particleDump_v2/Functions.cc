#include "Composite.h"
#include "Functions.h"
#include <fstream>
#include <iostream>

using namespace std;

// read the Event characteristics from a file
const Event *read(ifstream &file) {

  Event *temp_event = new Event;

  // make a temporary Event, fill it with data (if exist) and return it as a
  // pointer
  if (file >> temp_event->id) {
    file >> temp_event->decay_x >> temp_event->decay_y >> temp_event->decay_z >>
        temp_event->no_particles;
    temp_event->particles = new Particle *[temp_event->no_particles];
    for (int i = 0; i < temp_event->no_particles; i++) {
      Particle *temp_particle = new Particle;
      file >> temp_particle->charge >> temp_particle->mom_x >>
          temp_particle->mom_y >> temp_particle->mom_z;
      temp_event->particles[i] = temp_particle;
    }
  } else {
    return 0;
  }

  return temp_event;
}

// dump Event characteristics to the screen
void dump(const Event *event) {

  cout << event->id << endl;
  cout << event->decay_x << " " << event->decay_y << " " << event->decay_z
       << endl;
  cout << event->no_particles << endl;

  // each Particle
  for (int i = 0; i < event->no_particles; i++) {
    cout << event->particles[i]->charge << " " << event->particles[i]->mom_x
         << " " << event->particles[i]->mom_y << " "
         << event->particles[i]->mom_z << endl;
  }

  return;
}

// delete the composite objects
void clear(const Event *event) {
  for (int i = 0; i < event->no_particles; i++) {
    delete event->particles[i];
  }
  delete event->particles;
  delete event;
  return;
}
