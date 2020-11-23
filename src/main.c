#include <stdio.h>
#include "libs/neural_network/neuralnetwork.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    // Launch interface
    printf("Should be the interface here");
  } else {
    printf("test: %s", argv[0]);
    NeuralNetwork network;
    size_t nb_neurons_per_layer[] = {2, 3, 1};
    init(&network, 3, nb_neurons_per_layer);
  }
  return 0;
}