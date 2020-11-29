#include <stdio.h>
#include "libs/neural_network/neuralnetwork.h"
#include "libs/application/application.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    // Launch interface
    return launch_application(argc, argv);
  }
  printf("Called: %s\n", argv[0]);
  double inputs[1][2] = {
      {0.05, 0.1}
  };
  double outputs[1][2] = {
      {0.05, 0.80},
  };
  size_t nb_neurons_per_layer[3] = {
      2, 2, 2
  };
  NeuralNetwork network;

  init(&network, 3, nb_neurons_per_layer);
  for (int i = 0; i < 1000; i++) {
    propagation(&network, inputs[0]);
    backpropagation(&network, outputs[0], 0.5);
  }
  propagation(&network, inputs[0]);
  return 0;
}