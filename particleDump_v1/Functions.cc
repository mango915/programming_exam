#include "Functions.h"
#include <fstream>
#include <iostream>

using namespace std;

// read the Event characteristics from a file
int read(ifstream &file, float *decay_x, float *decay_y, float *decay_z,
         int charges[], float mom_x[], float mom_y[], float mom_z[]) {
  int no_particles;
  file >> *decay_x >> *decay_y >> *decay_z >> no_particles;
  for (int i = 0; i < no_particles; i++) {
    file >> charges[i] >> mom_x[i] >> mom_y[i] >> mom_z[i];
  }
  return no_particles;
}

// dump Event characteristics to the screen
void dump(int id_event, int no_particles, float decay_x, float decay_y,
          float decay_z, int charges[], float mom_x[], float mom_y[],
          float mom_z[]) {
  cout << id_event << endl;
  cout << decay_x << " " << decay_y << " " << decay_z << endl;
  cout << no_particles << endl;
  for (int i = 0; i < no_particles; i++) {
    cout << charges[i] << mom_x[i] << " " << mom_y[i] << " " << mom_z[i]
         << endl;
  }
  return;
}
