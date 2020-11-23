#include <math.h>
#include <stdio.h>
#include "neuralnetwork.h"

double sigmoid(double value) {
  return 1 / (1 + exp(-value));
}

List create_layer(size_t layer_size, size_t next_layer_size) {
  // Create a layer
  List neurons = create_list();

  // Add all neurons into it
  while (layer_size-- > 0)
    neurons = push_back_list(
        neurons,
        create_neuron(next_layer_size),
        NeuronType
    );

  return neurons;
}

void init(NeuralNetwork *net, size_t nb_layer, size_t nb_neurons_per_layer[]) {
  // Create the list of layers
  net->layers = create_list();

  // Adding all layers
  for (size_t i = 0; i < nb_layer; i++) {
    net->layers = push_back_list(
        net->layers,
        create_layer(
            nb_neurons_per_layer[i],
            (i == (nb_layer - 1) ? 0 : nb_neurons_per_layer[i + 1])
        ),
        LayerType
    );
  }
}

void propagation(NeuralNetwork *network, double entry[]);

void backpropagation(NeuralNetwork *network, double coef);

size_t learn(NeuralNetwork *network, double entry[], double expected[]);

size_t run(NeuralNetwork *network, double entry[]);

void save_neural_network(NeuralNetwork *network);

void load_neural_network(NeuralNetwork *net);