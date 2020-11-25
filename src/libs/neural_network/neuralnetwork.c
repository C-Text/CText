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

double sum(List layer, double *links) {
  double value = 0;
  Node *current_node = layer->first;
  for (size_t neuron_i = 0; neuron_i < layer->length; neuron_i++) {
    Neuron *n = current_node->value;
    value += n->value * links[neuron_i];
    current_node = current_node->next;
  }
  return value;
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
      Neuron *n = current_node->value;
      double new_val = sum(layer1, n->links);
      n->value = sigmoid(new_val + n->bias);
      current_node = current_node->next;
    }

    // Next layer
    current_layer = current_layer->next;
    next_layer = next_layer->next;
  }
}

void calculate_output_error(Node *node, size_t i, void *args, void *output) {
  Neuron *n = node->value;
  double *expected = args;
  double diff = expected[i] - n->value;
  n->error = (diff * diff) / 2;
  double *total = output;
  *total += n->error;
}

void update_links(Node *node, List previous_layer, double expected, double lr) {
  // We are in the first layer so no link to update
  if (!previous_layer)
    return;

  //Impact of links
  Neuron *n = node->value;
  Node *prev_n = previous_layer->first;
  for (int linkI = 0; linkI < n->nb_link; ++linkI) {
    Neuron *pn = prev_n->value;
    double cost = (n->value - expected) * n->value * (1 - n->value) * pn->value;
    n->links[linkI] = n->links[linkI] - lr * cost;
    prev_n = prev_n->next;
  }
}

double sum_error_t(List layer, size_t pos) {
  double sum = 0;
  Node *no = layer->first;
  Neuron *n = no->value;
  for (int linkI = 0; linkI < n->nb_link; ++linkI) {
    n = layer->first->value;
    sum += n->error * n->value * (1 - n->value) * n->links[pos];
    no = no->next;
  }
  return sum;
}

void backpropagation(NeuralNetwork *network, double expected[], double
learning_rate) {
  Node *last_layer_nod = network->layers->last;
  List last_layer = last_layer_nod->value;
  // Calculate the total error of output layers
  double total_error = 0;
  for_each_in(last_layer, calculate_output_error, expected, &total_error);

  // For each neurons in last layer
  Node *current_layer_nod = last_layer_nod->previous;
  List current_layer = current_layer_nod->value;
  Node *node = last_layer->first;
  for (int nI = 0; nI < last_layer->length; ++nI) {
    update_links(node, current_layer, expected[nI], learning_rate);
  }

  // Now we update hidden layers
  Node *prev_layer_nod = current_layer_nod->previous;
  for (int hlI = 0; hlI < network->layers->length - 2; ++hlI) {
    List pre_prev_layer = prev_layer_nod->value;
    current_layer = current_layer_nod->value;
    last_layer = last_layer_nod->value;

    // For each neuron
    node = current_layer->first;
    for (int nI = 0; nI < last_layer->length; ++nI) {
      Neuron *n = node->value;
      // For each links
      double s = sum_error_t(last_layer, nI);
      s *= n->value * (1 - n->value);
      for (int linkI = 0; linkI < n->nb_link; ++linkI) {
        Neuron *linked = get_element_by_index(pre_prev_layer, linkI)->value;
        n->links[linkI] = n->links[linkI] - s * learning_rate * linked->value;
      }
    }

    last_layer_nod = last_layer_nod->previous;
    current_layer_nod = current_layer_nod->previous;
    prev_layer_nod = prev_layer_nod->previous;
  }
}

// Machine learning function
size_t learn(NeuralNetwork *network, double **entries, double **expected, double
learning_rate) {

}

size_t run(NeuralNetwork *network, double entry[]) {

}

void save_neural_network(NeuralNetwork *network);

// Return the value of the current link
double set_new_link(FILE *file) {
  double link;
  fscanf(file, "%lf / ", &link);
  return link;
}

Neuron *set_new_neuron(size_t nb_neurons_per_layer[],
                       size_t index,
                       FILE *file) {

  // Take all info of th current neuron and save it
  Neuron *n = malloc(sizeof(Neuron));
  fscanf(file,
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
    fscanf(file, "Links:\n");

    // Read all links
    for (size_t i = 0; i < nb_neurons_per_layer[index - 1]; i++) {
      n->links[i] = set_new_link(file);
    }
  }
  fscanf(file, "\n");
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
  fscanf(file, "layers: %zi\n", &nb_layer);

  // Take the number of neurons into each layers
  size_t nb_neurons_per_layer[nb_layer];
  fscanf(file, "neurons:");
  int k = 0;
  while (fscanf(file, " %zi", &nb_neurons_per_layer[k++]));

  // Add all layers into network :
  int layer_num;
  for (size_t i = 0; i < nb_layer; i++) {
    fscanf(file, "= Layer %d =\n\n", &layer_num);

    net->layers = push_back_list(net->layers,
                                 set_new_neurons_list(nb_neurons_per_layer,
                                                      i,
                                                      file),
                                 LayerType);
  }

  fclose(file);
}