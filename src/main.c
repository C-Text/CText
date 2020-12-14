#include "libs/neural_network/train.h"
#include "libs/application/application.h"
#include "libs/string/string.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    // Launch interface
    return launch_application(argc, argv);
  }
  // ctext -t : train the network
  if (argc == 2 && equals(argv[1], "-t")) {
    training();
    return 0;
  }

  return 0;
}