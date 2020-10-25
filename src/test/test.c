#include "test.h"
#include "test_method.h"

/**
 * Run tests.
 *
 * @return positive number if a test failed
 */
int tests() {
  // Softmax tests
  double inputs[] = {1., 4.2, 0.6, 1.23, 4.3, 1.2, 2.5};
  double expected[] = {0.016590, 0.4069950, .011121, 0.020880,
                       0.449799, 0.020263, 0.074351};
  test_softmax(inputs, expected, 7);

  double inputs2[] = {1., 3., 2.5, 5., 4., 2.};
  double expected2[] = {.011, .082, .05, .605, .222, .03};
  test_softmax(inputs2, expected2, 6);

  // MSE tests
  double inputs_mse[1][2] = {
      {-0.37, 0}
  };
  double expected_mse[] = {.1369};
  tes_mse(1, inputs_mse, expected_mse);
}