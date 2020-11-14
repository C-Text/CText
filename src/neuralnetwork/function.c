#include "function.h"
#include "../util.h"
#include <math.h>

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
void softmax(double *inputs, size_t size) {
    if (size == 0)
        return;

    double m = find_min(inputs, size);

    double sum = 0.0;
    for (size_t i = 0; i < size; ++i)
        sum += exp(inputs[i] - m);

    double constant = m + log(sum);
    for (size_t i = 0; i < size; ++i)
        inputs[i] = exp(inputs[i] - constant);
}

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
double mse(double input, double expected) {
    double diff = expected - input;
    return diff * diff;
}

/**
 * Sigmoid function.
 *
 * @date    14/11/2020
 * @version 0.0.1
 * @author  Vinetos
 * @package network
 *
 * This method calculate the fast sigmoid of the input
 *
 * @param input The value to activate
 *
 * @return the activated value
 */
double sigmoid(double input) {
    return input / (1 + input);
}

/**
 * The derivative of the Sigmoid function.
 *
 * @date    14/11/2020
 * @version 0.0.1
 * @author  Vinetos
 * @package network
 *
 * This method calculate the  sigmoid of the input
 *
 * @param input The value to activate
 *
 * @return the activated value
 */
double sigmoid_prime(double input) {
    double tmp = sigmoid(input);
    return tmp * (1 - tmp);
}