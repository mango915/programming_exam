#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

public:
  MassMean(float min, float max); // mass range
  ~MassMean();

  bool add(const Event &ev); // add data from a new event
  void compute();            // compute mean and rms

  int nEvents() const;  // return number of accepted events
  double mMean() const; // return mean mass
  double mRMS() const;  // return rms  mass

private:
  float min_mass;
  float max_mass;

  int no_accepted_events;
  double sum_of_masses;
  double sum_of_squares;
  double mean;
  double rms;
};

#endif
