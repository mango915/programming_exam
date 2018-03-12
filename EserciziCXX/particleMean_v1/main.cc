#include "Composite.h" // composite objects
#include "Functions.h" // objects handling
#include <fstream>     // input handling
#include <iostream>
#include <math.h> // for statistics

using namespace std;

int main(int argc, char const *argv[]) {

  // input file
  ifstream file(argv[1]);

  // usefil declarations
  const Event *event;
  int no_accepted_events = 0;
  double sum_inv_masses = 0, sum_squares_inv_masses = 0;
  double mean_inv_mass, rms_inv_mass;

  // loop over Events
  while ((event = read(file)) != 0) {
    if (add(event, 0.490, 0.505, &sum_inv_masses, &sum_squares_inv_masses)) {
      no_accepted_events++;
    }
    // dump(event);
    clear(event);
  }

  // statistics
  mean_inv_mass = sum_inv_masses / no_accepted_events;
  rms_inv_mass = sqrt((sum_squares_inv_masses / no_accepted_events) -
                      pow(mean_inv_mass, 2));

  // final results
  cout << "La media computata è: " << mean_inv_mass << endl;
  cout << "L'rms computato è: " << rms_inv_mass << endl;
  return 0;
}
