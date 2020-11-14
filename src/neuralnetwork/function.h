#ifndef CTEXT_SRC_NEURALNETWORK_FUNCTION_H_
#define CTEXT_SRC_NEURALNETWORK_FUNCTION_H_

#include <stdlib.h>

/**
 * Softmax activation.
 *
 * @date    25/10/2020
 * @version 0.0.1
 * @author  Vinetos
 * @package network
 *
 * This method activates the given input array using the softmax
 * classification method.
 *
 * @warning This method modify the given array.
 *
 * @throw error  when size < 0.
 * @param inputs the arrays of values to activate.
 * @param size   the size of the array
 *
 */
void softmax(double *inputs, size_t size);

/**
 * Mean squared error.
 *
 * @date    25/10/2020
 * @version 0.0.1
 * @author  Vinetos
 * @package network
 *
 * This method calculate the mean squared error between the input and the
 * expected output.
 *
 * @param input      The activated value of the neuron
 * @param expected   The expected value
 *
 * @return the mean squared error value.
 */
double mse(double input, double expected);

/**
 * Sigmoid function.
 *
 * @date    14/11/2020
 * @version 0.0.1
 * @author  Vinetos
 * @package network
 *
 * This method calculate the sigmoid of the input
 *
 * @param input The value to activate
 *
 * @return the activated value
 */
double sigmoid(double input);

/**
 * The derivative of the Sigmoid function.
 *
 * @date    14/11/2020
 * @version 0.0.1
 * @author  Vinetos
 * @package network
 *
 * This method calculate the sigmoid of the input
 *
 * @param input The value to activate
 *
 * @return the activated value
 */
double sigmoid_prime(double input);

#endif //CTEXT_SRC_NEURALNETWORK_FUNCTION_H_
