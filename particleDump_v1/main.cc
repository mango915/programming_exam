#include <fstream>
#include <iostream>

using namespace std;

int read(ifstream *file, float *decay_x, float *decay_y, float *decay_z,
         int charges[], float mom_x[], float mom_y[], float mom_z[]) {
  int no_particles;
  *file >> *decay_x >> *decay_y >> *decay_z >> no_particles;
  for (int i = 0; i < no_particles; i++) {
    *file >> charges[i] >> mom_x[i] >> mom_y[i] >> mom_z[i];
  }
  return no_particles;
}

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

int main(int argc, char const *argv[]) {
  ifstream file(argv[1]);
  int charges[10];
  int id_event;
  int no_particles;
  float decay_x, decay_y, decay_z;
  float mom_x[10], mom_y[10], mom_z[10];
  while (file >> id_event) {
    no_particles =
        read(&file, &decay_x, &decay_y, &decay_z, charges, mom_x, mom_y, mom_z);
    dump(id_event, no_particles, decay_x, decay_y, decay_z, charges, mom_x,
         mom_y, mom_z);
  }
  return 0;
}
