#include "layer.h"
#include "neuron.h"
#include "function.h"
#include <stdio.h>

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
layer create_layer(size_t number_of_neurons, size_t next_layer_size) {
  struct layer_t layer;
  layer.number_of_neurons = number_of_neurons;
  layer.next_layer_size = next_layer_size;
  layer.neurons =
      (struct neuron_t *) malloc(number_of_neurons * sizeof(struct neuron_t));

  for (size_t i = 0; i < number_of_neurons; i++)
    layer.neurons[i] = create_neuron(layer.next_layer_size);

  return layer;
}

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
void feed(struct layer_t *layer, const double input[layer->number_of_neurons]) {
  for (int i = 0; i < layer->number_of_neurons; i++)
    layer->neurons[i].value = input[i];
}

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
void activate(struct layer_t *layer) {
  double values[layer->number_of_neurons];
  for (int i = 0; i < layer->number_of_neurons; i++)
    values[i] = layer->neurons[i].value;

  softmax(values, layer->number_of_neurons);
  feed(layer, values);
}

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
double sum(struct layer_t *layer, size_t neuron_num) {
  double sum = 0;
  for (size_t i = 0; i < layer->number_of_neurons; ++i)
    sum += layer->neurons[i].value * layer->neurons[i].weights[neuron_num];

  return sum;
}

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
void feedforward(struct layer_t *l1, struct layer_t *l2) {
  for (size_t i = 0; i < l2->number_of_neurons; ++i)
    l2->neurons[i].value = sum(l1, i);
}

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
void lprint(struct layer_t *l, bool pretty) {
  if (pretty) {
    printf("Layer={num=%zu,next=%zu,\n",
           l->number_of_neurons,
           l->next_layer_size);
    for (size_t i = 0; i < l->number_of_neurons; i++) {
      printf("\t");
      nprint(&l->neurons[i], true);
      printf("\n");
    }
    printf("}");
  } else {
    printf("[");
    for (size_t i = 0; i < l->number_of_neurons; i++)
      nprint(&l->neurons[i], false);
    printf("]");
  }
}