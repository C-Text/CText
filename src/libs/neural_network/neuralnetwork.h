#ifndef CTEXT_NEURALNETWORK_H
#define CTEXT_NEURALNETWORK_H
#include "neuron.h"
#include "../list/list.h"

// ================================
// Type definition
// ================================

/**
 * A neural network
 */
typedef struct NeuralNetwork {
  List layers;
} NeuralNetwork;

// ================================
// Functions prototypes
// ===============================

/**
 * Activation function sigmoid
 *
 * @param value the value to activate
 *
 * @return the activated value
 */
double sigmoid(double value);

/**
 * Initialize a neural network
 *
 * @param net                   the network to init
 * @param nb_layer              the number of layers in the networks
 * @param nb_neurons_per_layer  the numbers of neurons in layers
 */
void init(NeuralNetwork *net, size_t nb_layer, size_t nb_neurons_per_layer[]);

void print_info(NeuralNetwork *net);

/**
 *
 * @param network
 * @param entry
 */
void propagation(NeuralNetwork *network, double entry[]);

void update_error(NeuralNetwork *network, double expected[]);

/**
 *
 * @param network
 * @param coef
 */
void backpropagation(NeuralNetwork *network, double coef);

/**
 *
 * @param network
 * @param entry
 * @param expected
 * @return
 */
size_t learn(NeuralNetwork *network, double entry[], double expected[]);

/**
 *
 * @param network
 * @param entry
 * @return
 */
size_t run(NeuralNetwork *network, double entry[]);

/**
 *
 * @param network
 */
void save_neural_network(NeuralNetwork *network);

/**
 *
 * @param net
 */
void load_neural_network(NeuralNetwork *net);

#endif //CTEXT_NEURALNETWORK_H
