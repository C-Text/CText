#include <stdio.h>
#include "libs/neural_network/neuralnetwork.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    // Launch interface
    printf("Should be the interface here\n");
  }
  printf("Called: %s\n", argv[0]);
  NeuralNetwork network;
  size_t nb_neurons_per_layer[] = {2, 3, 1};
  init(&network, 3, nb_neurons_per_layer);
  double inputs[2] = {0, 1};
  double expected[1] = {1};
  double learning_rate = 0.1;

  propagation(&network, inputs);
  update_error(&network, expected);
  print_info(&network);
  //backpropagation(&network, learning_rate);
  //propagation(&network, inputs);


  // Principal learn function
  int k = 0;
  int result = 0;
  /*for (int i = 1; i < 10000; i++) {
    // Random letter
    k = 1;

    size_t result = learn(&network, &inputs[k], &expected[k]);
    // Update all links with the errors
    backpropagation(&network, learning_rate);
    if(i == 9999) {
      printf("(%u) Expected : %f  ", i, expected[k]);
      printf("result : %lu   |   <input>: %i \n", result, inputs[k]);
      printf("\033[0m");
    }

    //for (int kI = 0; kI < 4; ++kI) {
    //  printf("Test %u and get %lu", kI, run(&network, &inputs[kI]))
   // }

  }*/

  return 0;
}