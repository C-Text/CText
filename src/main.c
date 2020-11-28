#include <stdio.h>
#include "libs/neural_network/neuralnetwork.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    // Launch interface
    printf("Should be the interface here\n");
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
  load_neural_network(&network,
                      "/home/vinetos/Documents/EPITA/SPE/PROG/CText/"
                      "CText/back-network.txt");

  for (int i = 0; i < 1000; i++) {
    propagation(&network, inputs[0]);
    backpropagation(&network, outputs[0], 0.5);
  }
  propagation(&network, inputs[0]);
  print_info(&network);
  return 0;
}