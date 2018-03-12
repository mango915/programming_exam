#ifndef LifetimeFit_h
#define LifetimeFit_h

#include <vector>

class Event;

class LifetimeFit {

public:
  LifetimeFit(double min_mass, double max_mass, double min_time,
              double max_time, double min_scan, double max_scan,
              double scan_step); // parameters
  ~LifetimeFit();

  bool add(const Event &ev); // add data from a new event
  void compute();            // compute mean and rms

  double lifeTime();
  double lifeTimeError();

  int nEvents() const; // return number of accepted events

private:
  double min_mass;
  double max_mass;
  double min_time;
  double max_time;
  double min_scan;
  double max_scan;
  double scan_step;

  std::vector<double> decay_times;

  double p_lifetime_mean;
  double p_lifitime_error;
};

#endif
