#ifndef NN_TEST_METHOD_H
#define NN_TEST_METHOD_H

#include "stdlib.h"

int test_softmax(double *inputs, double *expected, size_t size);

int tes_mse(size_t size, double input[size][2], double expected[size]);

#endif // NN_TEST_METHOD_H
