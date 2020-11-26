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
      {0.01, 0.99},
  };
  NeuralNetwork network;

  //init(&network, 3, nb_neurons_per_layer);
  load_neural_network(&network,
                      "/home/vinetos/Documents/EPITA/SPE/PROG/CText/"
                      "CText/back-network.txt");

  double *entry = inputs[0];
  double *expected = outputs[0];
  //propagation(&network, entry);
  backpropagation(&network, expected, 0.5);
  print_info(&network);

  for (int i = 0; i < 10000; i++) {
    for (int iI = 0; iI < 1; ++iI) {

      /*if (i % 100 == 0)
        error[iI] = *expected - predict(&network, entry);*/
    }

    /*if (i % 100 == 0) {
      printf("---------\n");
      printf("%lf\n", error[0]);
      printf("%lf\n", error[1]);
      printf("%lf\n", error[2]);
      printf("%lf\n", error[3]);
    }*/
  }

  return 0;
}