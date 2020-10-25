#ifndef CTEXT_SRC_NEURALNETWORK_LAYER_H_
#define CTEXT_SRC_NEURALNETWORK_LAYER_H_

#include "neuron.h"
#include <stdlib.h>
#include <stdbool.h>

/**
 * Represent a layer in the neural network
 */
typedef struct layer_t {
  size_t number_of_neurons;
  struct neuron_t *neurons;
  size_t next_layer_size;

} layer;

/**
 *
 * Initialize a layer structure with default parameters.
 *
 * @date    24/10/2020, last modified: 25/10/2020
 * @version 0.0.2
 * @author  Valentin (Vinetos) Chassignol
 * @package neuralnetwork
 *
 * @param number_of_neurons the number of neuron in this layer
 * @param next_layer_size   the number of neuron is the next layer
 *
 * @return initialized layer_t with default parameters.
 */
layer create_layer(size_t number_of_neurons, size_t next_layer_size);

/**
 * Feed the neuron with the input.
 * Replace the i-th neuron's value with the * i-th input value.
 *
 * @date    25/10/2020
 * @version 0.0.1
 * @author  Valentin (Vinetos) Chassignol
 * @package neuralnetwork
 *
 * @param layer The layer to feed
 * @param input
 */
void feed(struct layer_t *layer, const double input[layer->number_of_neurons]);

/**
 *
 * Activate the given layer using the softmax function.
 *
 * @warning It replaces the neuron's values with the activated one.
 *
 * @date    25/10/2020
 * @version 0.0.1
 * @author  Valentin (Vinetos) Chassignol
 * @package neuralnetwork
 *
 * @param layer      The layer to activate
 */
void activate(struct layer_t *layer);

/**
 *
 * Sum the value and weight of the layer l1 for de l2_i neuron.
 *
 * Consider a neural network with 2 layers l1 (l1_n neurons) and l2 (l2_n
 * neurons).
 * The input value of the neuron l2_i is the sum of all (value * weight) from
 * its connected neurons in l1.
 *
 * @date    25/10/2020
 * @version 0.0.1
 * @author  Valentin (Vinetos) Chassignol
 * @package neuralnetwork
 *
 * @param layer      The layer to sum
 * @param neuron_num The number of the neuron in the next layer
 *
 * @return the sum of values * weight for the l2_i neuron.
 */
double sum(struct layer_t *layer, size_t neuron_num);

/**
 *
 * Update a layer neuron's values.
 * Consider a neural network with 2 layers l1 (l1_n neurons) and l2 (l2_n
 * neurons).
 * The input value of the neuron l2_i is the sum of all (value * weight) from
 * its connected neurons in l1.
 *
 * @date    25/10/2020
 * @version 0.0.1
 * @author  Valentin (Vinetos) Chassignol
 * @package neuralnetwork
 *
 * @param l1 The first layer
 * @param l2 The layer to update
 *
 */
void feedforward(struct layer_t *l1, struct layer_t *l2);

/**
 * Print the content of a layer in the console.
 *
 * @date    23/10/2020
 * @version 0.0.1
 * @author  Valentin (Vinetos) Chassignol
 * @package neuralnetwork
 *
 * @param l      the layer to print.
 * @param pretty true if the output should be easy to read.
 */
void lprint(struct layer_t *l, bool pretty);

#endif //CTEXT_SRC_NEURALNETWORK_LAYER_H_
