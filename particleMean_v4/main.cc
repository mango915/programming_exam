#include "AnalysisSteering.h"
#include "Constants.h"
#include "Event.h"
#include "EventDump.h"
#include "EventReadFromFile.h"
#include "EventSim.h"
#include "EventSource.h"
#include "MassMean.h"
#include "ParticleMass.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Constants constants = Constants::instance();
double mass(const Event *event);

int main(int argc, char *argv[]) {
  EventSource *es;
  const string first_argument = argv[1];

  if (first_argument == "input") {
    const string file_input = argv[2];
    es = new EventReadFromFile(file_input);
  } else if (first_argument == "sim") {

    const string nevt = argv[2];
    const string seed = (argc > 3 ? argv[3] : "1");
    stringstream sstr;
    unsigned int n;
    sstr.str(nevt);
    sstr >> n;
    sstr.clear();
    unsigned int s;
    sstr.str(seed);
    sstr >> s;
    es = new EventSim(n, s);
  } else {
    cout << "invalid keyword" << endl;
    return 0;
  }
  vector<AnalysisSteering *> aList;
  aList.push_back(new EventDump);
  aList.push_back(new ParticleMass);
  int l = aList.size();
  int i;
  for (i = 0; i < l; ++i)
    aList[i]->beginJob();

  const Event *ev;
  while ((ev = es->get()) != 0) {
    for (i = 0; i < l; ++i) {
      aList[i]->process(*ev);
    }
    delete ev;
  }
  for (i = 0; i < l; ++i)
    aList[i]->endJob();

  return 0;
}

double mass(const Event *event) {
  int no_positive = 0, no_negative = 0;
  double mom_x_sum = 0, mom_y_sum = 0, mom_z_sum = 0;
  double energy_sum_K0 = 0, energy_sum_Lambda0 = 0;
  double inv_mass_K0 = 0, inv_mass_Lambda0 = 0;
  if (event->nParticles() != 2) {
    return -1;
  }
  for (int i = 0; i < event->nParticles(); i++) {
    if (event->particle(i)->charge == +1) {
      ++no_positive;
    } else if (event->particle(i)->charge == -1) {
      ++no_negative;
    } else {
      return -1;
    }
    mom_x_sum += event->particle(i)->mom_x;
    mom_y_sum += event->particle(i)->mom_y;
    mom_z_sum += event->particle(i)->mom_z;
    energy_sum_K0 +=
        Utilities::energy(event->particle(i)->mom_x, event->particle(i)->mom_y,
                          event->particle(i)->mom_z, constants.get_massPion());
    if (event->particle(i)->charge == -1) {
      energy_sum_Lambda0 += Utilities::energy(
          event->particle(i)->mom_x, event->particle(i)->mom_y,
          event->particle(i)->mom_z, constants.get_massPion());
    } else if (event->particle(i)->charge == +1) {
      energy_sum_Lambda0 += Utilities::energy(
          event->particle(i)->mom_x, event->particle(i)->mom_y,
          event->particle(i)->mom_z, constants.get_massProton());
    } else {
      return -1;
    }
  }

  if ((no_positive != 1) || (no_negative != 1)) {
    return -1;
  }
  inv_mass_K0 =
      Utilities::inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_K0);
  inv_mass_Lambda0 =
      Utilities::inv_mass(mom_x_sum, mom_y_sum, mom_z_sum, energy_sum_Lambda0);

  if (abs(inv_mass_K0 - constants.get_massK0()) <
      abs(inv_mass_Lambda0 - constants.get_massLambda0())) {
    return inv_mass_K0;
  } else if (abs(inv_mass_K0 - constants.get_massK0()) >
             abs(inv_mass_Lambda0 - constants.get_massLambda0())) {
    return inv_mass_Lambda0;
  } else {
    return -1;
  }
}
