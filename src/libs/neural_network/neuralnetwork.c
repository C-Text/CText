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

double sum_layer(List layer, double *links) {
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
    n->input = *entries;
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
      n2->input = sum;
      n2->value = sigmoid(sum);
    }
  }

}

void update_error(NeuralNetwork *network, double expected[]) {

  Node *current_layer_2 = network->layers->last;
  List layer_2 = (List) current_layer_2->value;
  Node *current_neuron_2 = layer_2->first;

  // Calcul all delta errors of the last layer
  for (size_t i_neuron = 0; i_neuron < layer_2->length; i_neuron++) {
    Neuron *neuron_2 = (Neuron *) current_neuron_2->value;
    neuron_2->error = expected[i_neuron] - neuron_2->value;
    current_neuron_2 = current_neuron_2->next;
  }

  current_layer_2 = network->layers->last;
  Node *current_layer_1 = current_layer_2->previous;

  // All other layer :
  for (size_t i_layers = 0; i_layers < network->layers->length - 2;
       i_layers++) {
    layer_2 = (List) current_layer_2->value;
    List layer_1 = (List) current_layer_1->value;
    Node *current_neuron_1 = layer_1->first;

    // All neurons of the next layer :
    for (size_t i_neuron_1 = 0; i_neuron_1 < layer_1->length; i_neuron_1++) {
      Neuron *neuron_1 = (Neuron *) current_neuron_1->value;

      // Derivation value
      double derivate_neuron = neuron_1->value * (1 - neuron_1->value);

      double error_propagation = 0;
      Node *current_neuron_2 = layer_2->first;

      // for all neurons in the layer
      for (size_t i_neuron_2 = 0; i_neuron_2 < layer_2->length; i_neuron_2++) {
        Neuron *neuron_2 = (Neuron *) current_neuron_2->value;

        // sum of the error
        double link_2 = neuron_2->links[i_neuron_1];
        error_propagation += link_2 * neuron_2->error;

        current_neuron_2 = current_neuron_2->next;
      }
      // Stock the current error sum into the neuron
      neuron_1->error += derivate_neuron * error_propagation * neuron_1->bias;

      current_neuron_1 = current_neuron_1->next;
    }
    // Next layer
    current_layer_1 = current_layer_1->previous;
    current_layer_2 = current_layer_2->previous;
  }
}

void backpropagation(NeuralNetwork *network, double expected[], double
learning_rate) {
  update_error(network, expected);
  Node *current_layer_2 = network->layers->last;
  Node *current_layer_1 = current_layer_2->previous;

  // All layer :
  for (size_t i_layers = 0; i_layers < network->layers->length - 1;
       i_layers++) {
    List layer_1 = (List) current_layer_1->value;
    List layer_2 = (List) current_layer_2->value;

    Node *current_neuron_2 = layer_2->first;

    // All neurons in current layer:
    for (size_t i_neuron_2 = 0; i_neuron_2 < layer_2->length; i_neuron_2++) {
      Neuron *neuron_2 = (Neuron *) current_neuron_2->value;

      Node *current_neuron_1 = layer_1->first;

      // All links in current neuron:
      for (size_t i_link_2 = 0; i_link_2 < neuron_2->nb_link; i_link_2++) {
        Neuron *neuron_1 = (Neuron *) current_neuron_1->value;

        // Calcul of the new weight of the link
        double tot = neuron_2->links[i_link_2]
            + learning_rate * neuron_1->value * neuron_2->error;
        neuron_2->bias += neuron_2->value * neuron_2->error;

        neuron_2->links[i_link_2] = tot;
        current_neuron_1 = current_neuron_1->next;
      }
      // Next neuron
      current_neuron_2 = current_neuron_2->next;
    }
    // Next layer
    current_layer_1 = current_layer_1->previous;
    current_layer_2 = current_layer_2->previous;
  }

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

double *predict(NeuralNetwork *network, double *input) {
  propagation(network, input);
  List output_layer = network->layers->last->value;
  double *results = malloc(sizeof(double) * output_layer->length);
  for (Node *node = output_layer->first; node != NULL; node = node->next) {
    *(results++) = ((Neuron *) node->value)->value;
  }

  return results;
}