#include <time.h>
#include <stdlib.h>
#include "neuron.h"

// Return a random value between 5 and -5
double generate_link() {
  return (((double) (random() % 100)) / 100) - 0.5;
}

Neuron *create_neuron(size_t previous_layer_size) {
  // Creation of the neuron
  Neuron *n = malloc(sizeof(Neuron));
  n->bias = 0;
  n->value = 0;
  n->error = 0;
  n->nb_link = 0;

  if (previous_layer_size != 0) {
    // Add links for the next layer
    n->links = malloc(sizeof(double) * previous_layer_size);
    n->nb_link = previous_layer_size;

    // Generating random weight for each links
    for (size_t i = 0; i < previous_layer_size; i++)
      n->links[i] = generate_link();
  }
  return n;
}