#include <stdio.h>
#include "libs/neural_network/neuralnetwork.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    // Launch interface
    printf("Should be the interface here\n");
  }
  printf("Called: %s\n", argv[0]);
  double inputs[4][2] = {
      {0, 0},
      {0, 1},
      {1, 0},
      {1, 1},
  };
  NeuralNetwork network;

  size_t nb_neurons_per_layer[3] = {2, 3, 1};
  // init(&network, 3, nb_neurons_per_layer);
  load_neural_network(&network,
                      "/home/vinetos/Documents/EPITA/SPE/PROG/CText/"
                      "CText/xor-trained-network.txt");

  for (int iI = 0; iI < 4; ++iI) {
    double *entry = inputs[iI];
    propagation(&network, entry);
    //print_info(&network);
    printf("%d, %d = %lf\n", (int)entry[0], (int)entry[1], predict(&network,
    entry));
  }

  return 0;
}