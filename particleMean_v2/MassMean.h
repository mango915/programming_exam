#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

 public:

  MassMean( float min, float max ); // mass range
  ~MassMean();

  void add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  ...                               // return number of accepted events
  ...                               // return mean mass
  ...                               // return rms  mass

 private:

  ... // min mass
  ... // max mass

  ... // number of accepted events
  ... // sum of masses
  ... // sum of masses square

  ... // mean mass
  ... // rms  mass

};

#endif

