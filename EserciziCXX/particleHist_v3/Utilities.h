#ifndef Utilities_h
#define Utilities_h

class Utilities {
public:
  Utilities();
  ~Utilities();
  static double energy(double p_x, double p_y, double p_z,
                       double invariant_mass);
  // compute invariant mass from momentum x,y,z components and energy
  static double inv_mass(double p_x, double p_y, double p_z, double energy);

private:
};

#endif
