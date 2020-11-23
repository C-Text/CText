#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

// ================================
// Type definition
// ================================

/**
 * A neuron
 */
typedef struct Neuron {
  double value;
  double bias;
  double error;
  double *links;
  size_t nb_link;
} Neuron;

/**
 */
typedef struct NeuralNetwork {
  List layers;
} NeuralNetwork;

// ================================
// Functions prototypes
// ===============================

/**
 *
 * @param value
 * @return
 */
double sigmmoide(double value);

/**
 *
 * @param value
 * @return
 */
double derivative(double value);

/**
 *
 * @param net
 * @param nb_layer
 * @param nb_neurons_per_layer
 */
void init(NeuralNetwork *net, size_t nb_layer, size_t nb_neurons_per_layer[]);

/**
 *
 * @param network
 * @param entry
 */
void propagation(NeuralNetwork *network, double entry[]);

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
 * @param file
 * @return
 */
double load_link(FILE *file);

/**
 *
 * @param file
 * @param num_layer
 * @param nb_neurons_per_layer
 * @return
 */
Neuron load_neuron(FILE *file, size_t num_layer, size_t nb_neurons_per_layer[]);

/**
 *
 * @param file
 * @param num_layer
 * @param nb_neurons_per_layer
 * @return
 */
List load_layer(FILE *file, int num_layer, size_t nb_neurons_per_layer[]);

/**
 *
 * @param net
 */
void load_neural_network(NeuralNetwork *net);

#endif //NEURALNETWORK_H
