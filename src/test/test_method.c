#include "test_method.h"
#include "../neuralnetwork/function.h"
#include "../util.h"
#include <stdio.h>

int test_softmax(double *inputs, double *expected, size_t size) {
  printf("============= TEST: SOFTMAX =============\n");
  double *test = inputs;

  // Print input
  printf("Input Array: ");
  print_array(inputs, size);

  // Clone inputs
  for (size_t i = 0; i < size; i++)
    test[i] = inputs[i];

  softmax(test, size);

  // Print results
  printf("Softmax Array: ");
  print_array(test, size);

  // Test results
  for (size_t i = 0; i < size; i++)
    if (test[i] - expected[i] > 0.01) { // Compare the two values
      printf("Error on index %zu : expected %lf got %lf. Diff : %lf", i,
             expected[i], test[i], (test[i] - expected[i]));
      return 1;
    }

  return 0;
}

int tes_mse(size_t size, double inputs[size][2], double expected[size]) {
  printf("============= TEST: MSE =============\n");
  // Print input
  printf("Input Arrays: [\n");
  for (int i = 0; i < size; ++i) {
    printf("\t");
    print_array(inputs[i], 2);
  }
  printf("]");

  // Test results
  for (size_t i = 0; i < size; i++) {
    double mse_v = mse(inputs[i][0], inputs[i][1]);
    if (mse_v - expected[i] > 0.01) { // Compare the
      // two values
      printf("Error on index %zu : expected %lf got %lf. Diff : %lf", i,
             expected[i], mse_v, (mse_v - expected[i]));
      return 1;
    }
  }

  return 0;
}