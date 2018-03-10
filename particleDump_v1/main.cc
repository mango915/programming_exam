#include "Functions.h" //for Events handling
#include <fstream>     // for input handling

using namespace std;

int main(int argc, char const *argv[]) {

  // input file
  ifstream file(argv[1]);

  // useful variables delcaration
  int charges[10];
  int id_event;
  int no_particles;
  float decay_x, decay_y, decay_z;
  float mom_x[10], mom_y[10], mom_z[10];

  // loop over Events
  while (file >> id_event) {
    no_particles =
        read(file, &decay_x, &decay_y, &decay_z, charges, mom_x, mom_y, mom_z);
    dump(id_event, no_particles, decay_x, decay_y, decay_z, charges, mom_x,
         mom_y, mom_z);
  }

  return 0;
}
