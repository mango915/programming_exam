#include "LifetimeFit.h"
#include "ParticleReco.h"
#include "ProperTime.h"
#include "QuadraticFitter.h"
#include <fstream>
#include <math.h>

using namespace std;

LifetimeFit::LifetimeFit(double min_mass, double max_mass, double min_time,
                         double max_time, double min_scan, double max_scan,
                         double scan_step)
    : min_mass(min_mass), max_mass(max_mass), min_time(min_time),
      max_time(max_time), min_scan(min_scan), max_scan(max_scan),
      scan_step(scan_step) {}

LifetimeFit::~LifetimeFit() {}

// add data from a new event
bool LifetimeFit::add(const Event &ev) {
  static ParticleReco *reco = ParticleReco::instance();
  static ProperTime *time = ProperTime::instance();
  double time_temp = time->decayTime();
  if (time_temp == -1)
    return false;

  // data->update(ev);
  double temp_mass = (reco->invariantMass());
  // check for mass being in range
  if ((temp_mass <= max_mass) && (temp_mass >= min_mass)) {
    if ((time_temp >= min_time) && (time_temp <= max_time)) {
      decay_times.push_back(time_temp);
      // update events vector
      return true;

    } else {
      return false;
    }
  } else {
    return false;
  }
}

// compute
void LifetimeFit::compute() {
  QuadraticFitter *fit = new QuadraticFitter;
  for (double t = min_scan; t < max_scan; t += scan_step) {
    double L = 0;
    for (double t_i : decay_times) {
      L += (t_i / t) + log(t) + log(exp(-min_time / t) + exp(-max_time / t));
    }
    fit->add(t, L);
  }
  p_lifetime_mean = -fit->b() / (2. * fit->c());
  p_lifitime_error = 1. / sqrt(2. * fit->c());
  delete fit;
  return;
}

double LifetimeFit::lifeTime() { return p_lifetime_mean; }
double LifetimeFit::lifeTimeError() { return p_lifitime_error; }

int LifetimeFit::nEvents() const { return decay_times.size(); }
