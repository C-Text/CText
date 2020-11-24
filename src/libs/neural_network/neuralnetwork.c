#include <math.h>
#include <stdio.h>
#include "neuralnetwork.h"

double sigmoid(double value) {
  return 1 / (1 + exp(-value));
}

double derivative(double activated_value) {
  return activated_value * (1 - activated_value);
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

void print_info(NeuralNetwork *net) {
  if (!net)
    return;
  // Init values
  List layers = net->layers;
  printf("number of layers : %lu\n", layers->length);
  Node *neurons = (layers->first);
  List list_neuron;
  Neuron *n;

  // All layers
  for (unsigned long i = 1; i <= layers->length; i++) {
    printf("\n===============layer: %lu=============== (with %lu neurons)\n",
           i,
           ((List) (neurons->value))->length);
    list_neuron = (List) (neurons->value);
    Node *current_n = list_neuron->first;
    n = (Neuron *) (current_n->value);

    // if it is not the first layer :
    if (n->links)
      // All neurons:
      for (unsigned long k = 1; k <= list_neuron->length; k++) {
        n = (Neuron *) (current_n->value);

        // Print infos of the neuron
        printf(
            "Current Neuron: %lu : value = %.10lf (with %lu links)\n bias : %"
            ".10lf | error : %.10lf\n ----links:------\n",
            k,
            n->value,
            n->nb_link,
            n->bias,
            n->error);
        // print all links
        for (unsigned long j = 0; j < n->nb_link; j++) {
          printf("  (%lu) = %.30f   ", j, n->links[j]);
        }
        printf("\n");
        current_n = current_n->next;
      }
      // it is the first layer :
    else
      for (unsigned long k = 1; k <= list_neuron->length; k++) {
        n = (Neuron *) (current_n->value);
        // Print all infos of the neuron
        printf("Current Neuron: %lu : value = %lf  ( with %lu links)\n error"
               " : %.10lf\n",
               k,
               n->value,
               (unsigned long) 0,
               n->error
        );
        current_n = (current_n->next);
      }

    neurons = neurons->next;
  }
}

double sum(List layer, size_t pos) {
  double value = 0;
  Node *current_node = layer->first;
  for (size_t neuron_i = 0; neuron_i < layer->length; neuron_i++) {
    Neuron *n = current_node->value;
    value += n->value * n->links[pos];
    current_node = current_node->next;
  }
  return value;
}

double sum_error(List layer, size_t pos) {
  double value = 0;
  Node *current_node = layer->first;
  for (size_t neuron_i = 0; neuron_i < layer->length; neuron_i++) {
    Neuron *n = current_node->value;
    value += n->error * n->links[pos];
    current_node = current_node->next;
  }
  return value;
}

void propagation(NeuralNetwork *network, double entries[]) {
  // Feed first layer with entries values
  Node *current_layer = network->layers->first;
  List l = (List) current_layer->value;
  Node *current_first = l->first;
  for (size_t i = 0; i < l->length; i++) {
    Neuron *first = (Neuron *) current_first->value;
    first->value = entries[i];
    current_first = current_first->next;
  }

  // Propagation of the information into the network
  Node *next_layer = current_layer->next;

  // Process all layers
  for (size_t i = 0; i < network->layers->length - 1; ++i) {
    List layer1 = (List) current_layer->value;
    List layer2 = (List) next_layer->value;

    Node *current_node = layer2->first;
    for (size_t neuron_i = 0; neuron_i < layer2->length; neuron_i++) {
      double new_val = sum(layer1, neuron_i);
      Neuron *n = current_node->value;
      n->value = sigmoid(new_val + n->bias);
      current_node = current_node->next;
    }

    // Next layer
    current_layer = current_layer->next;
    next_layer = next_layer->next;
  }
}

void backpropagation(NeuralNetwork *network, double learning_rate) {

}

void update_error(NeuralNetwork *network, double expected[]) {
  Node *last_nod = network->layers->last;
  List last = (List) last_nod->value;
  Node *current_node = last->first;

  for (size_t i = 0; i < last->length; i++) {
    Neuron *n = current_node->value;
    n->error = n->value - expected[i] * derivative(n->value);
    current_node = current_node->next;
  }

  // For all layers
  Node *prev = last_nod->previous;
  for (int lI = 0; lI < network->layers->length - 1; ++lI) {
    List prev_layer = prev->value;
    last = (List) last_nod->value;

    Node *previous_node = prev_layer->first;
    for (size_t i = 0; i < last->length; i++) {
      Neuron *n = previous_node->next;
      // Update error of n
      n->error = sum(last, i) * derivative(n->value);
      previous_node = previous_node->next;
    }

    prev = prev->previous;
    last_nod = last_nod->previous;
  }
}

// Machine learning function
size_t learn(NeuralNetwork *network, double entry[], double expected[]) {

}

size_t run(NeuralNetwork *network, double entry[]) {

}

void save_neural_network(NeuralNetwork *network);

void load_neural_network(NeuralNetwork *net);