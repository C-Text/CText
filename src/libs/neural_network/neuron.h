#ifndef CTEXT_NEURALNETWORK_NEURON_H
#define CTEXT_NEURALNETWORK_NEURON_H

#include <stdlib.h>

/**
 * Represent a neuron of the neural network
 */
typedef struct Neuron {
  double value;
  double bias;
  double error;
  double *links;
  size_t nb_link;
} Neuron;

/**
 *
 * Initialize a neuron structure with default parameters.
 *
 * @date    20/10/2020, last modified: 23/11/2020
 * @version 0.0.3
 * @author  Valentin (Vinetos) Chassignol
 * @package neuralnetwork
 *
 * @param next_layer_size the number of neuron is the next layer
 *
 * @return initialized neuron_t with default parameters.
 */
Neuron *create_neuron(size_t next_layer_size);

#endif //CTEXT_NEURALNETWORK_NEURON_H