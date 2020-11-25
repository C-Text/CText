#include <stdio.h>
#include "libs/neural_network/neuralnetwork.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    // Launch interface
    printf("Should be the interface here\n");
  }
  printf("Called: %s\n", argv[0]);
  NeuralNetwork network;
  load_neural_network(&network,
                      "/home/vinetos/Documents/EPITA/SPE/PROG/CText/CText/network.txt");
  double expected[] = {0, 1};
  //backpropagation(&network, expected, 0.8);
  //print_info(&network);


  return 0;
}