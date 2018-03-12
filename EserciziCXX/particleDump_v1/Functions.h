#ifndef Functions_h
#define Functions_h

#include <fstream>

// read the Event characteristics from a file
int read(std::ifstream &file, float *decay_x, float *decay_y, float *decay_z,
         int charges[], float mom_x[], float mom_y[], float mom_z[]);

// dump Event characteristics to the screen
void dump(int id_event, int no_particles, float decay_x, float decay_y,
          float decay_z, int charges[], float mom_x[], float mom_y[],
          float mom_z[]);

#endif
