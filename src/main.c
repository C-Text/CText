#include "libs/neural_network/train.h"
#include "libs/application/application.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    // Launch interface
    return launch_application(argc, argv);
  }
  // ctext -t : train the network
  if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 't') {
    training();
    return 0;
  }

  return 0;
}