#include "neuron.h"
#include <stdio.h>

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
neuron create_neuron(size_t next_layer_size) {
  struct neuron_t neuron;
  neuron.next_layer_size = next_layer_size;
  neuron.value = 0;
  // malloc reserved memory with undefined values which can lead to undefined
  // behavior
  neuron.weights = malloc(next_layer_size * sizeof(double));
  // Initialize default weights to 1
  for (int i = 0; i < next_layer_size; ++i)
    neuron.weights[i] = 1;

  return neuron;
}

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
void nprint(struct neuron_t *n, bool pretty) {
  if (pretty)
    printf("Neuron={v=%lf,w=[", n->value);
  else
    printf("{%lf,[", n->value);

  // Print weights
  for (int i = 0; i < n->next_layer_size; ++i)
    printf("%c%lf", (i == 0 ? 0 : ','), n->weights[i]);

  printf("]}");
}