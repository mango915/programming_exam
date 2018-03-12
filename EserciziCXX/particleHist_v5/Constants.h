#ifndef Constants_h
#define Constants_h

// singleton class for constants handling
class Constants {

public:
  // instance calling
  static Constants *instance();

  const double get_massPion();
  const double get_massProton();
  const double get_massK0();
  const double get_massLambda0();
  const double get_lightVelocity();

private:
  Constants();
  ~Constants();
  const double massPion;      // GeV/c^2
  const double massProton;    // GeV/c^2
  const double massK0;        // GeV/c^2
  const double massLambda0;   // GeV/c^2
  const double lightVelocity; // cm/ps
};
#endif
