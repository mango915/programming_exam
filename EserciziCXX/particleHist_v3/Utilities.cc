#include "Utilities.h"
#include <math.h>

double Utilities::energy(double p_x, double p_y, double p_z,
                         double invariant_mass) {
  return sqrt(pow(p_x, 2) + pow(p_y, 2) + pow(p_z, 2) + pow(invariant_mass, 2));
}

double Utilities::inv_mass(double p_x, double p_y, double p_z, double energy) {
  return sqrt(pow(energy, 2) - pow(p_x, 2) - pow(p_y, 2) - pow(p_z, 2));
}
