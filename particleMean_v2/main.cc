#include <iostream>
#include <fstream>

... include header files ...

... declare functions to read and dump events ...

int main( int argc, char* argv[] ) {

  // open input file
  ...

  // create MassMean objects
  ...

  // loop over events
  const Event* ev;
  while ( ... ) {
    ...
  }

  // compute results
  ...

  // print number of selected events and results for both particles
  ...

  return 0;

}

