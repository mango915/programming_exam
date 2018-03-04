#include <fstream>
#include <iostream>

using namespace std;

struct Particle {
  int charge;
  float mom_x, mom_y, mom_z;
};

struct Event {
  int id;
  float decay_x, decay_y, decay_z;
  int no_particles;
  Particle **particles;
};

const Event *read(ifstream &file) {
  Event *temp_event = new Event;
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

void dump(const Event *event) {
  cout << event->id << endl;
  cout << event->decay_x << " " << event->decay_y << " " << event->decay_z
       << endl;
  cout << event->no_particles << endl;
  for (int i = 0; i < event->no_particles; i++) {
    cout << event->particles[i]->charge << " " << event->particles[i]->mom_x
         << " " << event->particles[i]->mom_y << " "
         << event->particles[i]->mom_z << endl;
  }
  return;
}

void clear(const Event *event) {
  for (int i = 0; i < event->no_particles; i++) {
    delete event->particles[i];
  }
  delete event->particles;
  delete event;
  return;
}

int main(int argc, char const *argv[]) {
  ifstream file(argv[1]);
  const Event *event;
  while ((event = read(file)) != 0) {
    dump(event);
    clear(event);
  }
  return 0;
}
