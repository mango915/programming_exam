#include "Composite.h" // composite objects
#include "Functions.h" // for objects handling
#include <fstream>     // input handling

using namespace std;

int main(int argc, char const *argv[]) {
  ifstream file(argv[1]);
  const Event *event;

  // Loop over Events
  while ((event = read(file)) != 0) {
    dump(event);
    clear(event);
  }

  return 0;
}
