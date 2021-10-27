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

/**
 * Prints the neural network in the console
 *
 * @param net the network to print
 */
void print_info(NeuralNetwork *net);

/**
 * Save the neural network in a file
 *
 * @param net      the network to save
 * @param filename the file where to save the network
 */
void save_neural_network(NeuralNetwork *net, const char *filename);

/**
 * Load the neural network from a file
 *
 * @param net      the network to save
 * @param filename the file where to save the network
 */
void load_neural_network(NeuralNetwork *net, const char *filename);

/**
 * Feedforward the input in the neural network
 *
 * @param network The network the feed
 * @param entries the input
 */
void propagation(NeuralNetwork *network, double *entries);

/**
 * Update error, weights and biases of the neural network according the
 * expected result
 *
 * @param network The network the feed
 * @param entries the input of the neural network
 */
void backpropagation(NeuralNetwork *network, double expected[], double
learning_rate);

/**
 * Use a trained network to predict a result from the given input
 *
 * @param network a trained neural network (or untrained if you are doing
 * weird things)
 * @param input   the input of the neural network
 *
 * @return an array containing the result of each output neurons
 */
size_t predict(NeuralNetwork *network, double input[]);

#endif //CTEXT_NEURALNETWORK_H
