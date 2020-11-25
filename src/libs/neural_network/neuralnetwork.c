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
            (i == 0 ? 0 : nb_neurons_per_layer[i - 1])
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

double sum_error(List layer, double *links) {
  double value = 0;
  Node *current_node = layer->first;
  for (size_t neuron_i = 0; neuron_i < layer->length; neuron_i++) {
    Neuron *n = current_node->value;
    value += n->error * links[neuron_i];
    current_node = current_node->next;
  }
  return value;
}

double sum_layer(List layer, double *links) {
  // Feed the i-th neuron
  double sum = 0;
  size_t pos = 0;
  for (Node *node = layer->first; node != NULL; node = node->next) {
    Neuron *n = node->value;
    sum += n->value * links[pos];
    pos++;
  }
  return sum;
}

void propagation(NeuralNetwork *network, double *entries) {
  // Feed first layer with entries values
  Node *current_layer = network->layers->first;
  List first_layer = current_layer->value;

  for (Node *node = first_layer->first; node != NULL; node = node->next) {
    Neuron *n = node->value;
    n->value = *(entries++);
  }

  // Propagation of the information into the network
  Node *next_layer = NULL;
  for (next_layer = current_layer->next; next_layer != NULL;
       next_layer = next_layer->next, current_layer = current_layer->next) {
    List l1 = current_layer->value, l2 = next_layer->value;

    // Feed the i-th neuron
    for (Node *node2 = l2->first; node2 != NULL; node2 = node2->next) {
      Neuron *n2 = node2->value;
      double sum = sum_layer(l1, n2->links) + n2->bias;
      n2->value = sigmoid(sum);
    }
  }
}

void backpropagation(NeuralNetwork *network, double expected[], double
learning_rate) {

}

void save_neural_network(NeuralNetwork *net, const char *filename);

// Return the value of the current link
double set_new_link(FILE *file) {
  double link;
  int items = fscanf(file, "%lf / ", &link);
  return link + (items - items);
}

Neuron *set_new_neuron(size_t nb_neurons_per_layer[],
                       size_t index,
                       FILE *file) {

  // Take all info of th current neuron and save it
  Neuron *n = malloc(sizeof(Neuron));
  int items = fscanf(file,
                     "Value:\n%lf\nBias:\n%lf\nError:\n%lf\n",
                     &n->value,
                     &n->bias,
                     &n->error);
  n->nb_link = 0;

  // if it is not the first layer, take all links
  if (index != 0) {
    double *link = malloc(sizeof(double) * nb_neurons_per_layer[index - 1]);
    n->links = link;
    n->nb_link = nb_neurons_per_layer[index - 1];
    items += fscanf(file, "Links:\n");

    // Read all links
    for (size_t i = 0; i < nb_neurons_per_layer[index - 1]; i++) {
      n->links[i] = set_new_link(file);
    }
  }
  items += fscanf(file, "\n");
  return n;
}

List set_new_neurons_list(size_t nb_neurons_per_layer[],
                          size_t index,
                          FILE *file) {
  List neurons = create_list();

  // Add all neurons into the current layer
  for (size_t i = 0; i < nb_neurons_per_layer[index]; i++) {
    neurons = push_back_list(neurons,
                             set_new_neuron(nb_neurons_per_layer, index, file),
                             NeuronType);
  }
  return neurons;
}

void load_neural_network(NeuralNetwork *net, const char *filename) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    printf("Error: File not found !\n");
    exit(EXIT_FAILURE);
  }

  net->layers = create_list();

  // Init the number of layers
  size_t nb_layer = 0;
  int items = fscanf(file, "layers: %zi\n", &nb_layer);

  // Take the number of neurons into each layers
  size_t nb_neurons_per_layer[nb_layer];
  items += fscanf(file, "neurons:");
  int k = 0;
  while (fscanf(file, " %zi", &nb_neurons_per_layer[k++]));

  // Add all layers into network :
  int layer_num;
  for (size_t i = 0; i < nb_layer; i++) {
    items += fscanf(file, "= Layer %d =\n\n", &layer_num);

    net->layers = push_back_list(net->layers,
                                 set_new_neurons_list(nb_neurons_per_layer,
                                                      i,
                                                      file),
                                 LayerType);
  }

  fclose(file);
}

double predict(NeuralNetwork *network, double *input) {
  propagation(network, input);
  return ((Neuron *) ((List) network->layers->last->value)->last->value)->value;
}