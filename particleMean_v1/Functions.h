#ifndef Functions_h
#define Functions_h

#include <fstream>

struct Event;

// compute energy from momentum components and invariant mass (relativistic)
double energy(double p_x, double p_y, double p_z, double invariant_mass);

// compute invariant mass from momentum components and energy (relativistic)
double inv_mass(double p_x, double p_y, double p_z, double energy);

// return the most likehood invariant mass of the original decaying particle
double mass(const Event *event);

// update partial data for statistics
bool add(const Event *event, double min_mass, double max_mass,
         double *sum_inv_mass, double *sum_squares);

// read the Event characteristics from a file
const Event *read(std::ifstream &file);

// dump Event characteristics to the screen
void dump(const Event *event);

// delete composite objects
void clear(const Event *event);

#endif
