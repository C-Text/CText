#ifndef CTEXT_SRC_NEURALNETWORK_NEURON_H_
#define CTEXT_SRC_NEURALNETWORK_NEURON_H_

#include <stdbool.h>
#include <stdlib.h>

/**
 * Represent a neuron of the neural network
 */
typedef struct neuron_t {
  double value;// Input value
  double *weights; // Weights for the next layer (= link)
  size_t next_layer_size; // Next layer size

} neuron;

/**
 *
 * Initialize a neuron structure with default parameters.
 *
 * @date    20/10/2020, last modified: 25/10/2020
 * @version 0.0.2
 * @author  Valentin (Vinetos) Chassignol
 * @package neuralnetwork
 *
 * @param next_layer_size the number of neuron is the next layer
 *
 * @return initialized neuron_t with default parameters.
 */
neuron create_neuron(size_t next_layer_size);

/**
 * Print the content of the neuron in the console.
 *
 * @date    20/10/2020
 * @version 0.0.1
 * @author  Valentin (Vinetos) Chassignol
 * @package neuralnetwork
 *
 * @param n      the neuron to print.
 * @param pretty true if the output should be easy to read.
 */
void nprint(struct neuron_t *n, bool pretty);

#endif //CTEXT_SRC_NEURALNETWORK_NEURON_H_
